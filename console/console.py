#!/usr/bin/env python3
"""L4 cloud-phone web console (P1): instance list, lifecycle control via
mgr.sh, and browser screen streaming via adb screenrecord (H.264) +
WebSocket. Input goes back through adb input commands.

Single file, stdlib only. Listens on 0.0.0.0:8088 (LAN/Tailscale).
Optional shared token: set CONSOLE_TOKEN to require ?token= / X-Token.
"""
import asyncio
import json
import os
import re
import subprocess
import sys
import time

BASE = os.path.dirname(os.path.abspath(__file__))
ADB = os.environ.get("CONSOLE_ADB", "/srv/console/adb")
MGR = os.environ.get("CONSOLE_MGR", "/vol1/redroid-inst/mgr.sh")
INST_DIR = os.environ.get("CONSOLE_INST_DIR", "/vol1/redroid-inst")
PORT = int(os.environ.get("CONSOLE_PORT", "8088"))
TOKEN = os.environ.get("CONSOLE_TOKEN", "")

# Legacy hand-managed instances: streamable, not lifecycle-managed.
LEGACY = {"redroid": 5555, "redroid2": 5556}

STREAMS = {}  # name -> StreamState


def sh(args, timeout=20):
    return subprocess.run(args, capture_output=True, text=True, timeout=timeout)


def list_instances():
    out = []
    # managed instances: directories under INST_DIR with a compose file
    try:
        names = sorted(os.listdir(INST_DIR))
    except OSError:
        names = []
    for name in names:
        d = os.path.join(INST_DIR, name)
        if name in ("template",) or not os.path.isdir(d):
            continue
        if not os.path.exists(os.path.join(d, "docker-compose.yaml")):
            continue
        m = re.match(r"vm(\d+)$", name)
        idx = int(m.group(1)) if m else None
        port = 5555 + idx if idx else None
        out.append({"name": name, "index": idx, "adb": port, "managed": True})
    for name, port in LEGACY.items():
        out.append({"name": name, "index": None, "adb": port, "managed": False})
    # enrich with container state
    try:
        ps = sh(["docker", "ps", "-a", "--format", "{{.Names}} {{.State}}"], 10).stdout
        states = dict(line.split(" ", 1) for line in ps.strip().splitlines() if " " in line)
    except Exception:
        states = {}
    for it in out:
        it["state"] = states.get(it["name"], "absent")
    return out


def adb_serial(inst):
    return f"127.0.0.1:{inst['adb']}"


async def adb_connect(serial):
    await asyncio.create_subprocess_exec(
        ADB, "connect", serial,
        stdout=asyncio.subprocess.DEVNULL, stderr=asyncio.subprocess.DEVNULL)


class StreamState:
    def __init__(self, name, serial):
        self.name = name
        self.serial = serial
        self.proc = None
        self.clients = set()
        self.task = None
        self.lock = asyncio.Lock()

    async def ensure_started(self):
        async with self.lock:
            if self.proc and self.proc.returncode is None:
                return
            await adb_connect(self.serial)
            self.proc = await asyncio.create_subprocess_exec(
                ADB, "-s", self.serial, "exec-out", "screenrecord",
                "--output-format=h264", "--size", "960x540",
                "--bit-rate", "4000000", "-",
                stdout=asyncio.subprocess.PIPE,
                stderr=asyncio.subprocess.DEVNULL)
            self.task = asyncio.create_task(self.pump())

    async def pump(self):
        # screenrecord caps at 180s; respawn transparently and tell
        # clients to reset their muxer. Guard against instant-death
        # loops (bad adb, dead instance): 3 strikes -> error + stop.
        strikes = 0
        while self.clients:
            started = time.time()
            got = 0
            try:
                while True:
                    chunk = await self.proc.stdout.read(65536)
                    if not chunk:
                        break
                    got += len(chunk)
                    dead = []
                    for q in self.clients:
                        try:
                            q.put_nowait(chunk)
                        except asyncio.QueueFull:
                            dead.append(q)
                    for q in dead:
                        self.clients.discard(q)
            except Exception:
                pass
            if not self.clients:
                break
            if got == 0 and time.time() - started < 2:
                strikes += 1
                if strikes >= 3:
                    for q in self.clients:
                        q.put_nowait(b'\x00CTRL:ERROR:stream failed to start (adb/screenrecord)')
                    break
                await asyncio.sleep(2)
            else:
                strikes = 0
                for q in self.clients:
                    q.put_nowait(b"\x00CTRL:RESTART")
            await adb_connect(self.serial)
            self.proc = await asyncio.create_subprocess_exec(
                ADB, "-s", self.serial, "exec-out", "screenrecord",
                "--output-format=h264", "--size", "960x540",
                "--bit-rate", "4000000", "-",
                stdout=asyncio.subprocess.PIPE,
                stderr=asyncio.subprocess.DEVNULL)
        await self.stop_proc()

    async def stop_proc(self):
        if self.proc and self.proc.returncode is None:
            self.proc.terminate()
            try:
                await asyncio.wait_for(self.proc.wait(), 3)
            except asyncio.TimeoutError:
                self.proc.kill()
        self.proc = None


