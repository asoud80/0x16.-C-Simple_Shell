#include "shell.h"


/**
 * _strcat - concatnate TWO Strings
 * @dest: destination string
 * @src: the origin String
 *
 * Return: 0 always
 */

char *_strcat(char *dest, char *src)
{
	int i, j = 0;

	for (i = 0; dest[i] != '\0'; i++)
	{
	}
	for (j = 0; src[j] != '\0'; j++)
	{
		dest[i] = src[j];
		i++;

	}
	dest[i] = '\0';
return (dest);
}

/**
 * _strcmp - TWO Strings to be compared
 * @s1: String
 *
 * @s2: another one String
 * Return: Many Returns
 */


int _strcmp(char *s1, char *s2)
{
	int i = 0;
	int val;

	while (s1[i] != 0 && s2[i] != 0 && s1[i] == s2[i])
		i++;
val = s1[i] - s2[i];
return (val);

}


/**
 * _strlen - to Get Size Of String
 *
 * @s: String To be Measured
 *
 * Return: Length Of String
 */


int _strlen(char *s)
{
	int i;

	for (i = 0; s[i] != 0; i++)
		;

	return (i);
}


/**
 *_strncmp -  a Function which Compares TWO Strings

 *@s1: first String

 *@s2: Second String

 *@n: NUMS Of Char

 * Return: Diference between them
 */



size_t _strncmp(char *s1, char *s2, size_t n)
{
	size_t i, j;

	for (j = 0; s1[j] != '\0' && j < n; j++)
	{
		i = s1[j] - s2[j];

		if (i != 0)
		{
			return (i);
		}
	}
	return (0);
}


/**
 * _strcpy - it will Copy String that Pointed To By source to destination
 *
 * @dest: the Destination Of Copy
 *
 * @src: the Source Of copy
 * Return: Character Pointer To Destination
 */


char *_strcpy(char *dest, char *src)
{
	int i = 0;

	for (i = 0; src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
	dest[i + 1] = 0;
	return (dest);
}
