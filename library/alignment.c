#include "alignment.h"

uint16_t mbedtls_get_unaligned_uint16(const void *p)
{
    uint16_t r;
#if defined(UINT_UNALIGNED)
    mbedtls_uint16_unaligned_t *p16 = (mbedtls_uint16_unaligned_t *) p;
    r = *p16;
#elif defined(UINT_UNALIGNED_STRUCT)
    mbedtls_uint16_unaligned_t *p16 = (mbedtls_uint16_unaligned_t *) p;
    r = p16->x;
#else
    memcpy(&r, p, sizeof(r));
#endif
    return r;
}

void mbedtls_put_unaligned_uint16(void *p, uint16_t x)
{
#if defined(UINT_UNALIGNED)
    mbedtls_uint16_unaligned_t *p16 = (mbedtls_uint16_unaligned_t *) p;
    *p16 = x;
#elif defined(UINT_UNALIGNED_STRUCT)
    mbedtls_uint16_unaligned_t *p16 = (mbedtls_uint16_unaligned_t *) p;
    p16->x = x;
#else
    memcpy(p, &x, sizeof(x));
#endif
}

uint32_t mbedtls_get_unaligned_uint32(const void *p)
{
    uint32_t r;
#if defined(UINT_UNALIGNED)
    mbedtls_uint32_unaligned_t *p32 = (mbedtls_uint32_unaligned_t *) p;
    r = *p32;
#elif defined(UINT_UNALIGNED_STRUCT)
    mbedtls_uint32_unaligned_t *p32 = (mbedtls_uint32_unaligned_t *) p;
    r = p32->x;
#else
    memcpy(&r, p, sizeof(r));
#endif
    return r;
}

void mbedtls_put_unaligned_uint32(void *p, uint32_t x)
{
#if defined(UINT_UNALIGNED)
    mbedtls_uint32_unaligned_t *p32 = (mbedtls_uint32_unaligned_t *) p;
    *p32 = x;
#elif defined(UINT_UNALIGNED_STRUCT)
    mbedtls_uint32_unaligned_t *p32 = (mbedtls_uint32_unaligned_t *) p;
    p32->x = x;
#else
    memcpy(p, &x, sizeof(x));
#endif
}

uint64_t mbedtls_get_unaligned_uint64(const void *p)
{
    uint64_t r;
#if defined(UINT_UNALIGNED)
    mbedtls_uint64_unaligned_t *p64 = (mbedtls_uint64_unaligned_t *) p;
    r = *p64;
#elif defined(UINT_UNALIGNED_STRUCT)
    mbedtls_uint64_unaligned_t *p64 = (mbedtls_uint64_unaligned_t *) p;
    r = p64->x;
#else
    memcpy(&r, p, sizeof(r));
#endif
    return r;
}

void mbedtls_put_unaligned_uint64(void *p, uint64_t x)
{
#if defined(UINT_UNALIGNED)
    mbedtls_uint64_unaligned_t *p64 = (mbedtls_uint64_unaligned_t *) p;
    *p64 = x;
#elif defined(UINT_UNALIGNED_STRUCT)
    mbedtls_uint64_unaligned_t *p64 = (mbedtls_uint64_unaligned_t *) p;
    p64->x = x;
#else
    memcpy(p, &x, sizeof(x));
#endif
}