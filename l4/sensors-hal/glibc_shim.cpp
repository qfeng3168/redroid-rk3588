// Shim for glibc-isms that leaked into the objects because the C headers
// came from the build container's glibc while the target libc is Bionic.
// Only three symbols were referenced: __assert_fail (glibc assert.h),
// __errno_location (glibc errno.h) and __isoc23_sscanf (glibc 2.38 stdio
// redirect for sscanf; our format strings use plain %f, vsscanf is exact).
// NOTE: this file must not include glibc <cstdio>/<cstdlib> — they would
// redirect vsscanf/abort right back to __isoc23_* names. Declare manually.
#include <cstdarg>

extern "C" {
int* __errno(void);  // Bionic errno accessor
int vsscanf(const char* str, const char* fmt, va_list ap);  // Bionic
[[noreturn]] void abort(void);                              // Bionic
void __android_log_print(int prio, const char* tag, const char* fmt, ...);

void __assert_fail(const char* assertion, const char* file, unsigned int line,
                   const char* function) {
    __android_log_print(7 /*ANDROID_LOG_FATAL*/, "sensors-shim",
                        "assert failed: %s (%s:%u, %s)", assertion, file, line,
                        function);
    abort();
}

int* __errno_location(void) { return __errno(); }

int __isoc23_sscanf(const char* str, const char* fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    int ret = vsscanf(str, fmt, ap);
    va_end(ap);
    return ret;
}
}  // extern "C"
