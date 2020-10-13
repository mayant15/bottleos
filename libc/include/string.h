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
     * @brief 
     * 
     * @return int 
     */
    int memcmp(const void *, const void *, size_t);

    /**
     * @brief Copies values from a source to the destination directly.
     * 
     * @attention If the source and the destination overlap, some bytes in 
     * the source may be overwritten before they are copied. Use memmove() 
     * in that case instead of memcpy().
     * 
     * @param __restrict 
     * @param __restrict 
     * @return void* 
     */
    void *memcpy(void *__restrict, const void *__restrict, size_t);

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
     * @brief 
     * 
     * @return void* 
     */
    void *memset(void *, int, size_t);

    /**
     * @brief Calculate the length of a string.
     * 
     * @return size_t 
     */
    size_t strlen(const char *);

#ifdef __cplusplus
}
#endif

#endif
