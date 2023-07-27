#include "shell.h"

int lsh_help(char **args);
int lsh_cd(char **args);
int lsh_ctrld(char **args);
int lsh_exit(char **args);


/*
 * this is the list for  Builtin Coomands and Followed BY it's Functions
 */


int (*builtin_func[]) (char **) = {&lsh_cd, &lsh_help, &lsh_exit, &lsh_ctrld};
char *builtin_str[] = {"cd", "help", "exit", "^D"};


/**
 * lsh_num_builtins - SIZE
 *
 * Return: SIZE
 */


int lsh_num_builtins(void)
{
	return (sizeof(builtin_str) / sizeof(char *));
}


/*
 * builtin Function that will be implemented
*/


/**
 * lsh_cd - change dirction of Builtin.
 *
 * @args: this is the list OF Arguments. Argus[0] IS "CD". Argus[1] IS Dir
 *
 * Return: for Successful 1.
 */

int lsh_cd(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "hsh: expected argument to \"cd\"\n");
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			perror("hsh");
		}
	}
	return (1);
}


/**
 * lsh_help - it will Print HELP of SHELL
 *
 * @args: this is a list OF Arguments. and not Examined
 *
 * Return: Return 1 always, for Continuing Execut
 */

int lsh_help(char **args)
{
	int i;

	printf("Amgad aboul seoud and Nahla Hussien\n");
	printf("in case You want HELP, Call 122-HELP\n");
	(void)args;
	for (i = 0; i < lsh_num_builtins(); i++)
	{
		printf("  %s\n", builtin_str[i]);
	}

	return (1);
}


/**
 * lsh_exit - this is Builtin for Exit Shell
 *
 * @args: this is a list OF Arguments. and not Examined
 *
 * Return: Return 1 always, for Continuing Execut
 */

int lsh_exit(char **args)
{
	(void)args;
	free(args);
	return (200);
}


/**
 * lsh_ctrld - this is a Builtin for handling "^d" CALL
 *
 * @args: this is a list OF Arguments. and not Examined
 *
 * Return: Return 1 always, for Continuing Execut
 */

int lsh_ctrld(char **args)
{
	(void)args;
	free(args);
	return (200);
}


/**
 *_fork_fun - FOO which will Create FORK
 *
 *@arg: this is a command & values PATH

 *@av: it have Name of the Program

 *@env: environ.

 *@lineptr: this is the command Line of a User

 *@np: Proces ID

 *@c: the checker will ADD a New TEST

 *Return: if successfull 0
 */


int _fork_fun(char **arg, char **av, char **env, char *lineptr, int np, int c)
{

	pid_t child;
	int status, i = 0;
	char *format = "%s: %d: %s: not found\n";

	if (arg[0] == NULL)
		return (1);
	for (i = 0; i < lsh_num_builtins(); i++)
	{
		if (_strcmp(arg[0], builtin_str[i]) == 0)
			return (builtin_func[i](arg));
	}
	child = fork();
	if (child == 0)
	{
		if (execve(arg[0], arg, env) == -1)
		{
			fprintf(stderr, format, av[0], np, arg[0]);
			if (!c)
				free(arg[0]);
			free(arg);
			free(lineptr);
			exit(errno);
		}
	}
	else
	{
		wait(&status);
		return (status);
	}
	return (0);
}
