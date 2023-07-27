#include "shell.h"


/**
 * interactive - it will Returns True in case of Shell in Interactive Mode
 *
 * @info: Struct the Address
 * Return: in case of Interactive Mode 1, Otherwise 0.
 */

int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}


/**
 * is_delim - it will Checks wheter the Character Is Delimeter or not
 *
 * @ch: Character To be checked
 *
 * @dlim: a Delimeter String
 *
 * Return: in case of true 1, in case of false 0
 */

int is_delim(char ch, char *dlim)
{
	while (*dlim)
		if (*dlim++ == ch)
			return (1);
	return (0);
}


/**
 *_isalpha - it will Checks the Alphabetic Character
 *
 *@h: Character To Input
 *
 *Return: in case of h Is Alphabetic return 1, Otherwise 0
 */


int _isalpha(int h)
{
	if ((h >= 'a' && h <= 'z') || (h >= 'A' && h <= 'Z'))
		return (1);
	else
		return (0);
}


/**
 *_atoi - it Converts the String To integer
 *
 *@t: String To Be Converted
 *
 *Return: in case of No NumS In String, otherwise Convert the Number
 */


int _atoi(char *t)
{
	unsigned int rslt = 0;
	int l, sgn = 1, flg = 0, otpt;

	for (l = 0;  t[l] != '\0' && flg != 2; l++)
	{
		if (t[l] == '-')
			sgn *= -1;

		if (t[l] >= '0' && t[l] <= '9')
		{
			flg = 1;
			rslt *= 10;
			rslt += (t[l] - '0');
		}
		else if (flg == 1)
			flg = 2;
	}

	if (sgn == -1)
		otpt = -rslt;
	else
		otpt = rslt;

	return (otpt);
}
