#include "shell.h"


/**
 * input_buf - chained of Buffers Commands
 *
 * @info: the Parameter Struct
 *
 * @buff: Buffer Address
 *
 * @ln: Address Of ln Var
 * Return: Read Bytes
 */

ssize_t input_buf(info_t *info, char **buff, size_t *ln)
{
	size_t len_p = 0;
	ssize_t r = 0;

	if (!*ln)
	{
		free(*buff);
		*buff = NULL;
		signal(SIGINT, sigintHandler);

		r = getline(buff, &len_p, stdin);

		r = _getline(info, buff, &len_p);

		if (r > 0)
		{
			if ((*buff)[r - 1] == '\n')
			{
				(*buff)[r - 1] = '\0';
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buff);
			build_history_list(info, *buff, info->histcount++);
			{
				*ln = r;
				info->cmd_buf = buff;
			}
		}
	}
	return (r);
}


/**
 * get_input - to Gets the Line Minus Newline
 *
 * @info: a Parameter Struct
 * Return: Read a Bytes
 */

ssize_t get_input(info_t *info)
{
	static size_t l, g, ln;
	static char *buff;
	char **buf_p = &(info->arg), *b;
	ssize_t r = 0;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buff, &ln);
	if (r == -1)
		return (-1);
	if (ln)
	{
		g = l;
		b = buff + l;

		check_chain(info, buff, &g, l, ln);
		while (g < ln)
		{
			if (is_chain(info, buff, &g))
				break;
			g++;
		}

		l = g + 1;
		if (l >= ln)
		{
			l = ln = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = b;
		return (_strlen(b));
	}

	*buf_p = buff;
	return (r);
}


/**
 * read_buf - Buffer to be read
 *
 * @info: a Parameter Struct
 *
 * @buf: Buffer
 *
 * @i: size
 * Return: r
 */

ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}


/**
 * _getline - to Gets Next Line Of Input From STDIN
 *
 * @info: a Parameter Struct
 *
 * @ptr: Address Of Pointer To Buffer & Preallocated Or NULL
 *
 * @length: the Size Of Preallocated pointr Buffer, NULL If Not
 * Return: s
 */

int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	ssize_t r = 0, s = 0;
	size_t k;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}


/**
 * sigintHandler - the Blocks ctrl+C
 *
 * @sig_num: a Signal Numb
 * Return: void
 */

void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
