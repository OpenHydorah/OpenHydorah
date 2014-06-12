/*-*- mode:C; -*- */
/* config.h.  Generated from build/cmake/config.h.in by cmake configure */
/*
 * Check: a unit test framework for C
 *
 * Copyright (C) 2011 Mateusz Loskot
 * Copyright (C) 2001, 2002 Arien Malec
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#if defined(__osf__)
# define _OSF_SOURCE
#endif

/*
 * Ensure we have C99-style int64_t, etc, all defined.
 */

/* First, we need to know if the system has already defined them. */
#define HAVE_INT16_T
#define HAVE_INT32_T
#define HAVE_INT64_T
#define HAVE_INTMAX_T

#define HAVE_UINT8_T
#define HAVE_UINT16_T
#define HAVE_UINT32_T
#define HAVE_UINT64_T
#define HAVE_UINTMAX_T

/* We might have the types we want under other spellings. */
/* #undef HAVE___INT64 */
/* #undef HAVE_U_INT64_T */
/* #undef HAVE_UNSIGNED___INT64 */

/* The sizes of various standard integer types. */
#define SIZE_OF_SHORT 2
#define SIZE_OF_INT 4
#define SIZE_OF_LONG 8
#define SIZE_OF_LONG_LONG 8
#define SIZE_OF_UNSIGNED_SHORT 2
#define SIZE_OF_UNSIGNED 4
#define SIZE_OF_UNSIGNED_LONG 8
#define SIZE_OF_UNSIGNED_LONG_LONG 8

/*
 * If we lack int64_t, define it to the first of __int64, int, long, and long long
 * that exists and is the right size.
 */
#if !defined(HAVE_INT64_T) && defined(HAVE___INT64)
typedef __int64 int64_t;
#define HAVE_INT64_T
#endif

#if !defined(HAVE_INT64_T) && SIZE_OF_INT == 8
typedef int int64_t;
#define HAVE_INT64_T
#endif

#if !defined(HAVE_INT64_T) && SIZE_OF_LONG == 8
typedef long int64_t;
#define HAVE_INT64_T
#endif

#if !defined(HAVE_INT64_T) && SIZE_OF_LONG_LONG == 8
typedef long long int64_t;
#define HAVE_INT64_T
#endif

#if !defined(HAVE_INT64_T)
#error No 64-bit integer type was found.
#endif

/*
 * Similarly for int32_t
 */
#if !defined(HAVE_INT32_T) && SIZE_OF_INT == 4
typedef long int32_t;
#define HAVE_INT32_T
#endif

#if !defined(HAVE_INT32_T) && SIZE_OF_LONG == 4
typedef long int32_t;
#define HAVE_INT32_T
#endif

#if !defined(HAVE_INT32_T)
#error No 32-bit integer type was found.
#endif

/*
 * Similarly for int16_t
 */
#if !defined(HAVE_INT16_T) && SIZE_OF_INT == 2
typedef int int16_t;
#define HAVE_INT16_T
#endif

#if !defined(HAVE_INT16_T) && SIZE_OF_SHORT == 2
typedef short int16_t;
#define HAVE_INT16_T
#endif

#if !defined(HAVE_INT16_T)
#error No 16-bit integer type was found.
#endif

/*
 * Similarly for uint64_t
 */
#if !defined(HAVE_UINT64_T) && defined(HAVE_UNSIGNED___INT64)
typedef unsigned __int64 uint64_t;
#define HAVE_UINT64_T
#endif

#if !defined(HAVE_UINT64_T) && SIZE_OF_UNSIGNED == 8
typedef unsigned uint64_t;
#define HAVE_UINT64_T
#endif

#if !defined(HAVE_UINT64_T) && SIZE_OF_UNSIGNED_LONG == 8
typedef unsigned long uint64_t;
#define HAVE_UINT64_T
#endif

#if !defined(HAVE_UINT64_T) && SIZE_OF_UNSIGNED_LONG_LONG == 8
typedef unsigned long long uint64_t;
#define HAVE_UINT64_T
#endif

#if !defined(HAVE_UINT64_T)
#error No 64-bit unsigned integer type was found.
#endif


