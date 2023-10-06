#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

/**
 * struct liststr - a function that used to singly linked list.
 * @number: field number.
 * @string: string.
 * @next: points to next node.
 */

typedef struct liststr
{
	int number;
	char *string;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - a function that used to contains pseudo-arguements
 *			to pass into a function.
 *@arg: a string generated from arguements.
 *@argv: strings array.
 *@path: a string path for current command.
 *@argc: argument counter.
 *@line_count: error counter.
 *@err_num: error code for exit.
 *@linecount_flag: if on count this line of input.
 *@fname: filename.
 *@env: linked list local copy of environ.
 *@environ: custom modified copy of environ.
 *@history: the node history.
 *@alias: alias node.
 *@env_changed: on if environ was changed.
 *@status: the return status of the last executed command.
 *@cmd_buf: pointer address to cmd_buf, on if chaining.
 *@cmd_buf_type: CMD_type, &&, || ;
 *@readfd: the file from which to read line input.
 *@histcount: line number history.
 */

typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - a function that used to contains a builtin string.
 *@type: command flag.
 *@func: function.
 */

typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

int loophsh(char **);

char *_strcat(char *strin1, char *strin2);
char *starts_with(const char *strin1, const char *strin2);
int _strcmp(char *x, char *y);
int _strlen(char *m);

int _putchar(char m);
void _puts(char *string);
char *_strdup(const char *string);
char *_strcpy(char *strin1, char *strin2);

char *_strchr(char *string, char ch);
char *_strncat(char *strin1, char *strin2, int m);
char *_strncpy(char *strin1, char *strin2, int m);

char **strtow2(char *string, char n);
char **strtow(char *string, char *n);

void ffree(char **string);
void *_realloc(void *pointer, unsigned int old, unsigned int new);
char *_memset(char *m, char m_byte, unsigned int amount);

int bfree(void **pointer);

int _atoi(char *string);
int interactive(info_t *m);
int is_delim(char character, char *certain);
int _isalpha(int character);

void remove_comments(char *buffer);
int _erratoi(char *string);
void print_error(info_t *m, char *string);
int print_d(int m, int file);
char *convert_number(long int number, int b, int f);

void free_list(list_t **head_pointer);
list_t *add_node(list_t **head, const char *string, int number);
list_t *add_node_end(list_t **head, const char *string, int number);
size_t print_list_str(const list_t *m);
int delete_node_at_index(list_t **head, unsigned int point);

ssize_t get_node_index(list_t *head, list_t *n_node);
size_t list_len(const list_t *m);
char **list_to_strings(list_t *head);
size_t print_list(const list_t *m);
list_t *node_starts_with(list_t *n_node, char *pre_fix, char character);

int is_cmd(info_t *n_info, char *n_path);
char *dup_chars(char *path, int begin, int end);
char *find_path(info_t *n_info, char *n_path, char *n_cmd);

void _eputs(char *s);
int _eputchar(char character);
int _putfd(char character, int file);
int _putsfd(char *s, int file);

int _myhelp(info_t *information);
int _myexit(info_t *information);
int _mycd(info_t *information);

int _myalias(info_t *information);
int _myhistory(info_t *information);
int unset_alias(info_t *information, char *string);
int set_alias(info_t *information, char *string);
int print_alias(list_t *n_node);

int populate_env_list(info_t *information);
char *_getenv(info_t *information, const char *n_name);
int _myenv(info_t *information);
int _mysetenv(info_t *information);
int _myunsetenv(info_t *information);

int _setenv(info_t *information, char *variable, char *n_value);
char **get_environ(info_t *information);
int _unsetenv(info_t *information, char *variable);

void free_info(info_t *information, int n_all);
void clear_info(info_t *information);
void set_info(info_t *information, char **n_av);

void sigintHandler(__attribute__((unused))int sig_num);
ssize_t input_buf(info_t *information, char **buffer, size_t *length);
ssize_t get_input(info_t *information);
ssize_t read_buf(info_t *information, char *buffer, size_t *m);
int _getline(info_t *information, char **pointer, size_t *n_length);

void fork_cmd(info_t *information);
int hsh(info_t *information, char **n_av);
int find_builtin(info_t *information);
void find_cmd(info_t *information);

int renumber_history(info_t *information);
char *get_history_file(info_t *information);
int write_history(info_t *information);
int read_history(info_t *information);
int build_history_list(info_t *information, char *buffer, int linecounter);

int replace_string(char **old_str, char *new_str);
int is_chain(info_t *information, char *buffer, size_t *pointer);
void check_chain(info_t *information, char *buffer,
		size_t *pointer, size_t x, size_t length);
int replace_alias(info_t *information);
int replace_vars(info_t *information);

#endif
