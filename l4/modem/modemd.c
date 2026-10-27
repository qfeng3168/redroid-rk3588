// l4-modemd: virtual AT modem for the redroid guest (L4-M2 Telephony).
//
// Listens on 127.0.0.1:<port> (argv[1], default 8901). The image's stock
// libril + libreference-ril.so connects here via `rild.libargs=-p <port>`
// and speaks 3GPP 27.007 AT commands; this daemon answers as a GSM modem
// with a ready SIM so the framework sees a registered phone with a real
// IMEI/IMSI/ICCID/operator. Identity values come from system properties
// (persist.l4.modem.*), read per request:
//
//   persist.l4.modem.imei    (default 353328051234563, Luhn-valid)
//   persist.l4.modem.imsi    (default 460001234567890, China Mobile)
//   persist.l4.modem.iccid   (default 89860012345678901234)
//   persist.l4.modem.msisdn  (default 8613800138000)
//   persist.l4.modem.op_long (default "China Mobile")
//   persist.l4.modem.op_short(default "CMCC")
//   persist.l4.modem.op_num (default "46000")
//   persist.l4.modem.rssi    (default 21, AT+CSQ scale 0..31)
//
// Scope: identity + registration + signal. Voice calls and data calls
// intentionally fail (ERROR) in this milestone.
//
// Local test build: cc -DL4_LOCAL_TEST modemd.c -o modemd
//   (properties then come from env L4P_<name>, e.g. L4P_imei=...)
#define _POSIX_C_SOURCE 200809L
#include <arpa/inet.h>
#include <ctype.h>
#include <netinet/in.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>

#ifdef L4_LOCAL_TEST
static int prop_get(const char* name, char* out, const char* dflt) {
    char key[96];
    snprintf(key, sizeof key, "L4P_%s", name + 15);  // strip "persist.l4."
    const char* v = getenv(key);
    snprintf(out, 128, "%s", v ? v : dflt);
    return (int)strlen(out);
}
#else
int __system_property_get(const char* name, char* value);
static int prop_get(const char* name, char* out, const char* dflt) {
    char buf[128];
    int n = __system_property_get(name, buf);
    if (n <= 0) {
        snprintf(out, 128, "%s", dflt);
        return (int)strlen(out);
    }
    snprintf(out, 128, "%s", buf);
    return n;
}
#endif

static char P_IMEI[128], P_IMSI[128], P_ICCID[128], P_MSISDN[128];
static char P_OPL[128], P_OPS[128], P_OPN[128];
static int P_RSSI;

static void load_props(void) {
    char rssi[128];
    prop_get("persist.l4.modem.imei", P_IMEI, "353328051234563");
    prop_get("persist.l4.modem.imsi", P_IMSI, "460001234567890");
    prop_get("persist.l4.modem.iccid", P_ICCID, "89860012345678901234");
    prop_get("persist.l4.modem.msisdn", P_MSISDN, "8613800138000");
    prop_get("persist.l4.modem.op_long", P_OPL, "China Mobile");
    prop_get("persist.l4.modem.op_short", P_OPS, "CMCC");
    prop_get("persist.l4.modem.op_num", P_OPN, "46000");
    prop_get("persist.l4.modem.rssi", rssi, "21");
    P_RSSI = atoi(rssi);
    if (P_RSSI < 0 || P_RSSI > 31) P_RSSI = 21;
}

// ---- modem state --------------------------------------------------------
static int g_cfun = 1;        // radio on
static int g_cops_fmt = 0;    // 0=long alpha, 1=short, 2=numeric
static int g_creg_n = 0;      // unsolicited mode set via AT+CREG=<n>
static int g_cgreg_n = 0;
static const char* kLac = "1234";      // hex
static const char* kCi = "00005678";   // hex

// ---- EF (SIM file) contents ---------------------------------------------
// ICCID: BCD with swapped nibbles, 0xF padding (GSM 11.11).
static int ef_iccid(unsigned char* out) {
    int n = 0;
    const char* s = P_ICCID;
    for (int i = 0; s[i] && s[i + 1] && n < 10; i += 2)
        out[n++] = (unsigned char)(((s[i + 1] - '0') << 4) | (s[i] - '0'));
    if (strlen(s) % 2 && n < 10)
        out[n++] = (unsigned char)(0xF0 | (s[strlen(s) - 1] - '0'));
    while (n < 10) out[n++] = 0xFF;
    return 10;
}

