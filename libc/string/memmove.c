#include <string.h>

void* memmove(void* dest_ptr, const void* src_ptr, size_t size)
{
    unsigned char* dest = (unsigned char*) dest_ptr;
    const unsigned char* src = (const unsigned char*) src_ptr;

    // If the destination is before the source, start copying from
    // the start. Otherwise, we need to start copying from the back
    // to avoid overwriting the source.
    if (dest < src)
    {
        for (size_t i = 0; i < size; i++)
        {
            dest[i] = src[i];
        }
    }
    else
    {
        for (size_t i = size; i != 0; i--)
        {
            dest[i - 1] = src[i - 1];
        }
    }

    return dest_ptr;
}
