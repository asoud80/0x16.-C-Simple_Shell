#include "shell.h"


/**
 * _myhistory - to Displays History List, only One Command By the Line Preceded
 *
 *	With a Line Numbs that Starting with 0.
 *
 * @info: a structure that Containing a Potential Argums & used for Maintaining
 *
 *	the Constant Function Prototype.
 *  Return: 0 always
 */

int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}


/**
 * unset_alias - to Sets an Alias To a String
 *
 * @info: a Parameter Struct
 *
 * @strg: a String Alias
 * Return:in success 0 always, in Error 1
 */

int unset_alias(info_t *info, char *strg)
{
	int ret;
	char *b, d;

	b = _strchr(strg, '=');
	if (!b)
		return (1);
	d = *b;
	*b = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, strg, -1)));
	*b = d;
	return (ret);
}


/**
 * set_alias - to Sets an Alias To the String
 *
 * @info: a Parameter Struct
 *
 * @strg: String Alias
 * Return: in success 0 always, in Error 1
 */

int set_alias(info_t *info, char *strg)
{
	char *p;

	p = _strchr(strg, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, strg));

	unset_alias(info, strg);
	return (add_node_end(&(info->alias), strg, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */

int print_alias(list_t *node)
{
	char *b = NULL, *c = NULL;

	if (node)
	{
		b = _strchr(node->strg, '=');
		for (c = node->strg; c <= b; c++)
			_putchar(*c);
		_putchar('\'');
		_puts(b + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @info: a structure that Containing a Potential Argums & used for Maintaining
 *
 *  Return: 0 always
 */

int _myalias(info_t *info)
{
	list_t *node = NULL;
	int l = 0;
	char *b = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (l = 1; info->argv[l]; l++)
	{
		b = _strchr(info->argv[l], '=');
		if (b)
			set_alias(info, info->argv[l]);
		else
			print_alias(node_starts_with(info->alias, info->argv[l], '='));
	}

	return (0);
}
