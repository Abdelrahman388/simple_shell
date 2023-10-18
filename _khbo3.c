#include "custom_shell.h"

/**
 * custom_split_to_words - splits a custom string into words. Repeat custom_delimiters are ignored
 * @custom_str: the custom input string
 * @custom_d: the custom delimiter string
 *
 * Return: a pointer to an array of custom strings, or NULL on failure
 */
char **custom_split_to_words(char *custom_str, char *custom_d)
{
    int custom_i, custom_j, custom_k, custom_m, custom_num_words = 0;
    char **custom_s;

    if (custom_str == NULL || custom_str[0] == 0)
        return NULL;
    if (!custom_d)
        custom_d = " ";

    for (custom_i = 0; custom_str[custom_i] != '\0'; custom_i++)
    {
        if (!is_custom_delimiter(custom_str[custom_i], custom_d) && (is_custom_delimiter(custom_str[custom_i + 1], custom_d) || !custom_str[custom_i + 1]))
            custom_num_words++;
    }

    if (custom_num_words == 0)
        return NULL;

    custom_s = custom_malloc((1 + custom_num_words) * sizeof(char *));
    if (!custom_s)
        return NULL;

    for (custom_i = 0, custom_j = 0; custom_j < custom_num_words; custom_j++)
    {
        while (is_custom_delimiter(custom_str[custom_i], custom_d))
            custom_i++;

        custom_k = 0;

        while (!is_custom_delimiter(custom_str[custom_i + custom_k], custom_d) && custom_str[custom_i + custom_k])
            custom_k++;

        custom_s[custom_j] = custom_malloc((custom_k + 1) * sizeof(char));
        if (!custom_s[custom_j])
        {
            for (custom_k = 0; custom_k < custom_j; custom_k++)
                custom_free(custom_s[custom_k]);
            custom_free(custom_s);
            return NULL;
        }

        for (custom_m = 0; custom_m < custom_k; custom_m++)
            custom_s[custom_j][custom_m] = custom_str[custom_i++];

        custom_s[custom_j][custom_m] = 0;
    }

    custom_s[custom_j] = NULL;
    return custom_s;
}

/**
 * custom_split_to_words_2 - splits a custom string into words
 * @custom_str: the custom input string
 * @custom_delimiter: the custom delimiter
 *
 * Return: a pointer to an array of custom strings, or NULL on failure
 */
char **custom_split_to_words_2(char *custom_str, char custom_delimiter)
{
    int custom_i, custom_j, custom_k, custom_m, custom_num_words = 0;
    char **custom_s;

    if (custom_str == NULL || custom_str[0] == 0)
        return NULL;

    for (custom_i = 0; custom_str[custom_i] != '\0'; custom_i++)
    {
        if ((custom_str[custom_i] != custom_delimiter && custom_str[custom_i + 1] == custom_delimiter) ||
            (custom_str[custom_i] != custom_delimiter && !custom_str[custom_i + 1]) || custom_str[custom_i + 1] == custom_delimiter)
            custom_num_words++;
    }

    if (custom_num_words == 0)
        return NULL;

    custom_s = custom_malloc((1 + custom_num_words) * sizeof(char *));
    if (!custom_s)
        return NULL;

    for (custom_i = 0, custom_j = 0; custom_j < custom_num_words; custom_j++)
    {
        while (custom_str[custom_i] == custom_delimiter && custom_str[custom_i] != custom_delimiter)
            custom_i++;

        custom_k = 0;

        while (custom_str[custom_i + custom_k] != custom_delimiter && custom_str[custom_i + custom_k] && custom_str[custom_i + custom_k] != custom_delimiter)
            custom_k++;

        custom_s[custom_j] = custom_malloc((custom_k + 1) * sizeof(char));
        if (!custom_s[custom_j])
        {
            for (custom_k = 0; custom_k < custom_j; custom_k++)
                custom_free(custom_s[custom_k]);
            custom_free(custom_s);
            return NULL;
        }

        for (custom_m = 0; custom_m < custom_k; custom_m++)
            custom_s[custom_j][custom_m] = custom_str[custom_i++];

        custom_s[custom_j][custom_m] = 0;
    }

    custom_s[custom_j] = NULL;
    return custom_s;
}
