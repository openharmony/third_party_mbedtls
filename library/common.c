#include "common.h"

void mbedtls_xor(unsigned char *r, const unsigned char *a, const unsigned char *b, size_t n)
{
    size_t i = 0;
#if defined(MBEDTLS_EFFICIENT_UNALIGNED_ACCESS)
#if defined(MBEDTLS_ARCH_IS_X64) || defined(MBEDTLS_ARCH_IS_ARM64)
    /* This codepath probably only makes sense on architectures with 64-bit registers */
    for (; (i + 8) <= n; i += 8) {
        uint64_t x = mbedtls_get_unaligned_uint64(a + i) ^ mbedtls_get_unaligned_uint64(b + i);
        mbedtls_put_unaligned_uint64(r + i, x);
    }
#if defined(__IAR_SYSTEMS_ICC__)
    /* This if statement helps some compilers (e.g., IAR) optimise out the byte-by-byte tail case
     * where n is a constant multiple of 8.
     * For other compilers (e.g. recent gcc and clang) it makes no difference if n is a compile-time
     * constant, and is a very small perf regression if n is not a compile-time constant. */
    if (n % 8 == 0) {
        return;
    }
#endif
#else
    for (; (i + 4) <= n; i += 4) {
        uint32_t x = mbedtls_get_unaligned_uint32(a + i) ^ mbedtls_get_unaligned_uint32(b + i);
        mbedtls_put_unaligned_uint32(r + i, x);
    }
#if defined(__IAR_SYSTEMS_ICC__)
    if (n % 4 == 0) {
        return;
    }
#endif
#endif
#endif
    for (; i < n; i++) {
        r[i] = a[i] ^ b[i];
    }
}

void mbedtls_xor_no_simd(unsigned char *r,
                         const unsigned char *a,
                         const unsigned char *b,
                         size_t n)
{
    size_t i = 0;
#if defined(MBEDTLS_EFFICIENT_UNALIGNED_ACCESS)
#if defined(MBEDTLS_ARCH_IS_X64) || defined(MBEDTLS_ARCH_IS_ARM64)
    /* This codepath probably only makes sense on architectures with 64-bit registers */
    for (; (i + 8) <= n; i += 8) {
        uint64_t x = mbedtls_get_unaligned_uint64(a + i) ^ mbedtls_get_unaligned_uint64(b + i);
        mbedtls_put_unaligned_uint64(r + i, x);
    }
#if defined(__IAR_SYSTEMS_ICC__)
    /* This if statement helps some compilers (e.g., IAR) optimise out the byte-by-byte tail case
     * where n is a constant multiple of 8.
     * For other compilers (e.g. recent gcc and clang) it makes no difference if n is a compile-time
     * constant, and is a very small perf regression if n is not a compile-time constant. */
    if (n % 8 == 0) {
        return;
    }
#endif
#else
    for (; (i + 4) <= n; i += 4) {
        uint32_t x = mbedtls_get_unaligned_uint32(a + i) ^ mbedtls_get_unaligned_uint32(b + i);
        mbedtls_put_unaligned_uint32(r + i, x);
    }
#if defined(__IAR_SYSTEMS_ICC__)
    if (n % 4 == 0) {
        return;
    }
#endif
#endif
#endif
    for (; i < n; i++) {
        r[i] = a[i] ^ b[i];
    }
}