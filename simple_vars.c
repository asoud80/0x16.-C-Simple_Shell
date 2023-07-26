#include "shell.h"

/**
 * is_chain - Test if Current Character In the Buffer IS Chain Delim or not
 *
 * @info: struct Parameter
 *
 * @buf: Character Buffer
 *
 * @p: to Address the Current Position In Buffer
 * Return: in case Chain Delim return 1, else 0
 */

int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}


/**
 * check_chain - to Checks if Should we Continue to Chain Based ON Last Status
 *
 * @info: struct Parameter
 *
 * @buf: Character Buffer
 *
 * @p: Address Of Current Position In the Buffer
 *
 * @i: to Starting Position into the Buffer
 *
 * @len: the Len of te Buffer
 * Return: Void
 */

void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_alias - to Replaces the Aliases Into tokenized String
 *
 * @info: atruct Parameter
 * Return: in case of  Replaced return 1, else 0
 */

int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}


/**
 * replace_vars - it will Replace Variables Into tokenized String
 *
 * @info: struct Parameter
 * Return: in case of  Replaced return 1, else 0
 */

int replace_vars(info_t *info)
{
	list_t *node;
	int i = 0;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - string will be Replaceed
 *
 * @old: to Address Of Old Str
 *
 * @new: a New String
 * Return: in case of  Replaced return 1, else 0
 */

int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
