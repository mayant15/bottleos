#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>


#define MAX_DIGITS 32

static const char ALPHABET[] = "0123456789ABCDEF";
static char int_buf[MAX_DIGITS + 1];

static bool contiguous_print(const char *data, size_t length)
{
    const unsigned char *bytes = (const unsigned char *)data;
    for (size_t i = 0; i < length; i++)
    {
        if (putchar(bytes[i]) == EOF)
        {
            return false;
        }
    }
        
    return true;
}

// TODO: Support negative numbers
static char* itoa(unsigned int val, unsigned int base)
{
    if (base < 2 || base > 16)
    {
        return NULL;
    }

    int_buf[MAX_DIGITS] = '\0';
    if (val == 0)
    {
        int_buf[MAX_DIGITS - 1] = '0';
        return (int_buf + MAX_DIGITS - 1);
    }

    int len = 0;
    while (val != 0)
    {
        len++;
        int_buf[MAX_DIGITS - len] = ALPHABET[val % base];
        val = val / base;
    }

    if (base == 16)
    {
        int_buf[MAX_DIGITS - len - 1] = 'x';
        int_buf[MAX_DIGITS - len - 2] = '0';
        len += 2;
    }

    return (int_buf + MAX_DIGITS - len);
}

int printf(const char *__restrict format, ...)
{
    va_list parameters;
    va_start(parameters, format);

    int written = 0;
    while (format[0] != '\0')
    {
        long unsigned int maxrem = INT_MAX - written;

        // Handle % placeholders
        if (format[0] == '%')
        {
            format++;
            if (format[0] == '%')
            {
                if (maxrem < sizeof (char))
                {
                    // TODO: Buffer overflow
                    return -1;
                }

                if (putchar('%') == EOF)
                {
                    return -1;
                }

                format++;
                written++;
            }
            else if (format[0] == 'c')
            {
                if (maxrem < sizeof (char))
                {
                    // TODO: Buffer overflow
                    return -1;
                }

                char c = (char) va_arg(parameters, int);
                if (putchar(c) == EOF)
                {
                    return -1;
                }

                format++;
                written++;
            }
            else if (format[0] == 'd' || format[0] == 'X')
            {
                int d = va_arg(parameters, int);
                int base = (format[0] == 'd') ? 10 : 16;
                char* ch = itoa(d, base);
                if (ch == NULL)
                {
                    // TODO: Bad argument exception
                    return -1;
                }

                size_t len = MAX_DIGITS + int_buf - ch;
                if (maxrem < len)
                {
                    // TODO: Overflow
                    return -1;
                }

                if (!contiguous_print(ch, len))
                {
                    return -1;
                }

                written += len;
                format++;
            }
            else if (format[0] == 's')
            {
                const char *str = va_arg(parameters, const char *);
                size_t len = strlen(str);
                if (maxrem < len)
                {
                    // TODO: Set errno to EOVERFLOW.
                    return -1;
                }

                if (!contiguous_print(str, len))
                {
                    return -1;
                }

                written += len;
                format++;
            }
            else
            {
                // NOTE: Unknown % placeholders are silently ignored for now
                // TODO: Implement more parsing
                format++;
            }
        }
        else
        {
            if (maxrem < sizeof (char))
            {
                return -1;
            }

            if (putchar(*format) == EOF)
            {
                return -1;
            }

            format++;
            written++;
        }
    }

    va_end(parameters);
    return written;
}