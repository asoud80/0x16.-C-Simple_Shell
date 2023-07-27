#include "shell.h"


/**
 * get_environ - to Returns String Arr Copy Of the Environment
 *
 * @info: a Structure that Containing a Potential Argus & Used for Maintaining
 *
 *         the Constant Function Prototype
 *
 * Return: 0 always
 */

char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}


/**
 * _unsetenv - to remove the Environ Var
 *
 * @info: a Structure that Containing a Potential Argus & Used for Maintaining
 *
 *        the Constant Function Prototype
 *
 *  Return: in case of Delete return 1, Otherwise 0
 *
 * @var: String Environment Variable Property
 */

int _unsetenv(info_t *info, char *var)
{
	size_t i = 0;
	char *p;
	list_t *node = info->env;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}


/**
 * _setenv - It will initialize the  New Environ Variable
 *
 *             Or for Modifing the Existing One
 *
 * @info: a Structure that Containing a Potential Argus & Used for Maintaining
 *
 *       the Constant Function Prototype
 *
 * @var: String Environment Variable Property
 *
 * @value: String Environment Variable Value
 *
 *  Return: 0 always
 */

int _setenv(info_t *info, char *var, char *value)
{
	list_t *node;
	char *p;
	char *buf = NULL;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
