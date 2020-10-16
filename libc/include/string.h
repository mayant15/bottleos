/**
 * @file string.h
 * @brief String manipulation utilities for the C library
 */

#ifndef _STRING_H
#define _STRING_H

#include <sys/cdefs.h>
#include <stddef.h>

// If building with C++, we want C linkage here
#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief Compare two memory locations, byte-by-byte
     * 
     * @param a_ptr Pointer to the first location
     * @param b_ptr Pointer to the second location
     * @param size  Number of bytes to compare
     * @return int  Returns signum(a/b - 1)
     */
    int memcmp(const void *a_ptr, const void *b_ptr, size_t size);

    /**
     * @brief Copies values from a source to the destination directly.
     * 
     * @attention If the source and the destination overlap, some bytes in 
     * the source may be overwritten before they are copied. Use memmove() 
     * in that case instead of memcpy().
     * 
     * @param dest_ptr Pointer to the destination location
     * @param src_ptr  Pointer to the source location
     * @param size     Number of bytes to copy
     * @return void*   Pointer to the source location
     */
    void *memcpy(void *__restrict dest_ptr, const void *__restrict src_ptr, size_t size);

    /**
     * @brief Copies values from a source to the destination, as if
     * a buffer was used in between, allowing overlap.
     * 
     * @param dest_ptr Pointer to the destination memory block
     * @param src_ptr  Pointer to the source memory block
     * @param size     Number of bytes to copy
     * @return void*   Pointer to the destination block, with the bytes copied
     */
    void *memmove(void *dest_ptr, const void *src_ptr, size_t size);

    /**
     * @brief Set a given location to a value
     * 
     * @param buf_ptr Pointer to the start of the location that is to be set
     * @param value   Value to be set in the provided location
     * @param size    Number of bytes to be set
     * @return void*  Pointer to the start of the location that was set
     */
    void *memset(void *buf_ptr, int value, size_t size);

    /**
     * @brief Calculate the length of a string
     * 
     * @param str     Input string
     * @return size_t Length of the input string
     */
    size_t strlen(const char * str);

#ifdef __cplusplus
}
#endif

#endif