/*
 * Similarly for uint32_t
 */
#if !defined(HAVE_UINT32_T) && SIZE_OF_UNSIGNED == 4
typedef unsigned uint32_t;
#define HAVE_UINT32_T
#endif

#if !defined(HAVE_UINT32_T) && SIZE_OF_UNSIGNED_LONG == 4
typedef unsigned long uint32_t;
#define HAVE_UINT32_T
#endif

#if !defined(HAVE_UINT32_T)
#error No 32-bit unsigned integer type was found.
#endif

/*
 * Similarly for uint16_t
 */
#if !defined(HAVE_UINT16_T) && SIZE_OF_UNSIGNED == 2
typedef unsigned uint16_t;
#define HAVE_UINT16_T
#endif

#if !defined(HAVE_UINT16_T) && SIZE_OF_UNSIGNED_SHORT == 2
typedef unsigned short uint16_t;
#define HAVE_UINT16_T
#endif

#if !defined(HAVE_UINT16_T)
#error No 16-bit unsigned integer type was found.
#endif

/*
 * Similarly for uint8_t
 */
#if !defined(HAVE_UINT8_T)
typedef unsigned char uint8_t;
#define HAVE_UINT8_T
#endif

#if !defined(HAVE_UINT16_T)
#error No 8-bit unsigned integer type was found.
#endif

/* Define intmax_t and uintmax_t if they are not already defined. */
#if !defined(HAVE_INTMAX_T)
typedef int64_t intmax_t;
#define INTMAX_MIN INT64_MIN
#define INTMAX_MAX INT64_MAX
#endif

#if !defined(HAVE_UINTMAX_T)
typedef uint64_t uintmax_t;
#endif

/* Define to 1 if you have the declaration of `INT64_MAX', and to 0 if you
   don't. */
/* #undef HAVE_DECL_INT64_MAX */

/* Define to 1 if you have the declaration of `INT64_MIN', and to 0 if you
   don't. */
/* #undef HAVE_DECL_INT64_MIN */

/* Define to 1 if you have the declaration of `SIZE_MAX', and to 0 if you
   don't. */
/* #undef HAVE_DECL_SIZE_MAX */

/* Define to 1 if you have the declaration of `SSIZE_MAX', and to 0 if you
   don't. */
/* #undef HAVE_DECL_SSIZE_MAX */

/* Define to 1 if you have the declaration of `UINT32_MAX', and to 0 if you
   don't. */
/* #undef HAVE_DECL_UINT32_MAX */

/* Define to 1 if you have the declaration of `UINT64_MAX', and to 0 if you
   don't. */
/* #undef HAVE_DECL_UINT64_MAX */

/* Define to 1 if you have the <errno.h> header file. */
#define HAVE_ERRNO_H 1

/* Define to 1 if you have the `fork' function. */
#define HAVE_FORK 1

/* Define to 1 if you have the `getpid' function. */
#define HAVE_GETPID 1

/* Define to 1 if you have the `gettimeofday' function. */
#define HAVE_GETTIMEOFDAY 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the <limits.h> header file. */
#define HAVE_LIMITS_H 1

/* Define to 1 if you have the `localtime_r' function. */
#define HAVE_DECL_LOCALTIME_R 1

/* Define to 1 if you have the `localtime_s' function. */
/* #undef HAVE_LOCALTIME_S */

/* Define to 1 if the system has the type `long long int'. */
#define HAVE_LONG_LONG_INT 1

/* Define to 1 if you have the `malloc' function. */
#define HAVE_MALLOC 1

/* Define to 1 if you have the `realloc' function. */
#define HAVE_REALLOC 1

/* Define to 1 if you have the `setenv' function. */
#define HAVE_DECL_SETENV 1

/* Define to 1 if you have the <signal.h> header file. */
#define HAVE_SIGNAL_H 1

/* Define to 1 if you have the 'sigaction' function. */
#define HAVE_SIGACTION 1

/* Define to 1 if you have the <stdarg.h> header file. */
#define HAVE_STDARG_H 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the `strdup' function. */
#define HAVE_DECL_STRDUP 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the `strsignal' function. */
#define HAVE_DECL_STRSIGNAL 1

