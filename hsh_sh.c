#include "shell.h"

/**
 * main - the main Argus Functions.
 *
 * @ac: Arguments count
 *
 * @av: argus
 *
 * @env: environ.
 *
 * Return: Exit = 0.
 */

int main(int ac, char **av, char **env)
{
	int pathValue = 0, status = 0, is_path = 0;
	char *line = NULL, /**input pointr*/ **commands = NULL; /**tokenized command*/
	(void)ac;
	while (1)/* will Loop Till Exit */
	{
		errno = 0;
		line = _getline_command();/** it will Reads User Input*/
		if (line == NULL && errno == 0)
			return (0);
		if (line)
		{
			pathValue++;
			commands = tokenize(line);/** tokenizes OR Parse User Input*/
			if (!commands)
				free(line);
			if (!_strcmp(commands[0], "env"))/**will Checks whether User Wrote env"*/
				_getenv(env);
			else
			{
				is_path = _values_path(&commands[0], env);/** tokenizes path*/
				status = _fork_fun(commands, av, env, line, pathValue, is_path);
					if (status == 200)
					{
						free(line);
						return (0);
					}
				if (is_path == 0)
					free(commands[0]);
			}
			free(commands); /*it will Free UP Memory*/
		}
		else
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);/** it will Write To Standard Output*/
			exit(status);
		}
		free(line);
	}
	return (status);
}
