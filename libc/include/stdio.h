/**
 * @file stdio.h
 * @brief Defines functions useful for I/O with stdin/stdout
 */

#ifndef _STDIO_H
#define _STDIO_H

#include <sys/cdefs.h>

/** @brief End-of-file character */
#define EOF (-1)

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief Write something to stdout
     * 
     * @param format Format string for the text to be written
     * @param ...    Arguments to be replaced in the format string
     * @return int   Number of characters written
     */
    int printf(const char *__restrict format, ...);
    
    /**
     * @brief Print a character to stdout
     * 
     * @param ch   Data to be written
     * @return int Number of characters written
     */
    int putchar(int ch);

    /**
     * @brief Print a string to stdout
     * 
     * @param string Data to be written
     * @return int   Number of characters written
     */
    int puts(const char * string);

#ifdef __cplusplus
}
#endif

#endif