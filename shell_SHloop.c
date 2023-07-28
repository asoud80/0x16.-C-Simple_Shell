#include "shell.h"


/**
 * hsh - this is the Main Shell Loop
 *
 * @info: Parameter and Return info Struct
 *
 * @av: Argus Vector From main()
 *
 * Return: in case of success return 0, in case of error return 1,Or Error Code
 */


int hsh(info_t *info, char **av)
{
	int builtin_ret = 0;
	ssize_t i = 0;

	while (i != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		i = get_input(info);
		if (i != -1)
		{
			set_info(info, av);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - for Finding bltin Command.
 *
 * @info: a Parameter and Return info Struct
 * Return: in case of  bltin not found return -1,
 *
 *			If bltin Executed Successfully Return 0,
 *
 *			If bltin Found NBt Not Successful Return 1,
 *
 *			If bltin Signals exit() Return -2
 */

int find_builtin(info_t *info)
{
	int c, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (c = 0; builtintbl[i].type; c++)
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - to Find Command In the PATH
 *
 * @info: Parameter and Return Info Struct
 * Return: void
 */

void find_cmd(info_t *info)
{
	int a, b;
	char *path = NULL;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (a = 0, b = 0; info->arg[a]; a++)
		if (!is_delim(info->arg[a], " \t\n"))
			b++;
	if (!b)
		return;

	path = find_path(info, _getenv(info, "path="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - it will Forks and execuate Thread for running cmd.
 *
 * @info: Parameter and Return Info Struct
 * Return: void
 */

void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
