#include "custom_shell.h"

/**
 * custom_check_chain_delimiter - test if the current character in the buffer is a chain delimiter
 * @custom_info: the custom parameter struct
 * @custom_buf: the custom char buffer
 * @custom_p: address of the current position in custom_buf
 *
 * Return: 1 if chain delimiter, 0 otherwise
 */
int custom_check_chain_delimiter(custom_info_t *custom_info, char *custom_buf, size_t *custom_p)
{
    size_t custom_j = *custom_p;

    if (custom_buf[custom_j] == '|' && custom_buf[custom_j + 1] == '|')
    {
        custom_buf[custom_j] = 0;
        custom_j++;
        custom_info->custom_buffer_type = CUSTOM_CMD_OR;
    }
    else if (custom_buf[custom_j] == '&' && custom_buf[custom_j + 1] == '&')
    {
        custom_buf[custom_j] = 0;
        custom_j++;
        custom_info->custom_buffer_type = CUSTOM_CMD_AND;
    }
    else if (custom_buf[custom_j] == ';')
    {
        custom_buf[custom_j] = 0;
        custom_info->custom_buffer_type = CUSTOM_CMD_CHAIN;
    }
    else
    {
        return 0;
    }
    *custom_p = custom_j;
    return 1;
}

/**
 * custom_check_chain_condition - checks if we should continue chaining based on the last status
 * @custom_info: the custom parameter struct
 * @custom_buf: the custom char buffer
 * @custom_p: address of the current position in custom_buf
 * @custom_i: starting position in custom_buf
 * @custom_len: length of custom_buf
 *
 * Return: Void
 */
void custom_check_chain_condition(custom_info_t *custom_info, char *custom_buf, size_t *custom_p, size_t custom_i, size_t custom_len)
{
    size_t custom_j = *custom_p;

    if (custom_info->custom_buffer_type == CUSTOM_CMD_AND)
    {
        if (custom_info->custom_status)
        {
            custom_buf[custom_i] = 0;
            custom_j = custom_len;
        }
    }
    if (custom_info->custom_buffer_type == CUSTOM_CMD_OR)
    {
        if (!custom_info->custom_status)
        {
            custom_buf[custom_i] = 0;
            custom_j = custom_len;
        }
    }
    *custom_p = custom_j;
}

/**
 * custom_replace_command_alias - replaces aliases in the tokenized string
 * @custom_info: the custom parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int custom_replace_command_alias(custom_info_t *custom_info)
{
    int custom_i;
    custom_list_t *custom_node;
    char *custom_p;

    for (custom_i = 0; custom_i < 10; custom_i++)
    {
        custom_node = custom_node_starts_with(custom_info->custom_alias, custom_info->custom_argv[0], '=');
        if (!custom_node)
            return (0);
        custom_free(custom_info->custom_argv[0]);
        custom_p = custom_strchr(custom_node->custom_str, '=');
        if (!custom_p)
            return (0);
        custom_p = custom_strdup(custom_p + 1);
        if (!custom_p)
            return (0);
        custom_info->custom_argv[0] = custom_p;
    }
    return (1);
}

/**
 * custom_replace_command_variables - replaces variables in the tokenized string
 * @custom_info: the custom parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int custom_replace_command_variables(custom_info_t *custom_info)
{
    int custom_i = 0;
    custom_list_t *custom_node;

    for (custom_i = 0; custom_info->custom_argv[custom_i]; custom_i++)
    {
        if (custom_info->custom_argv[custom_i][0] != '$' || !custom_info->custom_argv[custom_i][1])
            continue;

        if (!custom_strcmp(custom_info->custom_argv[custom_i], "$?"))
        {
            custom_replace_string(&(custom_info->custom_argv[custom_i]),
                                  custom_strdup(custom_convert_number(custom_info->custom_status, 10, 0)));
            continue;
        }
        if (!custom_strcmp(custom_info->custom_argv[custom_i], "$$"))
        {
            custom_replace_string(&(custom_info->custom_argv[custom_i]),
                                  custom_strdup(custom_convert_number(custom_getpid(), 10, 0)));
            continue;
        }
        custom_node = custom_node_starts_with(custom_info->custom_env, &custom_info->custom_argv[custom_i][1], '=');
        if (custom_node)
        {
            custom_replace_string(&(custom_info->custom_argv[custom_i]),
                                  custom_strdup(custom_strchr(custom_node->custom_str, '=') + 1));
            continue;
        }
        custom_replace_string(&custom_info->custom_argv[custom_i], custom_strdup(""));
    }
    return (0);
}

/**
 * custom_replace_string - replaces a custom string
 * @custom_old: address of the old custom string
 * @custom_new: new custom string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int custom_replace_string(char **custom_old, char *custom_new)
{
    custom_free(*custom_old);
    *custom_old = custom_new;
    return (1);
}