# ---------------------------------------------------------------- HTTP/WS
# Minimal HTTP + WebSocket server on asyncio (stdlib only).

WS_GUID = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11"


def ws_accept_key(key):
    import base64, hashlib
    return base64.b64encode(
        hashlib.sha1((key + WS_GUID).encode()).digest()).decode()


async def ws_send(writer, data, opcode=0x2):
    if isinstance(data, str):
        data = data.encode()
        opcode = 0x1
    hdr = bytearray([0x80 | opcode])
    n = len(data)
    if n < 126:
        hdr.append(n)
    elif n < 65536:
        hdr.append(126)
        hdr += n.to_bytes(2, "big")
    else:
        hdr.append(127)
        hdr += n.to_bytes(8, "big")
    writer.write(bytes(hdr) + data)
    await writer.drain()


async def ws_recv(reader):
    hdr = await reader.readexactly(2)
    fin_op = hdr[0]
    masked = hdr[1] & 0x80
    n = hdr[1] & 0x7F
    if n == 126:
        n = int.from_bytes(await reader.readexactly(2), "big")
    elif n == 127:
        n = int.from_bytes(await reader.readexactly(8), "big")
    mask = await reader.readexactly(4) if masked else b"\x00" * 4
    data = await reader.readexactly(n) if n else b""
    if masked:
        data = bytes(b ^ mask[i % 4] for i, b in enumerate(data))
    return fin_op & 0x0F, data


def check_token(req_path, headers):
    if not TOKEN:
        return True
    if f"token={TOKEN}" in req_path:
        return True
    return headers.get("x-token") == TOKEN


async def handle_client(reader, writer):
    try:
        req = await reader.readuntil(b"\r\n\r\n")
    except Exception:
        writer.close()
        return
    head = req.decode("latin1")
    lines = head.split("\r\n")
    method, path = lines[0].split(" ", 2)[:2]
    headers = {}
    for ln in lines[1:]:
        if ": " in ln:
            k, v = ln.split(": ", 1)
            headers[k.lower()] = v
    body = b""
    clen = int(headers.get("content-length", "0"))
    if clen:
        body = await reader.readexactly(clen)

    async def reply(code, ctype, payload):
        if isinstance(payload, str):
            payload = payload.encode()
        resp = (f"HTTP/1.1 {code} OK\r\nContent-Type: {ctype}\r\n"
                f"Content-Length: {len(payload)}\r\nConnection: close\r\n\r\n")
        writer.write(resp.encode() + payload)
        await writer.drain()
        writer.close()

    if not check_token(path, headers):
        return await reply(403, "text/plain", "forbidden")

    route = path.split("?")[0]
    if route == "/" or route == "/index.html":
        with open(os.path.join(BASE, "index.html"), "rb") as f:
            return await reply(200, "text/html; charset=utf-8", f.read())
    if route == "/jmuxer.min.js":
        with open(os.path.join(BASE, "jmuxer.min.js"), "rb") as f:
            return await reply(200, "application/javascript", f.read())
    if route == "/api/instances" and method == "GET":
        return await reply(200, "application/json",
                           json.dumps(list_instances()))
    m = re.match(r"^/api/instance/([\w-]+)/(start|stop|restart)$", route)
    if m and method == "POST":
        name, action = m.groups()
        insts = {i["name"]: i for i in list_instances()}
        if name not in insts or not insts[name]["managed"]:
            return await reply(400, "application/json",
                               json.dumps({"error": "not a managed instance"}))
        try:
            r = await asyncio.get_event_loop().run_in_executor(
                None, lambda: sh([MGR, action, name], 120))
            return await reply(200, "application/json", json.dumps(
                {"rc": r.returncode, "out": (r.stdout + r.stderr)[-2000:]}))
        except Exception as e:
            return await reply(500, "application/json",
                               json.dumps({"error": str(e)}))
    m = re.match(r"^/api/instance/([\w-]+)/sensors$", route)
    if m and method in ("GET", "POST"):
        name = m.group(1)
        insts = {i["name"]: i for i in list_instances()}
        if name not in insts:
            return await reply(404, "application/json",
                               json.dumps({"error": "no such instance"}))
        if insts[name]["state"] != "running":
            return await reply(400, "application/json",
                               json.dumps({"error": "instance not running"}))
        loop = asyncio.get_event_loop()
        if method == "POST":
            try:
                cfg = json.loads(body or b"{}")
                mode = cfg.get("mode", "sine")
                if mode not in ("sine", "static"):
                    raise ValueError("mode must be sine|static")
                def vec(key):
                    v = cfg.get(key)
                    if not isinstance(v, list) or len(v) != 3:
                        raise ValueError(key + " must be [x,y,z]")
                    out = []
                    for x in v:
                        f = float(x)
                        if abs(f) > 100:
                            raise ValueError(key + " out of range")
                        out.append(f)
                    return ",".join(f"{f:g}" for f in out)
                sets = [("persist.l4.sensors.mode", mode),
                        ("persist.l4.sensors.accel", vec("accel")),
                        ("persist.l4.sensors.gyro", vec("gyro"))]
            except Exception as e:
                return await reply(400, "application/json",
                                   json.dumps({"error": str(e)}))
            def apply():
                for k, v in sets:
                    sh(["docker", "exec", name, "setprop", k, v], 10)
            await loop.run_in_executor(None, apply)
        def readback():
            vals = {}
            for key, prop in (("mode", "persist.l4.sensors.mode"),
                              ("accel", "persist.l4.sensors.accel"),
                              ("gyro", "persist.l4.sensors.gyro")):
                r = sh(["docker", "exec", name, "getprop", prop], 10)
                vals[key] = r.stdout.strip()
            return vals
        vals = await loop.run_in_executor(None, readback)
        return await reply(200, "application/json", json.dumps(vals))
    m = re.match(r"^/ws/([\w-]+)$", route)
    if m and headers.get("upgrade", "").lower() == "websocket":
        return await handle_ws(reader, writer, m.group(1), headers)
    return await reply(404, "text/plain", "not found")


