/**
 * \file common.h
 *
 * \brief Utility macros for internal use in the library
 */
/*
 *  Copyright The Mbed TLS Contributors
 *  SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later
 */

#ifndef MBEDTLS_LIBRARY_COMMON_H
#define MBEDTLS_LIBRARY_COMMON_H

#include "mbedtls/build_info.h"
#include "alignment.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stddef.h>

#if defined(__ARM_NEON)
#include <arm_neon.h>
#define MBEDTLS_HAVE_NEON_INTRINSICS
#elif defined(MBEDTLS_PLATFORM_IS_WINDOWS_ON_ARM64)
#include <arm64_neon.h>
#define MBEDTLS_HAVE_NEON_INTRINSICS
#endif

/** Helper to define a function as static except when building invasive tests.
 *
 * If a function is only used inside its own source file and should be
 * declared `static` to allow the compiler to optimize for code size,
 * but that function has unit tests, define it with
 * ```
 * MBEDTLS_STATIC_TESTABLE int mbedtls_foo(...) { ... }
 * ```
 * and declare it in a header in the `library/` directory with
 * ```
 * #if defined(MBEDTLS_TEST_HOOKS)
 * int mbedtls_foo(...);
 * #endif
 * ```
 */
#if defined(MBEDTLS_TEST_HOOKS)
#define MBEDTLS_STATIC_TESTABLE
#else
#define MBEDTLS_STATIC_TESTABLE static
#endif

