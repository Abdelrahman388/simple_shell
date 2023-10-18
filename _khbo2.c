#include "custom_shell.h"

/**
 * custom_copy_string - copies a custom string
 * @custom_dest: the custom destination
 * @custom_src: the custom source
 *
 * Return: pointer to custom destination
 */
char *custom_copy_string(char *custom_dest, char *custom_src)
{
    int custom_i = 0;

    if (custom_dest == custom_src || custom_src == 0)
        return custom_dest;
    while (custom_src[custom_i])
    {
        custom_dest[custom_i] = custom_src[custom_i];
        custom_i++;
    }
    custom_dest[custom_i] = 0;
    return custom_dest;
}

/**
 * custom_duplicate_string - duplicates a custom string
 * @custom_str: the custom string to duplicate
 *
 * Return: pointer to the duplicated custom string
 */
char *custom_duplicate_string(const char *custom_str)
{
    int custom_length = 0;
    char *custom_ret;

    if (custom_str == NULL)
        return NULL;
    while (*custom_str++)
        custom_length++;
    custom_ret = custom_malloc(sizeof(char) * (custom_length + 1));
    if (!custom_ret)
        return NULL;
    for (custom_length++; custom_length--;)
        custom_ret[custom_length] = *--custom_str;
    return custom_ret;
}

/**
 * custom_print_string - prints a custom input string
 * @custom_str: the custom string to be printed
 *
 * Return: Nothing
 */
void custom_print_string(char *custom_str)
{
    int custom_i = 0;

    if (!custom_str)
        return;
    while (custom_str[custom_i] != '\0')
    {
        custom_put_character(custom_str[custom_i]);
        custom_i++;
    }
}

/**
 * custom_put_character - writes the custom character to stdout
 * @custom_c: The custom character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int custom_put_character(char custom_c)
{
    static int custom_i;
    static char custom_buffer[CUSTOM_WRITE_BUF_SIZE];

    if (custom_c == CUSTOM_BUF_FLUSH || custom_i >= CUSTOM_WRITE_BUF_SIZE)
    {
        custom_write(1, custom_buffer, custom_i);
        custom_i = 0;
    }
    if (custom_c != CUSTOM_BUF_FLUSH)
        custom_buffer[custom_i++] = custom_c;
    return 1;
}
