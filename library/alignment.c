#include "alignment.h"

uint16_t mbedtls_get_unaligned_uint16(const void *p)
{
    uint16_t r;
    memcpy(&r, p, sizeof(r));
    return r;
}

void mbedtls_put_unaligned_uint16(void *p, uint16_t x)
{
    memcpy(p, &x, sizeof(x));
}

uint32_t mbedtls_get_unaligned_uint32(const void *p)
{
    uint32_t r;
    memcpy(&r, p, sizeof(r));
    return r;
}

void mbedtls_put_unaligned_uint32(void *p, uint32_t x)
{
    memcpy(p, &x, sizeof(x));
}

uint64_t mbedtls_get_unaligned_uint64(const void *p)
{
    uint64_t r;
    memcpy(&r, p, sizeof(r));
    return r;
}

void mbedtls_put_unaligned_uint64(void *p, uint64_t x)
{
    memcpy(p, &x, sizeof(x));
}