struct ef_file {
    int id;
    int size;          // transparent EF size in bytes
    unsigned char data[64];
};
// Record EFs are handled separately (only MSISDN in this milestone).
static struct ef_file g_efs[8];
static int g_nefs = 0;

static void build_efs(void) {
    g_nefs = 0;
    struct ef_file* f;
    // EF_ICCID 0x2FE2
    f = &g_efs[g_nefs++];
    f->id = 0x2FE2;
    f->size = ef_iccid(f->data);
    // EF_SPN 0x6F46: display condition 0x01 + name, 0xFF padded, 17 bytes
    f = &g_efs[g_nefs++];
    f->id = 0x6F46;
    memset(f->data, 0xFF, 17);
    f->data[0] = 0x01;
    memcpy(f->data + 1, P_OPL, strlen(P_OPL) < 16 ? strlen(P_OPL) : 16);
    f->size = 17;
    // EF_AD 0x6FAD: byte 4 = MNC length (2 for 46000)
    f = &g_efs[g_nefs++];
    f->id = 0x6FAD;
    memset(f->data, 0, 4);
    f->data[3] = (unsigned char)(strlen(P_OPN) - 3);  // "46000" -> MNC len 2
    f->size = 4;
    // EF_SST 0x6F38: SIM service table, most services activated
    f = &g_efs[g_nefs++];
    f->id = 0x6F38;
    memset(f->data, 0xFF, 16);
    f->size = 16;
    // EF_GID1 0x6F3E
    f = &g_efs[g_nefs++];
    f->id = 0x6F3E;
    memset(f->data, 0xFF, 8);
    f->size = 8;
}

static struct ef_file* find_ef(int id) {
    for (int i = 0; i < g_nefs; i++)
        if (g_efs[i].id == id) return &g_efs[i];
    return NULL;
}

// MSISDN record (EF_MSISDN 0x6F40), 34 bytes: 20 alpha + 14 fixed tail.
static int ef_msisdn_record(unsigned char* out) {
    memset(out, 0xFF, 34);
    memcpy(out, "Line 1", 6);
    unsigned char* t = out + 20;
    // BCD of the number, TON/NPI international (0x91)
    const char* num = P_MSISDN;
    int ndig = (int)strlen(num);
    int nbcd = (ndig + 1) / 2;
    t[0] = (unsigned char)(1 + nbcd);  // length: TON/NPI byte + BCD bytes
    t[1] = 0x91;
    for (int i = 0; i < nbcd; i++) {
        int lo = num[2 * i] - '0';
        int hi = (2 * i + 1 < ndig) ? num[2 * i + 1] - '0' : 0xF;
        t[2 + i] = (unsigned char)((hi << 4) | lo);
    }
    // remaining tail bytes (capability / extension) stay 0xFF
    return 34;
}

// ---- AT channel ----------------------------------------------------------
static int g_fd = -1;

static char g_obuf[8192];
static size_t g_olen;
static int g_suppress_final;  // mid-compound: hold back this command's OK
static int g_aborted;         // an ERROR ended a compound chain

static void send_raw(const char* s) {  // queue response bytes
    size_t len = strlen(s);
    if (g_olen + len >= sizeof g_obuf) return;
    memcpy(g_obuf + g_olen, s, len);
    g_olen += len;
}

static void resp_flush(void) {
    size_t off = 0;
    while (off < g_olen) {
        ssize_t w = write(g_fd, g_obuf + off, g_olen - off);
        if (w <= 0) break;
        off += (size_t)w;
    }
    g_olen = 0;
}

static void sendf(const char* fmt, ...) {
    char buf[1024];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, sizeof buf, fmt, ap);
    va_end(ap);
    send_raw(buf);
}

static void ok(void) {
    if (!g_suppress_final) send_raw("\r\nOK\r\n");
}
static void err(void) {
    send_raw("\r\nERROR\r\n");
    g_aborted = 1;
}

static void hex_encode(const unsigned char* in, int n, char* out) {
    static const char* H = "0123456789ABCDEF";
    for (int i = 0; i < n; i++) {
        out[2 * i] = H[in[i] >> 4];
        out[2 * i + 1] = H[in[i] & 15];
    }
    out[2 * n] = 0;
}

