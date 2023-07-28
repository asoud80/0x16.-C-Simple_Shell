#ifndef SHELL_H

#define SHELL_H

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>


int lsh_help(char **args);
extern char **environ;
int lsh_ctrld(char **args);
int lsh_exit(char **args);
int _strcmp(char *s1, char *s2);
int _strlen(char *s);
char *_strcat(char *dest, char *src);
int _putchar(char c);
size_t _strncmp(char *s1, char *s2, size_t n);
char *_strcpy(char *dest, char *src);
int lsh_cd(char **args);

int _values_path(char **arg, char **env);
char *_getline_command(void);
void _getenv(char **env);
void _exit_command(char **args, char *lineptr, int _exit);
int _fork_fun(char **arg, char **av, char **env,
char *lineptr, int np, int c);
char **tokenize(char *lineptr);
char *_get_path(char **env);


#endif /* SHELL_H */