/* Define to 1 if you have the <sys/time.h> header file. */
#define HAVE_SYS_TIME_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <time.h> header file. */
#define HAVE_TIME_H 1

/* Define to 1 if the system has the type `unsigned long long'. */
/* #undef HAVE_UNSIGNED_LONG_LONG */

/* Define to 1 if the system has the type `unsigned long long int'. */
/* #undef HAVE_UNSIGNED_LONG_LONG_INT */

/* Define to 1 if the system has the type `wchar_t'. */
/* #undef HAVE_WCHAR_T */

/* Define to 1 if you have the `_getpid' function. */
/* #undef HAVE__GETPID */

/* Define to 1 if you have the `_localtime64_s' function. */
/* #undef HAVE__LOCALTIME64_S */

/* Define to 1 if you have the `_strdup' function. */
/* #undef HAVE__STRDUP */

/* Version number of Check */
#define CHECK_VERSION "0.9.13"

/* The size of `wchar_t', as computed by sizeof. */
/* #undef SIZEOF_WCHAR_T */

/* Define to 1 if strerror_r returns char *. */
/* #undef STRERROR_R_CHAR_P */

/* Define to 1 if you can safely include both <sys/time.h> and <time.h>. */
/* #undef TIME_WITH_SYS_TIME */

/*
 * Some platform requires a macro to use extension functions.
 */
/* #undef SAFE_TO_DEFINE_EXTENSIONS */
#ifdef SAFE_TO_DEFINE_EXTENSIONS
/* Enable extensions on AIX 3, Interix.  */
#ifndef _ALL_SOURCE
# define _ALL_SOURCE 1
#endif
/* Enable GNU extensions on systems that have them.  */
#ifndef _GNU_SOURCE
# define _GNU_SOURCE 1
#endif
/* Enable threading extensions on Solaris.  */
#ifndef _POSIX_PTHREAD_SEMANTICS
# define _POSIX_PTHREAD_SEMANTICS 1
#endif
/* Enable extensions on HP NonStop.  */
#ifndef _TANDEM_SOURCE
# define _TANDEM_SOURCE 1
#endif
/* Enable general extensions on Solaris.  */
#ifndef __EXTENSIONS__
# define __EXTENSIONS__ 1
#endif
#endif /* SAFE_TO_DEFINE_EXTENSIONS */

/* Number of bits in a file offset, on hosts where this is settable. */
/* #undef _FILE_OFFSET_BITS */

/* Define to 1 to make fseeko visible on some hosts (e.g. glibc 2.2). */
/* #undef _LARGEFILE_SOURCE */

/* Define for large files, on AIX-style hosts. */
/* #undef _LARGE_FILES */

/* Define for Windows to use Windows 2000+ APIs. */
/* #undef _WIN32_WINNT */
/* #undef WINVER */

/* Define to empty if `const' does not conform to ANSI C. */
/* #undef const */

/* Define to `int' if <sys/types.h> doesn't define. */
/* #undef clockid_t */

/* Define to `int' if <sys/types.h> doesn't define. */
/* #undef gid_t */

/* Define to `unsigned long' if <sys/types.h> does not define. */
/* #undef id_t */

/* Define to `int' if <sys/types.h> does not define. */
/* #undef mode_t */

/* Define to `long long' if <sys/types.h> does not define. */
/* #undef off_t */

/* Define to `int' if <sys/types.h> doesn't define. */
/* #undef pid_t */

/* Define to `unsigned int' if <sys/types.h> does not define. */
/* #undef size_t */

/* Define to `int' if <sys/types.h> does not define. */
/* #undef ssize_t */

/* Define to `int' if <sys/types.h> does not define. */
/* #undef timer_t */

/* Define to `int' if <sys/types.h> doesn't define. */
/* #undef uid_t */

/* Define to `int' if <sys/types.h> does not define. */
/* #undef intptr_t */

/* Define to `unsigned int' if <sys/types.h> does not define. */
/* #undef uintptr_t */
