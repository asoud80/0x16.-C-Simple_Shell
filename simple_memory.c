#include "shell.h"


/**
 * bfree - to Frees the Pointer & NULLs Address.
 *
 * @potr: to Address Of a Pointer To be free
 * Return: in case of free return 1, Otherwise  0.
 */

int bfree(void **potr)
{
	if (potr && *potr)
	{
		free(*potr);
		*potr = NULL;
		return (1);
	}
	return (0);
}
