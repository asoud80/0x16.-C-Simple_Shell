#include "shell.h"


/**
 * **strtow - to Splits the String to Words & repeat Dlimiters that was Ignored
 *
 * @sr: an Input String.
 *
 * @lm: Delimeter String
 *
 * Return: the Pointer To Array Of Srings, Or NULL in a Failure
 */

char **strtow(char *sr, char *lm)
{
	char **t;
	int l, m, n, o, Nmword = 0;

	if (sr == NULL || sr[0] == 0)
		return (NULL);
	if (!lm)
		lm = " ";
	for (l = 0; sr[l] != '\0'; l++)
		if (!is_delim(sr[l], lm) && (is_delim(sr[l + 1], lm) || !sr[l + 1]))
			Nmword++;

	if (Nmword == 0)
		return (NULL);
	t = malloc((1 + Nmword) * sizeof(char *));
	if (!t)
		return (NULL);
	for (l = 0, m = 0; m < Nmword; m++)
	{
		while (is_delim(sr[l], lm))
			l++;
		n = 0;
		while (!is_delim(sr[l + n], lm) && sr[l + n])
			n++;
		t[m] = malloc((n + 1) * sizeof(char));
		if (!t[m])
		{
			for (n = 0; n < m; n++)
				free(t[n]);
			free(t);
			return (NULL);
		}
		for (o = 0; o < n; o++)
			t[m][o] = sr[l++];
		t[m][o] = 0;
	}
	t[m] = NULL;
	return (t);
}


/**
 * **strtow2 - to Splits the String to Words.
 *
 * @sr: an Input String.
 *
 * @lm: Delimeter
 *
 * Return: Pointer To Array Of Strings, Or NULL in Failure.
 */

char **strtow2(char *sr, char lm)
{
	char **t;
	int l, m, n, o, Nmword = 0;

	if (sr == NULL || sr[0] == 0)
		return (NULL);
	for (l = 0; sr[l] != '\0'; l++)
		if ((sr[l] != lm && sr[l + 1] == lm) ||
		    (sr[l] != lm && !sr[l + 1]) || sr[l + 1] == lm)
			Nmword++;
	if (Nmword == 0)
		return (NULL);
	t = malloc((1 + Nmword) * sizeof(char *));
	if (!t)
		return (NULL);
	for (l = 0, m = 0; m < Nmword; m++)
	{
		while (sr[l] == lm && sr[l] != lm)
			l++;
		n = 0;
		while (sr[l + n] != lm && sr[l + n] && sr[l + n] != lm)
			n++;
		t[m] = malloc((n + 1) * sizeof(char));
		if (!t[m])
		{
			for (n = 0; n < m; n++)
				free(t[n]);
			free(t);
			return (NULL);
		}
		for (o = 0; o < n; o++)
			t[m][o] = sr[l++];
		t[m][o] = 0;
	}
	t[m] = NULL;
	return (t);
}
