#include "shell.h"


/**
 * _strcpy - it will Copies the String
 *
 * @ddst: Destination
 *
 * @sorc: Source
 * Return: Pointer To Destination
 */

char *_strcpy(char *ddst, char *sorc)
{
	int l = 0;

	if (ddst == sorc || sorc == 0)
		return (ddst);
	while (sorc[l])
	{
		ddst[l] = sorc[l];
		l++;
	}
	ddst[l] = 0;
	return (ddst);
}


/**
 * _strdup - it will Duplicates the String
 *
 * @strg: duplicate a String.
 * Return: Pointer for Duplicated String
 */

char *_strdup(const char *strg)
{
	char *ret;
	int lgth = 0;

	if (strg == NULL)
		return (NULL);
	while (*strg++)
		lgth++;
	ret = malloc(sizeof(char) * (lgth + 1));
	if (!ret)
		return (NULL);
	for (lgth++; lgth--;)
		ret[lgth] = *--strg;
	return (ret);
}


/**
 *_puts - it Prints the Input String.

 *@strg: print a String.
 * Return: None.
 */

void _puts(char *strg)
{
	int l = 0;

	if (!strg)
		return;
	while (strg[l] != '\0')
	{
		_putchar(strg[l]);
		l++;
	}
}


/**
 * _putchar - Character K to stdout to be written.
 *
 * @k: Print a Character.
 * Return: 1 for Success
 *
 * On error, Return -1, & Errno will be Set Appropriately
 */

int _putchar(char k)
{
	static char buf[WRITE_BUF_SIZE];
	static int l;

	if (k == BUF_FLUSH || l >= WRITE_BUF_SIZE)
	{
		write(1, buf, l);
		l = 0;
	}
	if (k != BUF_FLUSH)
		buf[l++] = k;
	return (1);
}