// AT+CRSM=<ins>,<fileid>[,<p1>,<p2>[,<len>[,"<data>"]]]
static void handle_crsm(const char* args) {
    int ins = 0, fileid = 0, p1 = 0, p2 = 0, len = 0;
    char data[256] = "";
    int cnt = sscanf(args, "%d,%d,%d,%d,%d,\"%255[^\"]\"", &ins, &fileid, &p1,
                     &p2, &len, data);
    if (cnt < 2) {
        err();
        return;
    }
    char hex[160];
    switch (ins) {
        case 192: {  // GET RESPONSE: RFU(2) size(2) id(2) type(1) ...
            struct ef_file* f = find_ef(fileid);
            int size = (fileid == 0x6F40) ? 34 : (f ? f->size : 0);
            if (!f && fileid != 0x6F40) {
                send_raw("\r\n+CRSM: 148,4\r\n\r\nOK\r\n");
                return;
            }
            unsigned char gr[15];
            memset(gr, 0, sizeof gr);
            gr[2] = (unsigned char)(size >> 8);
            gr[3] = (unsigned char)size;
            gr[4] = (unsigned char)(fileid >> 8);
            gr[5] = (unsigned char)fileid;
            gr[6] = (fileid == 0x6F40) ? 3 : 2;  // record / transparent
            if (fileid == 0x6F40) gr[14] = 34;   // record length at byte 15
            hex_encode(gr, 15, hex);
            sendf("\r\n+CRSM: 144,0,\"%s\"\r\n\r\nOK\r\n", hex);
            return;
        }
        case 176: {  // READ BINARY offset=p1<<8|p2, length=len
            struct ef_file* f = find_ef(fileid);
            if (!f) {
                send_raw("\r\n+CRSM: 148,4\r\n\r\nOK\r\n");
                return;
            }
            int off = (p1 << 8) | p2;
            if (off >= f->size || len <= 0) {
                send_raw("\r\n+CRSM: 146,0\r\n\r\nOK\r\n");  // wrong length
                return;
            }
            if (off + len > f->size) len = f->size - off;
            hex_encode(f->data + off, len, hex);
            sendf("\r\n+CRSM: 144,0,\"%s\"\r\n\r\nOK\r\n", hex);
            return;
        }
        case 178: {  // READ RECORD recno=p1 (mode p2=4: absolute), length=len
            if (fileid != 0x6F40) {
                send_raw("\r\n+CRSM: 148,4\r\n\r\nOK\r\n");
                return;
            }
            unsigned char rec[34];
            int n = ef_msisdn_record(rec);
            if (len > 0 && len < n) n = len;
            hex_encode(rec, n, hex);
            sendf("\r\n+CRSM: 144,0,\"%s\"\r\n\r\nOK\r\n", hex);
            return;
        }
        case 214:  // UPDATE BINARY
        case 220:  // UPDATE RECORD
            send_raw("\r\n+CRSM: 144,0\r\n\r\nOK\r\n");
            return;
        case 242:  // STATUS
            send_raw("\r\n+CRSM: 144,0,\"\"\r\n\r\nOK\r\n");
            return;
        default:
            send_raw("\r\n+CRSM: 148,8\r\n\r\nOK\r\n");  // instruction not found
            return;
    }
}

