#include "shell.h"

/**
 *_strncpy - to Copies the String.
 *
 *@ddst: copy the Destination String To.
 *
 *@sorc: Source String.
 *
 *@m: Amount Of Chars that will Be Copied.
 *
 *Return: String will be Concatenated.
 */

char *_strncpy(char *ddst, char *sorc, int m)
{
	char *s = ddst;
	int l, k;

	l = 0;
	while (sorc[l] != '\0' && l < m - 1)
	{
		ddst[l] = sorc[l];
		l++;
	}
	if (l < m)
	{
		k = l;
		while (k < m)
		{
			ddst[k] = '\0';
			k++;
		}
	}
	return (s);
}


/**
 **_strncat - Two strings to be Concatenated.
 *
 *@ddst: 1st Str.
 *
 *@sorc: 2nd Str.
 *
 *@m: Amount Of Bytes that will Be optimum Used.
 *
 *Return: Concatenated Str.
 */

char *_strncat(char *ddst, char *sorc, int m)
{
	char *s = ddst;
	int l, k;

	k = 0;
	l = 0;
	while (ddst[l] != '\0')
		l++;
	while (sorc[k] != '\0' && k < m)
	{
		ddst[l] = sorc[k];
		l++;
		k++;
	}
	if (k < m)
		ddst[l] = '\0';
	return (s);
}


/**
 **_strchr - to puts the Character Into the String.
 *
 *@st: String that will Be Parsed
 *
 *@ch: Character that will be Looked For.
 *
 *Return: (st) Pointer To Memory Area st.
 */

char *_strchr(char *st, char ch)
{
	do {
		if (*st == ch)
			return (st);
	} while (*st++ != '\0');

	return (NULL);
}
