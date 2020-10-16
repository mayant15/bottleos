/**
 * @file stdlib.h
 * @brief Defined core features for the library
 */

#ifndef _STDLIB_H
#define _STDLIB_H

#include <sys/cdefs.h>

#ifdef __cplusplus
extern "C"
{
#endif

    /** @brief Terminate the process or initiate kernel panic */
    __attribute__((__noreturn__)) void abort();

#ifdef __cplusplus
}
#endif

#endif