static void dispatch(const char* c) {
    if (*c == 0 || strcasecmp(c, "Z") == 0) { ok(); return; }
    if (strncasecmp(c, "E0", 2) == 0 || strncasecmp(c, "E1", 2) == 0) {
        ok();
        return;
    }
    // --- identity
    if (strcasecmp(c, "+CGSN") == 0) { sendf("\r\n%s\r\n\r\nOK\r\n", P_IMEI); return; }
    if (strcasecmp(c, "+CIMI") == 0) { sendf("\r\n%s\r\n\r\nOK\r\n", P_IMSI); return; }
    if (strcasecmp(c, "+CGMI") == 0) { send_raw("\r\nredroid-l4\r\n\r\nOK\r\n"); return; }
    if (strcasecmp(c, "+CGMM") == 0) { send_raw("\r\nL4 Virtual Modem\r\n\r\nOK\r\n"); return; }
    if (strcasecmp(c, "+CGMR") == 0) { send_raw("\r\n1.0\r\n\r\nOK\r\n"); return; }
    // --- SIM / radio state
    if (strcasecmp(c, "+CPIN?") == 0) { send_raw("\r\n+CPIN: READY\r\n\r\nOK\r\n"); return; }
    if (strncasecmp(c, "+CPIN=", 6) == 0) { ok(); return; }
    if (strcasecmp(c, "+CFUN?") == 0) { sendf("\r\n+CFUN: %d\r\n\r\nOK\r\n", g_cfun); return; }
    if (strncasecmp(c, "+CFUN=", 6) == 0) {
        g_cfun = atoi(c + 6);
        ok();
        return;
    }
    if (strncasecmp(c, "+CRSM=", 6) == 0) { handle_crsm(c + 6); return; }
    if (strncasecmp(c, "+CGLA=", 6) == 0 || strncasecmp(c, "+CCHO=", 6) == 0 ||
        strncasecmp(c, "+CCHC=", 6) == 0) { err(); return; }  // no ISIM app
    // --- operator / registration
    if (strcasecmp(c, "+COPS?") == 0) {  // also used inside compound lines
        const char* v = g_cops_fmt == 2 ? P_OPN : g_cops_fmt == 1 ? P_OPS : P_OPL;
        if (g_cfun)
            sendf("\r\n+COPS: 0,%d,\"%s\",0\r\n", g_cops_fmt, v);
        else
            send_raw("\r\n+COPS: 0\r\n");
        ok();
        return;
    }
    if (strcasecmp(c, "+COPS=?") == 0) {
        sendf("\r\n+COPS: (2,\"%s\",\"%s\",\"%s\",0),,(0,1,2,3,4),(0,1,2)\r\n\r\nOK\r\n",
              P_OPL, P_OPS, P_OPN);
        return;
    }
    if (strncasecmp(c, "+COPS=", 6) == 0) {
        // Query format lives in the second field: reference-ril cycles it
        // via the compound AT+COPS=3,0;+COPS?;+COPS=3,1;+COPS?;...
        int mode = -1, fmt = -1;
        if (sscanf(c + 6, "%d,%d", &mode, &fmt) == 2 && fmt >= 0 && fmt <= 2)
            g_cops_fmt = fmt;
        ok();
        return;
    }
    if (strcasecmp(c, "+CREG?") == 0) {
        if (g_cfun)
            sendf("\r\n+CREG: %d,1,\"%s\",\"%s\",0\r\n\r\nOK\r\n", g_creg_n,
                  kLac, kCi);
        else
            sendf("\r\n+CREG: %d,0\r\n\r\nOK\r\n", g_creg_n);
        return;
    }
    if (strncasecmp(c, "+CREG=", 6) == 0) { g_creg_n = atoi(c + 6); ok(); return; }
    if (strcasecmp(c, "+CGREG?") == 0) {
        if (g_cfun)
            sendf("\r\n+CGREG: %d,1,\"%s\",\"%s\",0\r\n\r\nOK\r\n", g_cgreg_n,
                  kLac, kCi);
        else
            sendf("\r\n+CGREG: %d,0\r\n\r\nOK\r\n", g_cgreg_n);
        return;
    }
    if (strncasecmp(c, "+CGREG=", 7) == 0) { g_cgreg_n = atoi(c + 7); ok(); return; }
    if (strcasecmp(c, "+CEREG?") == 0) {
        sendf("\r\n+CEREG: %d,%d\r\n\r\nOK\r\n", g_creg_n, g_cfun ? 1 : 0);
        return;
    }
    if (strncasecmp(c, "+CEREG=", 7) == 0) { ok(); return; }
    if (strcasecmp(c, "+CSQ") == 0) {
        sendf("\r\n+CSQ: %d,99\r\n\r\nOK\r\n", P_RSSI);
        return;
    }
    // --- data context queries (no data calls in this milestone)
    if (strcasecmp(c, "+CGACT?") == 0) { send_raw("\r\n+CGACT: 1,0\r\n\r\nOK\r\n"); return; }
    if (strncasecmp(c, "+CGACT=", 7) == 0) { ok(); return; }
    if (strcasecmp(c, "+CGDCONT?") == 0) {
        send_raw("\r\n+CGDCONT: 1,\"IP\",\"cmnet\",\"0.0.0.0\",0,0\r\n\r\nOK\r\n");
        return;
    }
    if (strncasecmp(c, "+CGDCONT=", 8) == 0) { ok(); return; }
    if (strncasecmp(c, "+CGDATA", 7) == 0) { err(); return; }
    // --- calls: none in this milestone
    if (strcasecmp(c, "+CLCC") == 0) { ok(); return; }
    if (strncasecmp(c, "+CHLD", 5) == 0) { ok(); return; }
    if (strncasecmp(c, "D", 1) == 0 || strcasecmp(c, "A") == 0 ||
        strcasecmp(c, "H") == 0 || strncasecmp(c, "H0", 2) == 0) { err(); return; }
    // --- multimode probes: ERROR forces reference-ril's GSM fallback
    if (strncasecmp(c, "+CTEC", 5) == 0 || strncasecmp(c, "+WNAM", 5) == 0 ||
        strncasecmp(c, "+WRMP", 5) == 0) { err(); return; }
    // --- generic init / settings traffic: accept
    if (strncasecmp(c, "+CMEE=", 6) == 0 || strncasecmp(c, "+CSSN=", 6) == 0 ||
        strncasecmp(c, "+CCWA=", 6) == 0 || strncasecmp(c, "+CMOD=", 6) == 0 ||
        strncasecmp(c, "+CMUT=", 6) == 0 || strncasecmp(c, "+COLP=", 6) == 0 ||
        strncasecmp(c, "+CSCS=", 6) == 0 || strncasecmp(c, "+CGEREP=", 8) == 0 ||
        strncasecmp(c, "+CNMI=", 6) == 0 || strncasecmp(c, "+CNMA", 5) == 0 ||
        strncasecmp(c, "+CMGF=", 6) == 0 || strncasecmp(c, "+CUSD=", 6) == 0 ||
        strncasecmp(c, "+CGQREQ=", 8) == 0 || strncasecmp(c, "+CGQMIN=", 8) == 0 ||
        strncasecmp(c, "+VTS=", 5) == 0 || strncasecmp(c, "+CCSS=", 6) == 0) {
        ok();
        return;
    }
    if (strcasecmp(c, "+CCSS?") == 0) { send_raw("\r\n+CCSS: 0\r\n\r\nOK\r\n"); return; }
    if (strncasecmp(c, "+CSMS=", 6) == 0) {
        send_raw("\r\n+CSMS: 1,1,1\r\n\r\nOK\r\n");
        return;
    }
    if (strncasecmp(c, "+CMGS=", 6) == 0 || strncasecmp(c, "+CMGW=", 6) == 0 ||
        strncasecmp(c, "+CMGD=", 6) == 0) { err(); return; }  // SMS: next milestone
    err();
}

