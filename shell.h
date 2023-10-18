#ifndef _MY_SUPER_SHELL_H_
#define _MY_SUPER_SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define MY_SUPER_SHELL_READ_BUF_SIZE 1024
#define MY_SUPER_SHELL_WRITE_BUF_SIZE 1024
#define MY_SUPER_SHELL_BUF_FLUSH -1

#define MY_SUPER_SHELL_CMD_NORM 0
#define MY_SUPER_SHELL_CMD_OR 1
#define MY_SUPER_SHELL_CMD_AND 2
#define MY_SUPER_SHELL_CMD_CHAIN 3

#define MY_SUPER_SHELL_CONVERT_LOWERCASE 1
#define MY_SUPER_SHELL_CONVERT_UNSIGNED 2

#define MY_SUPER_SHELL_USE_GETLINE 0
#define MY_SUPER_SHELL_USE_STRTOK 0

#define MY_SUPER_SHELL_HIST_FILE ".my_super_shell_history"
#define MY_SUPER_SHELL_HIST_MAX 4096

extern char **my_super_shell_environ;

typedef struct my_super_shell_liststr
{
    int num;
    char *str;
    struct my_super_shell_liststr *next;
} my_super_shell_list_t;

typedef struct my_super_shell_passinfo
{
    char *arg;
    char **argv;
    char *path;
    int argc;
    unsigned int line_count;
    int err_num;
    int linecount_flag;
    char *fname;
    my_super_shell_list_t *env;
    my_super_shell_list_t *history;
    my_super_shell_list_t *alias;
    char **environ;
    int env_changed;
    int status;
    char **cmd_buf;
    int cmd_buf_type;
    int readfd;
    int histcount;
} my_super_shell_info_t;

#define MY_SUPER_SHELL_INFO_INIT {NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, 0, 0, 0}

typedef struct my_super_shell_builtin
{
    char *type;
    int (*func)(my_super_shell_info_t *);
} my_super_shell_builtin_table;

int my_super_shell_hsh(my_super_shell_info_t *, char **);
int my_super_shell_find_builtin(my_super_shell_info_t *);
void my_super_shell_find_cmd(my_super_shell_info_t *);
void my_super_shell_fork_cmd(my_super_shell_info_t *);

int my_super_shell_is_cmd(my_super_shell_info_t *, char *);
char *my_super_shell_dup_chars(char *, int, int);
char *my_super_shell_find_path(my_super_shell_info_t *, char *, char *);

int my_super_shell_loophsh(char **);

void my_super_shell_eputs(char *);
int my_super_shell_eputchar(char);
int my_super_shell_putfd(char c, int fd);
int my_super_shell_putsfd(char *str, int fd);

int my_super_shell_strlen(char *);
int my_super_shell_strcmp(char *, char *);
char *my_super_shell_starts_with(const char *, const char *);
char *my_super_shell_strcat(char *, char *);

char *my_super_shell_strcpy(char *, char *);
char *my_super_shell_strdup(const char *);
void my_super_shell_puts(char *);
int my_super_shell_putchar(char);

char *my_super_shell_strncpy(char *, char *, int);
char *my_super_shell_strncat(char *, char *, int);
char *my_super_shell_strchr(char *, char);

char **my_super_shell_strtow(char *, char *);
char **my_super_shell_strtow2(char *, char);

char *my_super_shell_memset(char *, char, unsigned int);
void my_super_shell_ffree(char **);
void *my_super_shell_realloc(void *, unsigned int, unsigned int);

int my_super_shell_bfree(void **);

int my_super_shell_interactive(my_super_shell_info_t *);
int my_super_shell_is_delim(char, char *);
int my_super_shell_is_alpha(int);
int my_super_shell_atoi(char *);

int my_super_shell_erratoi(char *);
void my_super_shell_print_error(my_super_shell_info_t *, char *);
int my_super_shell_print_d(int, int);
char *my_super_shell_convert_number(long int, int, int);
void my_super_shell_remove_comments(char *);

int my_super_shell_myexit(my_super_shell_info_t *);
int my_super_shell_mycd(my_super_shell_info_t *);
int my_super_shell_myhelp(my_super_shell_info_t *);

int my_super_shell_myhistory(my_super_shell_info_t *);
int my_super_shell_myalias(my_super_shell_info_t *);

ssize_t my_super_shell_get_input(my_super_shell_info_t *);
int my_super_shell_getline(my_super_shell_info_t *, char **, size_t *);
void my_super_shell_sigintHandler(int);

void my_super_shell_clear_info(my_super_shell_info_t *);
void my_super_shell_set_info(my_super_shell_info_t *, char **);
void my_super_shell_free_info(my_super_shell_info_t *, int);

char *my_super_shell_getenv(my_super_shell_info_t *, const char *);
int my_super_shell_myenv(my_super_shell_info_t *);
int my_super_shell_mysetenv(my_super_shell_info_t *);
int my_super_shell_myunsetenv(my_super_shell_info_t *);
int my_super_shell_populate_env_list(my_super_shell_info_t *);

char **my_super_shell_get_environ(my_super_shell_info_t *);
int my_super_shell_unsetenv(my_super_shell_info_t *, char *);
int my_super_shell_setenv(my_super_shell_info_t *, char *, char *);

char *my_super_shell_get_history_file(my_super_shell_info_t);
int my_super_shell_write_history(my_super_shell_info_t);
int my_super_shell_read_history(my_super_shell_info_t);
int my_super_shell_build_history_list(my_super_shell_info_t, char *, int);
int my_super_shell_renumber_history(my_super_shell_info_t);

my_super_shell_list_t *my_super_shell_add_node(my_super_shell_list_t **, const char *, int);
my_super_shell_list_t *my_super_shell_add_node_end(my_super_shell_list_t **, const char *, int);
size_t my_super_shell_print_list_str(my_super_shell_list_t *);
int my_super_shell_delete_node_at_index(my_super_shell_list_t **, unsigned int);
void my_super_shell_free_list(my_super_shell_list_t **);

size_t my_super_shell_list_len(my_super_shell_list_t *);
char **my_super_shell_list_to_strings(my_super_shell_list_t *);
size_t my_super_shell_print_list(my_super_shell_list_t *);
my_super_shell_list_t *my_super_shell_node_starts_with(my_super_shell_list_t *, char *, char);
ssize_t my_super_shell_get_node_index(my_super_shell_list_t *, my_super_shell_list_t *);

int my_super_shell_is_chain(my_super_shell_info_t *, char *, size_t *);
void my_super_shell_check_chain(my_super_shell_info_t *, char *, size_t *, size_t, size_t);
int my_super_shell_replace_alias(my_super_shell_info_t *);
int my_super_shell_replace_vars(my_super_shell_info_t *);
int my_super_shell_replace_string(char **, char *);

#endif
