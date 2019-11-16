#include <stddef.h>
#include <stdint.h>
#include "string.h"

#ifndef CONSOLE_H
#define CONSOLE_H

/**
 * Hardware text mode colour constants.
 *
 * @var enum
 */
enum vga_color
{
    COLOR_BLACK = 0,
	COLOR_BLUE = 1,
	COLOR_GREEN = 2,
	COLOR_CYAN = 3,
	COLOR_RED = 4,
	COLOR_MAGENTA = 5,
	COLOR_BROWN = 6,
	COLOR_LIGHT_GREY = 7,
	COLOR_DARK_GREY = 8,
	COLOR_LIGHT_BLUE = 9,
	COLOR_LIGHT_GREEN = 10,
	COLOR_LIGHT_CYAN = 11,
	COLOR_LIGHT_RED = 12,
	COLOR_LIGHT_MAGENTA = 13,
	COLOR_LIGHT_BROWN = 14,
	COLOR_WHITE = 15,
};

class Console
{
private:
    /**
     * The current row of the consoles cursor.
     */
    size_t row;

    /**
     * The current column of the consoles cursor.
     */
    size_t column;

    /**
     * The current colour of the console.
     */
    uint8_t color;

    /**
     * The consoles buffer.
     */
    uint16_t* buffer;

    /**
     * Generates a colour from the foreground and background.
     *
     * @param fg The foreground colour.
     * @param bg The background colour.
     *
     * @return The combined colour.
     */
    uint8_t makeColor(enum vga_color fg, enum vga_color bg)
    {
        return fg | bg << 4;
    }

    /**
     * Combines the colour with the character so we can output it
     * to the screen.
     *
     * @param c The character to colourize.
     * @param color The colour to set the character to.
     *
     * @return The colourized character.
     */
    uint16_t makeVgaEntry(char c, uint8_t color)
    {
        uint16_t c16 = c;
        uint16_t color16 = color;

        return c16 | color16 << 8;
    }

protected:
    /**
     * The width of the console window in columns.
     */
    static const size_t VGA_WIDTH = 80;

    /**
     * The height of the console window in rows.
     */
    static const size_t VGA_HEIGHT = 24;

    /**
     * The the cursors index at position x, y.
     *
     * @param x The 'x' coordinate.
     * @param y  The 'y' coordinate.
     *
     * @return The index for the cursor.
     */
    size_t getIndex(size_t x, size_t y)
    {
        return y * VGA_WIDTH + x;
    }

public:
    /**
     * Initialize the console by clearing it.
     */
    Console()
    {
        clear();
    }

    /**
     * Clear the current console window.
     */
    void clear()
    {
        row = 0;
        column = 0;
        color = makeColor(COLOR_LIGHT_GREY, COLOR_BLACK);
        buffer = (uint16_t*) 0xB8000;

        for (size_t y = 0; y < VGA_HEIGHT; y++)
        {
            for (size_t x = 0; x < VGA_WIDTH; x++)
            {
                putCharAt(' ', x, y, color);
            }
        }
    }

    /**
     * Set the current colour of the console window.
     *
     * @param c The new colour.
     */
    void setColor(uint8_t c)
    {
        color = c;
    }

    /**
     * Put a character at the given position.
     *
     * @param c The character to put.
     * @param x The 'x' coordinate of the character.
     * @param y The 'y' coordinate of the character.
     */
    void putCharAt(char c, size_t x, size_t y)
    {
        putCharAt(c, x, y, color);
    }

    /**
     * Put a character at the given position with a colour.
     *
     * @param c The character to put.
     * @param x The 'x' coordinate of the character.
     * @param y The 'y' coordinate of the character.
     * @param color The color to write the character with.
     */
    void putCharAt(char c, size_t x, size_t y, uint8_t color)
    {
        buffer[getIndex(x, y)] = makeVgaEntry(c, color);
    }

    /**
     * Put a single character on the screen at the current cursors position.
     * If the next character overflows then put it on the next line.
     *
     * @param c The character to put.
     */
    void putChar(char c)
    {
        putCharAt(c, column, row);

        // If the next column is at the end of the row then break onto a new line.
        if (++column >= VGA_WIDTH)
        {
            column = 0;

            // If the next row is at the end go back to the beginning.
            if (++row >= VGA_HEIGHT)
            {
                row = 0;
            }
        }
    }

    /**
     * Write an entire string to the console window.
     *
     * @param data The string.
     */
    void write(const char* data)
    {
        size_t len = strlen(data);

        for (size_t i = 0; i < len; i++)
        {
            putChar(data[i]);
        }
    }
};

#endif