// One input line = one AT command, or a compound chain joined by ';'
// (reference-ril's getOperator sends exactly that:
//  AT+COPS=3,0;+COPS?;+COPS=3,1;+COPS?;+COPS=3,2;+COPS?).
// Intermediate final results are suppressed; an ERROR aborts the chain.
// (No command we answer carries ';' inside a quoted argument.)
static void handle_line(char* line) {
    while (*line == ' ' || *line == '\t') line++;
    if (!line[0]) return;
    g_olen = 0;
    g_aborted = 0;
    load_props();  // identity follows props, picked up on re-query
    build_efs();   // EF contents derive from props (ICCID/SPN/AD)
    char* seg = line;
    int first = 1;
    while (seg) {
        char* semi = strchr(seg, ';');
        if (semi) *semi = 0;
        g_suppress_final = (semi != NULL);
        if (first) {
            if (strncasecmp(seg, "AT", 2) != 0) { err(); break; }
            dispatch(seg + 2);
            first = 0;
        } else {
            while (*seg == ' ' || *seg == '\t') seg++;
            if (*seg) dispatch(seg);
        }
        if (g_aborted) break;
        seg = semi ? semi + 1 : NULL;
    }
    g_suppress_final = 0;
    resp_flush();
}

int main(int argc, char** argv) {
    int port = argc > 1 ? atoi(argv[1]) : 8901;
    build_efs();
    int srv = socket(AF_INET, SOCK_STREAM, 0);
    if (srv < 0) return 1;
    int one = 1;
    setsockopt(srv, SOL_SOCKET, SO_REUSEADDR, &one, sizeof one);
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    addr.sin_port = htons((unsigned short)port);
    if (bind(srv, (struct sockaddr*)&addr, sizeof addr) < 0) return 1;
    if (listen(srv, 1) < 0) return 1;
    fprintf(stderr, "l4-modemd listening on 127.0.0.1:%d\n", port);
    for (;;) {
        g_fd = accept(srv, NULL, NULL);
        if (g_fd < 0) continue;
        char line[1024];
        int n = 0;
        char ch;
        ssize_t r;
        while ((r = read(g_fd, &ch, 1)) > 0) {
            if (ch == '\r' || ch == '\n') {
                if (n > 0) {
                    line[n] = 0;
                    handle_line(line);
                    n = 0;
                }
            } else if (n < (int)sizeof(line) - 1) {
                line[n++] = ch;
            }
        }
        close(g_fd);
        g_fd = -1;
    }
    return 0;
}