async def handle_ws(reader, writer, name, headers):
    insts = {i["name"]: i for i in list_instances()}
    if name not in insts:
        writer.close()
        return
    inst = insts[name]
    serial = adb_serial(inst)
    key = headers.get("sec-websocket-key", "")
    resp = ("HTTP/1.1 101 Switching Protocols\r\nUpgrade: websocket\r\n"
            "Connection: Upgrade\r\n"
            f"Sec-WebSocket-Accept: {ws_accept_key(key)}\r\n\r\n")
    writer.write(resp.encode())
    await writer.drain()

    st = STREAMS.get(name)
    if st is None:
        st = STREAMS[name] = StreamState(name, serial)
    q = asyncio.Queue(maxsize=64)
    st.clients.add(q)
    await st.ensure_started()

    async def sender():
        while True:
            chunk = await q.get()
            if chunk == b"\x00CTRL:RESTART":
                await ws_send(writer, json.dumps({"t": "restart"}), 0x1)
            elif chunk.startswith(b"\x00CTRL:ERROR:"):
                await ws_send(writer, json.dumps(
                    {"t": "error", "msg": chunk[12:].decode()}), 0x1)
            else:
                await ws_send(writer, chunk, 0x2)

    send_task = asyncio.create_task(sender())
    try:
        while True:
            op, data = await ws_recv(reader)
            if op == 0x8:
                break
            if op == 0x9:
                await ws_send(writer, data, 0xA)
                continue
            if op != 0x1:
                continue
            try:
                msg = json.loads(data)
            except Exception:
                continue
            await handle_input(serial, msg)
    except Exception:
        pass
    finally:
        send_task.cancel()
        st.clients.discard(q)
        if not st.clients and st.task:
            st.task.cancel()
            await st.stop_proc()
        writer.close()


async def adb_shell(serial, cmd):
    p = await asyncio.create_subprocess_exec(
        ADB, "-s", serial, "shell", cmd,
        stdout=asyncio.subprocess.DEVNULL, stderr=asyncio.subprocess.DEVNULL)
    await p.wait()


async def handle_input(serial, msg):
    t = msg.get("t")
    if t == "tap":
        await adb_shell(serial, f"input tap {int(msg['x'])} {int(msg['y'])}")
    elif t == "swipe":
        await adb_shell(serial, "input swipe {} {} {} {} {}".format(
            int(msg["x1"]), int(msg["y1"]), int(msg["x2"]), int(msg["y2"]),
            int(msg.get("ms", 200))))
    elif t == "key":
        await adb_shell(serial, f"input keyevent {int(msg['code'])}")
    elif t == "text":
        txt = str(msg.get("text", ""))[:200].replace(" ", "%s")
        txt = "".join(c for c in txt if c.isalnum() or c in "%s._@-/:")
        if txt:
            await adb_shell(serial, f"input text {txt}")


async def main():
    server = await asyncio.start_server(handle_client, "0.0.0.0", PORT)
    print(f"console listening on :{PORT} (adb={ADB} mgr={MGR})", flush=True)
    async with server:
        await server.serve_forever()


if __name__ == "__main__":
    asyncio.run(main())
