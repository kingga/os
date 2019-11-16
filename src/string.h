#include <stddef.h>

/**
 * Get the length of a string.
 *
 * @param str The string to get the length of.
 *
 * @return The length of the string.
 */
size_t strlen(const char* str)
{
    size_t ret = 0;

    while (str[ret] != 0)
    {
        ret++;
    }

    return ret;
}
