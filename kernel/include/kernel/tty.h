/**
 * @file tty.h
 * @brief Kernel interface for output terminals
 */

#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>

/** @brief Setup a VGA display and fill it completely with ' ' */
void terminal_initialize();

/**
 * @brief Output a character at the current position
 * 
 * @param c Character to write
 */
void terminal_putchar(char c);

/**
 * @brief Write the given data to the terminal
 * 
 * @param data Data that is to be written
 * @param size Size of the input data
 */
void terminal_write(const char *data, size_t size);

/**
 * @brief Write a given string to the terminal
 * 
 * @param data String that is to be written
 */
void terminal_write_string(const char *data);

#endif