#if defined(MBEDTLS_TEST_HOOKS)
extern void (*mbedtls_test_hook_test_fail)(const char *test, int line, const char *file);
#define MBEDTLS_TEST_HOOK_TEST_ASSERT(TEST) \
    do { \
        if ((!(TEST)) && ((*mbedtls_test_hook_test_fail) != NULL)) \
        { \
            (*mbedtls_test_hook_test_fail)( #TEST, __LINE__, __FILE__); \
        } \
    } while (0)
#else
#define MBEDTLS_TEST_HOOK_TEST_ASSERT(TEST)
#endif /* defined(MBEDTLS_TEST_HOOKS) */

/** \def ARRAY_LENGTH
 * Return the number of elements of a static or stack array.
 *
 * \param array         A value of array (not pointer) type.
 *
 * \return The number of elements of the array.
 */
/* A correct implementation of ARRAY_LENGTH, but which silently gives
 * a nonsensical result if called with a pointer rather than an array. */
#define ARRAY_LENGTH_UNSAFE(array)            \
    (sizeof(array) / sizeof(*(array)))

#if defined(__GNUC__)
/* Test if arg and &(arg)[0] have the same type. This is true if arg is
 * an array but not if it's a pointer. */
#define IS_ARRAY_NOT_POINTER(arg)                                     \
    (!__builtin_types_compatible_p(__typeof__(arg),                \
                                   __typeof__(&(arg)[0])))
/* A compile-time constant with the value 0. If `const_expr` is not a
 * compile-time constant with a nonzero value, cause a compile-time error. */
#define STATIC_ASSERT_EXPR(const_expr)                                \
    (0 && sizeof(struct { unsigned int STATIC_ASSERT : 1 - 2 * !(const_expr); }))

/* Return the scalar value `value` (possibly promoted). This is a compile-time
 * constant if `value` is. `condition` must be a compile-time constant.
 * If `condition` is false, arrange to cause a compile-time error. */
#define STATIC_ASSERT_THEN_RETURN(condition, value)   \
    (STATIC_ASSERT_EXPR(condition) ? 0 : (value))

#define ARRAY_LENGTH(array)                                           \
    (STATIC_ASSERT_THEN_RETURN(IS_ARRAY_NOT_POINTER(array),         \
                               ARRAY_LENGTH_UNSAFE(array)))

#else
/* If we aren't sure the compiler supports our non-standard tricks,
 * fall back to the unsafe implementation. */
#define ARRAY_LENGTH(array) ARRAY_LENGTH_UNSAFE(array)
#endif
/** Allow library to access its structs' private members.
 *
 * Although structs defined in header files are publicly available,
 * their members are private and should not be accessed by the user.
 */
#define MBEDTLS_ALLOW_PRIVATE_ACCESS

/**
 * \brief       Securely zeroize a buffer then free it.
 *
 *              Similar to making consecutive calls to
 *              \c mbedtls_platform_zeroize() and \c mbedtls_free(), but has
 *              code size savings, and potential for optimisation in the future.
 *
 *              Guaranteed to be a no-op if \p buf is \c NULL and \p len is 0.
 *
 * \param buf   Buffer to be zeroized then freed.
 * \param len   Length of the buffer in bytes
 */
void mbedtls_zeroize_and_free(void *buf, size_t len);

/** Return an offset into a buffer.
 *
 * This is just the addition of an offset to a pointer, except that this
 * function also accepts an offset of 0 into a buffer whose pointer is null.
 * (`p + n` has undefined behavior when `p` is null, even when `n == 0`.
 * A null pointer is a valid buffer pointer when the size is 0, for example
 * as the result of `malloc(0)` on some platforms.)
 *
 * \param p     Pointer to a buffer of at least n bytes.
 *              This may be \p NULL if \p n is zero.
 * \param n     An offset in bytes.
 * \return      Pointer to offset \p n in the buffer \p p.
 *              Note that this is only a valid pointer if the size of the
 *              buffer is at least \p n + 1.
 */
static inline unsigned char *mbedtls_buffer_offset(
    unsigned char *p, size_t n)
{
    return p == NULL ? NULL : p + n;
}

/** Return an offset into a read-only buffer.
 *
 * Similar to mbedtls_buffer_offset(), but for const pointers.
 *
 * \param p     Pointer to a buffer of at least n bytes.
 *              This may be \p NULL if \p n is zero.
 * \param n     An offset in bytes.
 * \return      Pointer to offset \p n in the buffer \p p.
 *              Note that this is only a valid pointer if the size of the
 *              buffer is at least \p n + 1.
 */
static inline const unsigned char *mbedtls_buffer_offset_const(
    const unsigned char *p, size_t n)
{
    return p == NULL ? NULL : p + n;
}

void mbedtls_xor(unsigned char *r, const unsigned char *a, const unsigned char *b, size_t n);

void mbedtls_xor_no_simd(unsigned char *r,
                         const unsigned char *a,
                         const unsigned char *b,
                         size_t n);

/* Fix MSVC C99 compatible issue
 *      MSVC support __func__ from visual studio 2015( 1900 )
 *      Use MSVC predefine macro to avoid name check fail.
 */
#if (defined(_MSC_VER) && (_MSC_VER <= 1900))
#define /*no-check-names*/ __func__ __FUNCTION__
#endif

/* Define `asm` for compilers which don't define it. */
/* *INDENT-OFF* */
#ifndef asm
#if defined(__IAR_SYSTEMS_ICC__)
#define asm __asm
#else
#define asm __asm__
#endif
#endif
/* *INDENT-ON* */

/*
 * Define the constraint used for read-only pointer operands to aarch64 asm.
 *
 * This is normally the usual "r", but for aarch64_32 (aka ILP32,
 * as found in watchos), "p" is required to avoid warnings from clang.
 *
 * Note that clang does not recognise '+p' or '=p', and armclang
 * does not recognise 'p' at all. Therefore, to update a pointer from
 * aarch64 assembly, it is necessary to use something like:
 *
 * uintptr_t uptr = (uintptr_t) ptr;
 * asm( "ldr x4, [%x0], #8" ... : "+r" (uptr) : : )
 * ptr = (void*) uptr;
 *
 * Note that the "x" in "%x0" is neccessary; writing "%0" will cause warnings.
 */
#if defined(__aarch64__) && defined(MBEDTLS_HAVE_ASM)
#if UINTPTR_MAX == 0xfffffffful
/* ILP32: Specify the pointer operand slightly differently, as per #7787. */
#define MBEDTLS_ASM_AARCH64_PTR_CONSTRAINT "p"
#elif UINTPTR_MAX == 0xfffffffffffffffful
/* Normal case (64-bit pointers): use "r" as the constraint for pointer operands to asm */
#define MBEDTLS_ASM_AARCH64_PTR_CONSTRAINT "r"
#else
#error "Unrecognised pointer size for aarch64"
#endif
#endif

/* Always provide a static assert macro, so it can be used unconditionally.
 * It will expand to nothing on some systems.
 * Can be used outside functions (but don't add a trailing ';' in that case:
 * the semicolon is included here to avoid triggering -Wextra-semi when
 * MBEDTLS_STATIC_ASSERT() expands to nothing).
 * Can't use the C11-style `defined(static_assert)` on FreeBSD, since it
 * defines static_assert even with -std=c99, but then complains about it.
 */
#if defined(static_assert) && !defined(__FreeBSD__)
#define MBEDTLS_STATIC_ASSERT(expr, msg)    static_assert(expr, msg);
#else
#define MBEDTLS_STATIC_ASSERT(expr, msg)
#endif

#if defined(__has_builtin)
#define MBEDTLS_HAS_BUILTIN(x) __has_builtin(x)
#else
#define MBEDTLS_HAS_BUILTIN(x) 0
#endif

/* Define compiler branch hints */
#if MBEDTLS_HAS_BUILTIN(__builtin_expect)
#define MBEDTLS_LIKELY(x)       __builtin_expect(!!(x), 1)
#define MBEDTLS_UNLIKELY(x)     __builtin_expect(!!(x), 0)
#else
#define MBEDTLS_LIKELY(x)       x
#define MBEDTLS_UNLIKELY(x)     x
#endif

/* MBEDTLS_ASSUME may be used to provide additional information to the compiler
 * which can result in smaller code-size. */
#if MBEDTLS_HAS_BUILTIN(__builtin_assume)
/* clang provides __builtin_assume */
#define MBEDTLS_ASSUME(x)       __builtin_assume(x)
#elif MBEDTLS_HAS_BUILTIN(__builtin_unreachable)
/* gcc and IAR can use __builtin_unreachable */
#define MBEDTLS_ASSUME(x)       do { if (!(x)) __builtin_unreachable(); } while (0)
#elif defined(_MSC_VER)
/* Supported by MSVC since VS 2005 */
#define MBEDTLS_ASSUME(x)       __assume(x)
#else
#define MBEDTLS_ASSUME(x)       do { } while (0)
#endif

/* For gcc -Os, override with -O2 for a given function.
 *
 * This will not affect behaviour for other optimisation settings, e.g. -O0.
 */
#if defined(MBEDTLS_COMPILER_IS_GCC) && defined(__OPTIMIZE_SIZE__)
#define MBEDTLS_OPTIMIZE_FOR_PERFORMANCE __attribute__((optimize("-O2")))
#else
#define MBEDTLS_OPTIMIZE_FOR_PERFORMANCE
#endif

/* Suppress compiler warnings for unused functions and variables. */
#if !defined(MBEDTLS_MAYBE_UNUSED) && defined(__has_attribute)
#    if __has_attribute(unused)
#        define MBEDTLS_MAYBE_UNUSED __attribute__((unused))
#    endif
#endif
#if !defined(MBEDTLS_MAYBE_UNUSED) && defined(__GNUC__)
#    define MBEDTLS_MAYBE_UNUSED __attribute__((unused))
#endif
#if !defined(MBEDTLS_MAYBE_UNUSED) && defined(__IAR_SYSTEMS_ICC__) && defined(__VER__)
/* IAR does support __attribute__((unused)), but only if the -e flag (extended language support)
 * is given; the pragma always works.
 * Unfortunately the pragma affects the rest of the file where it is used, but this is harmless.
 * Check for version 5.2 or later - this pragma may be supported by earlier versions, but I wasn't
 * able to find documentation).
 */
#    if (__VER__ >= 5020000)
#        define MBEDTLS_MAYBE_UNUSED _Pragma("diag_suppress=Pe177")
#    endif
#endif
#if !defined(MBEDTLS_MAYBE_UNUSED) && defined(_MSC_VER)
#    define MBEDTLS_MAYBE_UNUSED __pragma(warning(suppress:4189))
#endif
#if !defined(MBEDTLS_MAYBE_UNUSED)
#    define MBEDTLS_MAYBE_UNUSED
#endif

#endif /* MBEDTLS_LIBRARY_COMMON_H */
