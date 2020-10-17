/**
 * @file tty.c
 * @brief Implementation of kernel/tty.h for VGA devices
 */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/tty.h>

#include "vga.h"

/** @brief Width of the VGA display */
static const size_t VGA_WIDTH = 80;

/** @brief Height of the VGA display */
static const size_t VGA_HEIGHT = 25;

/** @brief Pointer to where the terminal buffer should start */
static uint16_t *const VGA_MEMORY = (uint16_t *)0xB8000;

/** @brief Currently active terminal row */
static size_t terminal_row;

/** @brief Currently active terminal column */
static size_t terminal_column;

/** @brief 8-bit VGA color information for the currently active color */
static uint8_t terminal_color;

/** @brief Pointer to the active terminal buffer */
static uint16_t *terminal_buffer;

/**
 * @brief Set the active terminal color
 * 
 * @param color A VGA color byte
 */
void terminal_setcolor(uint8_t color)
{
    terminal_color = color;
}

/**
 * @brief Put a character at the specified coordinate
 * 
 * @param c     Character to write
 * @param color VGA color byte to use
 * @param x     Horizontal position to place the character at
 * @param y     Vertical position to place the character at
 */
void terminal_putentry_at(unsigned char c, uint8_t color, size_t x, size_t y)
{
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = vga_entry(c, color);
}

void terminal_initialize(void)
{
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    terminal_buffer = VGA_MEMORY;
    for (size_t y = 0; y < VGA_HEIGHT; y++)
    {
        for (size_t x = 0; x < VGA_WIDTH; x++)
        {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }
}

void terminal_putchar(char c)
{
    unsigned char uc = c;
    if (uc == '\n')
    {
        terminal_column = 0;
        if (++terminal_row == VGA_HEIGHT)
        {
            terminal_row = 0;
        }
    }

    terminal_putentry_at(uc, terminal_color, terminal_column, terminal_row);
    if (++terminal_column == VGA_WIDTH)
    {
        terminal_column = 0;
        if (++terminal_row == VGA_HEIGHT)
            terminal_row = 0;
    }
}

void terminal_write(const char *data, size_t size)
{
    for (size_t i = 0; i < size; i++)
        terminal_putchar(data[i]);
}

void terminal_write_string(const char *data)
{
    terminal_write(data, strlen(data));
}
