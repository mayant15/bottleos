#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>

/**
 * @brief Initialize the terminal display and fill it completely with ' '
 */
void terminal_initialize(void);

/**
 * @brief Add a character at the currently active coordinate
 */
void terminal_putchar(char c);

/**
 * @brief Write some data to the terminal
 */
void terminal_write(const char *data, size_t size);

/**
 * @brief Write a string to the terminal
 */
void terminal_write_string(const char *data);

#endif
