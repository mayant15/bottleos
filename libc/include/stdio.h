#ifndef _STDIO_H
#define _STDIO_H 1

#include <sys/cdefs.h>

#define EOF (-1)

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief 
     * 
     * @param __restrict 
     * @param ... 
     * @return int 
     */
    int printf(const char *__restrict, ...);

    /**
     * @brief 
     * 
     * @return int 
     */
    int putchar(int);

    /**
     * @brief 
     * 
     * @return int 
     */
    int puts(const char *);

#ifdef __cplusplus
}
#endif

#endif