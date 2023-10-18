#include "custom_shell.h"

/**
 * my_custom_shell - main shell loop
 * @custom_info: the parameter & return info struct
 * @custom_av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int my_custom_shell(custom_info_t *custom_info, char **custom_av)
{
    ssize_t custom_read = 0;
    int custom_builtin_result = 0;

    while (custom_read != -1 && custom_builtin_result != -2)
    {
        clear_custom_info(custom_info);
        if (is_interactive(custom_info))
            _custom_puts("$ ");
        _custom_eputchar(CUSTOM_BUF_FLUSH);
        custom_read = custom_get_input(custom_info);
        if (custom_read != -1)
        {
            set_custom_info(custom_info, custom_av);
            custom_builtin_result = custom_find_builtin(custom_info);
            if (custom_builtin_result == -1)
                custom_find_custom_command(custom_info);
        }
        else if (is_interactive(custom_info))
            _custom_putchar('\n');
        free_custom_info(custom_info, 0);
    }
    write_custom_history(custom_info);
    free_custom_info(custom_info, 1);
    if (!is_interactive(custom_info) && custom_info->custom_status)
        exit(custom_info->custom_status);
    if (custom_builtin_result == -2)
    {
        if (custom_info->custom_error_number == -1)
            exit(custom_info->custom_status);
        exit(custom_info->custom_error_number);
    }
    return (custom_builtin_result);
}

/**
 * custom_find_builtin - finds a builtin command
 * @custom_info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *  0 if builtin executed successfully,
 *  1 if builtin found but not successful,
 *  2 if builtin signals exit()
 */
int custom_find_builtin(custom_info_t *custom_info)
{
    int custom_i, custom_builtin_result = -1;
    custom_builtin_table custom_builtintbl[] = {
        {"custom_exit", _my_custom_exit},
        {"custom_env", _my_custom_env},
        {"custom_help", _my_custom_help},
        {"custom_history", _my_custom_history},
        {"custom_setenv", _my_custom_setenv},
        {"custom_unsetenv", _my_custom_unsetenv},
        {"custom_cd", _my_custom_cd},
        {"custom_alias", _my_custom_alias},
        {NULL, NULL}
    };

    for (custom_i = 0; custom_builtintbl[custom_i].custom_type; custom_i++)
        if (_custom_strcmp(custom_info->custom_argv[0], custom_builtintbl[custom_i].custom_type) == 0)
        {
            custom_info->custom_line_count++;
            custom_builtin_result = custom_builtintbl[custom_i].custom_func(custom_info);
            break;
        }
    return (custom_builtin_result);
}

/**
 * custom_find_custom_command - finds a command in PATH
 * @custom_info: the parameter & return info struct
 *
 * Return: void
 */
void custom_find_custom_command(custom_info_t *custom_info)
{
    char *custom_path = NULL;
    int custom_i, custom_k;

    custom_info->custom_path = custom_info->custom_argv[0];
    if (custom_info->custom_linecount_flag == 1)
    {
        custom_info->custom_line_count++;
        custom_info->custom_linecount_flag = 0;
    }
    for (custom_i = 0, custom_k = 0; custom_info->custom_arg[custom_i]; custom_i++)
        if (!is_custom_delim(custom_info->custom_arg[custom_i], " \t\n"))
            custom_k++;
    if (!custom_k)
        return;

    custom_path = custom_find_custom_path(custom_info, _custom_getenv(custom_info, "PATH="), custom_info->custom_argv[0]);
    if (custom_path)
    {
        custom_info->custom_path = custom_path;
        custom_fork_custom_command(custom_info);
    }
    else
    {
        if ((is_interactive(custom_info) || _custom_getenv(custom_info, "PATH=") || custom_info->custom_argv[0][0] == '/') && is_custom_command(custom_info, custom_info->custom_argv[0]))
            custom_fork_custom_command(custom_info);
        else if (*(custom_info->custom_arg) != '\n')
        {
            custom_info->custom_status = 127;
            custom_print_error(custom_info, "not found\n");
        }
    }
}

/**
 * custom_fork_custom_command - forks a an exec thread to run cmd
 * @custom_info: the parameter & return info struct
 *
 * Return: void
 */
void custom_fork_custom_command(custom_info_t *custom_info)
{
    pid_t custom_child_pid;

    custom_child_pid = custom_fork();
    if (custom_child_pid == -1)
    {
        /* TODO: PUT ERROR FUNCTION */
        perror("Error:");
        return;
    }
    if (custom_child_pid == 0)
    {
        if (execve(custom_info->custom_path, custom_info->custom_argv, custom_get_custom_environment(custom_info)) == -1)
        {
            free_custom_info(custom_info, 1);
            if (errno == EACCES)
                exit(126);
            exit(1);
        }
        /* TODO: PUT ERROR FUNCTION */
    }
    else
    {
        wait(&(custom_info->custom_status));
        if (WIFEXITED(custom_info->custom_status))
        {
            custom_info->custom_status = WEXITSTATUS(custom_info->custom_status);
            if (custom_info->custom_status == 126)
                custom_print_error(custom_info, "Permission denied\n");
        }
    }
}
