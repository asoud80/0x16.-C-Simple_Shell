#ifndef _SHELL_H_
#define _SHELL_H_

#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <limits.h>


/* Reading & Writing Buffers */

#define BUF_FLUSH -1

#define WRITE_BUF_SIZE	1024

#define READ_BUF_SIZE 1024


/* Chaining of Command */

#define CMD_CHAIN       3

#define CMD_AND         2

#define CMD_OR		1

#define CMD_NORM       0


/* Converting Number() */

#define CONVERT_UNSIGNED        2

#define CONVERT_LOWERCASE	1

/*  1 in case of Use System getline() */

#define USE_STRTOK 0

#define USE_GETLINE 0

#define HIST_MAX	4096

#define HIST_FILE       ".simple_shell_history"


extern char **environ;

/**
 * struct lststr - Singly_linked_list.
 *
 * @num: Num Field.
 *
 * @str: the String.
 *
 * @next: Pointing The Next Node.
 */

typedef struct lststr
{
	char *str;

	struct lststr *next;

	int num;

} list_t;

/**
 *struct pssifo - it Containing Pesudo Argus for Passing into the Function
 *
 *		Allow the Uniform Prototype Of Function Pointer Struct.
 *
 *@arg: Generate the String From getline that Contains Argus.
 *
 *@argv: Array Of Strings that Generated From argumnets.
 *
 *@path: the String Path to Current Command.
 *
 *@argc: Argus Count.
 *
 *@line_count: Error Count.
 *
 *@err_num: Error Code to exit().
 *
 *@linecount_flag: in case of ON Count This Line Of Input.
 *
 *@fname: Program Filename.
 *
 *@env: copy envrion of Linked_ List_ Local.
 *
 *@environ: Custom Modified Copy Of Environ From LL env.
 *
 *@history: History Node.
 *
 *@alias: Alias Node.
 *
 *@env_changed: in case of Environ Was Changed it will be ON.
 *
 *@status: Return Status Of Last execed Command.
 *
 *@cmd_buf: Address Of Pointer To cmd_buf, if chaining ON.
 *
 *@cmd_buf_type: CMD_type  ||,  &&,  ;
 *
 *@readfd: fd From Which To Read Line Input.
 *
 *@histcount: History Line Number Count
 */

typedef struct pssifo
{
	char *path;
	int linecount_flag;
	int err_num;
	int argc;
	char *fname;
	char *arg;
	list_t *alias;
	list_t *env;
	list_t *history;
	char **environ;
	char **argv;
	int status;
	int env_changed;
	unsigned int line_count;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct bltin - it Contains bltin String & its Related Function
 *
 *@type: bltin Command Flag.
 *
 *@func: a Function.
 */

typedef struct bltin
{
	int (*func)(info_t *);
	char *type;
} builtin_table;


/* shell_SHloop.c */

void fork_cmd(info_t *);

void find_cmd(info_t *);

int hsh(info_t *, char **);

int find_builtin(info_t *);

/* shell_parser.c */

char *find_path(info_t *, char *, char *);

char *dup_char(char *, int, int);

int is_cmd(info_t *, char *);

/* simple_loopsh.c */

int loopsh(char **);


/* simple_Error.c */

int _putfd(char c, int fd);

void _eputs(char *);

int _putsfd(char *str, int fd);

int _eputchr(char);


/* simple_string.c */

char *starts_with(const char *, const char *);

int _strlen(char *);

char *_strcat(char *, char *);

int _strcmp(char *, char *);


/* simple_string1.c */

int _putchar(char);

char *_strcpy(char *, char *);

char *_strdup(const char *);

void _puts(char *);


/* simple_exits.c */

char *_strncat(char *, char *, int);

char *_strchr(char *, char);

char *_strncpy(char *, char *, int);


/* shell_2kenizer.c */

char **strtow2(char *, char);

char **strtow(char *, char *);


/* shell_realloc.c */

void ffree(char **);

void *_realloc(void *, unsigned int, unsigned int);

char *_memset(char *, char, unsigned int);


/* simple_memory.c */

int bfree(void **);


/* shell_atoi.c */

int _atoi(char *);

int _isalpha(int);

int interactive(info_t *);

int is_delim(char, char *);


/* shell_errors1.c */

int _erratoi(char *);

int print_d(int, int);

int _erratoi(char *);

void print_error(info_t *, char *);

char *convert_number(long int, int, int);

void remove_comments(char *);


/* simple_builtin.c */

int _mycd(info_t *);

int _myhelp(info_t *);

int _myexit(info_t *);

/* simple_builtin1.c */

int _myalias(info_t *);

int _myhistory(info_t *);


/* simple_getline.c */

void sigintHandler(int);

ssize_t get_input(info_t *);

int _getline(info_t *, char **, size_t *);


/* simple_getinfo.c */

void set_info(info_t *, char **);

void free_info(info_t *, int);

void clear_info(info_t *);


/* shell_environ.c */

int _myenv(info_t *);

char *_getenv(info_t *, const char *);

int populate_env_list(info_t *);

int _mysetenv(info_t *);

int _myunsetenv(info_t *);


/* simple_getenv.c */


int _setenv(info_t *, char *, char *);

int _unsetenv(info_t *, char *);

char **get_environ(info_t *);


/* shell_history.c */


int read_history(info_t *info);

char *get_history_file(info_t *info);

int renumber_history(info_t *info);

int write_history(info_t *info);

int build_history_list(info_t *info, char *buf, int linecount);


/* shell_lists.c */

list_t *add_node(list_t **, const char *, int);

int delete_node_at_index(list_t **, unsigned int);

void free_list(list_t **);

list_t *add_node_end(list_t **, const char *, int);

size_t print_list_str(const list_t *);


/* shell_lists1.c */

list_t *node_starts_with(list_t *, char *, char);

char **list_to_strings(list_t *);

ssize_t get_node_index(list_t *, list_t *);

size_t print_list(const list_t *);

size_t list_len(const list_t *);


/* simple_vars.c */

int replace_alias(info_t *);

int is_chain(info_t *, char *, size_t *);

void check_chain(info_t *, char *, size_t *, size_t, size_t);

int replace_string(char **, char *);

int replace_vars(info_t *);

#endif
