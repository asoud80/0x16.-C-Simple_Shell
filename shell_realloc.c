#include "shell.h"


/**
 **_memset - to Fills the Memory With Constant Byte.
 *
 *@t: a Pointer To a Memory Area.
 *
 *@p: Byte To Fill *t With
 *
 *@m: Amount Of Bytes To Be Filled.
 *
 *Return: (t) Pointer To a Memory Area t
 */

char *_memset(char *t, char p, unsigned int m)
{
	unsigned int l;

	for (l = 0; l < m; l++)
		t[l] = p;
	return (t);
}


/**
 * ffree - it will Frees the String Of Strings.
 *
 * @bb: the String Of Strings.
 */

void ffree(char **bb)
{
	char **c = bb;

	if (!bb)
		return;
	while (*bb)
		free(*bb++);
	free(c);
}

/**
 * _realloc - to Reallocates Block Of the Memory.
 *
 * @potr: a Pointer To the Previous malloc'ated Block.
 *
 * @od_sze: the Byte Size Of the Previous Block.
 *
 * @nw_sze: the Byte Size Of the New Block.
 * Return: a Pointer To Ol'block
 */

void *_realloc(void *potr, unsigned int od_sze, unsigned int nw_sze)
{
	char *b;

	if (!potr)
		return (malloc(nw_sze));
	if (!nw_sze)
		return (free(potr), NULL);
	if (nw_sze == od_sze)
		return (potr);

	b = malloc(nw_sze);
	if (!b)
		return (NULL);

	od_sze = od_sze < nw_sze ? od_sze : nw_sze;
	while (od_sze--)
		b[od_sze] = ((char *)potr)[od_sze];
	free(potr);
	return (b);
}
