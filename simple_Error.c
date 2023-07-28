#include "shell.h"

/**
 *_eputs - Input String to be printed.
 *
 * @strg: print a String.
 * Return: none
 */

void _eputs(char *strg)
{
	int c = 0;

	if (!strg)
		return;
	while (strg[c] != '\0')
	{
		_eputchr(strg[c]);
		c++;
	}
}


/**
 * _eputchr - Character k to bw write To stderr.
 *
 * @k: print a Charhacter.
 * Return: 1 in case of Success
 *
 * On error, reutrn -1 , & ErrNo Set in case of Appropriately
 */

int _eputchr(char k)
{
	static char buf[WRITE_BUF_SIZE];
	static int l;

	if (k == BUF_FLUSH || l >= WRITE_BUF_SIZE)
	{
		write(2, buf, l);
		l = 0;
	}
	if (k != BUF_FLUSH)
		buf[l++] = k;
	return (1);
}


/**
 * _putfd - to Writes Char C into a Given fd.
 *
 * @c: print a Char.
 *
 * @fd: Write Filedescriptor to
 * Return: 1 in case of Success
 *
 * On error, Return -1, & ErrNo will be Set Appropriately
 */


int _putfd(char c, int fd)
{
	static char buf[WRITE_BUF_SIZE];
	static int n;

	if (c == BUF_FLUSH || n >= WRITE_BUF_SIZE)
	{
		write(fd, buf, n);
		n = 0;
	}
	if (c != BUF_FLUSH)
		buf[n++] = c;
	return (1);
}


/**
 *_putsfd - Input String to be printed.
 *
 * @strg: Print a String.
 *
 * @fd: Writes a Filedescriptor into.
 * Return: Numb Of Characters Put.
 */

int _putsfd(char *strg, int fd)
{
	int m = 0;

	if (!strg)
		return (0);
	while (*strg)
	{
		m += _putfd(*strg++, fd);
	}
	return (m);
}
