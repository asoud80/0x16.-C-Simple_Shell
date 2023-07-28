#include "shell.h"

/**
 * _strlen - it will Returns Length Of the String
 *
 * @s: String which it's Length To Check.
 * Return: Integer Length Of String
 */


int _strlen(char *s)
{
	int c = 0;

	if (!s)
		return (0);

	while (*s++)
		c++;
	return (c);
}


/**
 * _strcmp - it Performs Comparison for 2 Strangs
 *
 * @s1: 1st String.
 * @s2: 2nd String.
 * Return: in case s1 < s2 -ve, in case s1 > s2 +ve, otherwise zero If s1 == s2
 */


int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}


/**
 * starts_with - it will Checks whether the brick Starts With wall.
 *
 * @wall: Search about the String.
 *
 * @brick: find the Substring
 *
 * Return: Address Of Next Character Of wall Or NULL.
 */

char *starts_with(const char *wall, const char *brick)
{
	while (*brick)
		if (*brick++ != *wall++)
			return (NULL);
	return ((char *)wall);
}


/**
 * _strcat - Two Strings to be Concatenated
 *
 * @ddst: Destination Buffer.
 *
 * @sorc: Source Buffer
 *
 * Return: Pointer To Destination Buffer
 */

char *_strcat(char *ddst, char *sorc)
{
	char *ret = ddst;

	while (*ddst)
		ddst++;
	while (*sorc)
		*ddst++ = *sorc++;
	*ddst = *sorc;
	return (ret);
}
