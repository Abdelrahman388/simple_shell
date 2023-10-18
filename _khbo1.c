#include "custom_shell.h"

/**
 * custom_string_length - returns the length of a custom string
 * @custom_str: the custom string whose length to check
 *
 * Return: integer length of custom string
 */
int custom_string_length(char *custom_str)
{
    int custom_i = 0;

    if (!custom_str)
        return (0);

    while (*custom_str++)
        custom_i++;
    return custom_i;
}

/**
 * custom_string_compare - performs lexicographic comparison of two custom strings.
 * @custom_str1: the first custom string
 * @custom_str2: the second custom string
 *
 * Return: negative if custom_str1 < custom_str2, positive if custom_str1 > custom_str2, zero if custom_str1 == custom_str2
 */
int custom_string_compare(char *custom_str1, char *custom_str2)
{
    while (*custom_str1 && *custom_str2)
    {
        if (*custom_str1 != *custom_str2)
            return (*custom_str1 - *custom_str2);
        custom_str1++;
        custom_str2++;
    }
    if (*custom_str1 == *custom_str2)
        return 0;
    else
        return (*custom_str1 < *custom_str2 ? -1 : 1);
}

/**
 * custom_starts_with - checks if custom_needle starts with custom_haystack
 * @custom_haystack: custom string to search
 * @custom_needle: the custom substring to find
 *
 * Return: address of the next character of custom_haystack or NULL
 */
char *custom_starts_with(const char *custom_haystack, const char *custom_needle)
{
    while (*custom_needle)
        if (*custom_needle++ != *custom_haystack++)
            return NULL;
    return (char *)custom_haystack;
}

/**
 * custom_string_concatenate - concatenates two custom strings
 * @custom_dest: the destination buffer
 * @custom_src: the source buffer
 *
 * Return: pointer to the destination buffer
 */
char *custom_string_concatenate(char *custom_dest, char *custom_src)
{
    char *custom_ret = custom_dest;

    while (*custom_dest)
        custom_dest++;
    while (*custom_src)
        *custom_dest++ = *custom_src++;
    *custom_dest = *custom_src;
    return custom_ret;
}
