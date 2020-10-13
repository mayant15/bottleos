#include <string.h>

void *memcpy(void *__restrict dest_ptr, const void *__restrict src_ptr, size_t size)
{
    unsigned char *dest = (unsigned char *)dest_ptr;
    const unsigned char *src = (const unsigned char *)src_ptr;
    for (size_t i = 0; i < size; i++)
    {
        dest[i] = src[i];
    }
    return dest_ptr;
}
