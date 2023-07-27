#include "shell.h"


/**
 * Is_cmd - it will Determines whether File consider Executable Command or not
 *
 * @info: Info Struct.
 *
 * @path: Path Of a File.
 * Return: in case of True return 1, Ohtherwise return 0.
 */


int Is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}


/**
 * ddup_char - to Duplicates Chars.
 *
 * @pathstr: a path String
 *
 * @start: index to Start.
 *
 * @stop: index to Stop.
 *
 * Return: a Pointer of a  New Buffer
 */

char *ddup_char(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int a = 0, b = 0;

	for (b = 0, a = start; a < stop; a++)
		if (pathstr[a] != ':')
			buf[b++] = pathstr[a];
	buf[b] = 0;
	return (buf);
}

/**
 * found_pth - to Finds a cmd into a path String.
 *
 * @info: info to be Struct.
 *
 * @pathstr: a peth String.
 *
 * @cmd: Find a cmd.
 *
 * Return: the Full Path Of the cmd in case of Found Or NULL.
 */

char *found_pth(info_t *info, char *pathstr, char *cmd)
{
	char *path;
	int c = 0, cur_ps = 0;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (Is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[c] || pathstr[c] == ':')
		{
			path = ddup_char(pathstr, cur_ps, c);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (Is_cmd(info, path))
				return (path);
			if (!pathstr[c])
				break;
			cur_ps = c;
		}
		c++;
	}
	return (NULL);
}
