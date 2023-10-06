#include "shell.h"

/**
 * _myalias - a function that used to mimics the alias builtin.
 * @information: Structure information.
 *  Return: 0.
 */

int _myalias(info_t *information)
{
	int x = 0;
	list_t *n_node = NULL;
	char *m = NULL;

	if (information->argc == 1)
	{
		n_node = information->alias;
		while (n_node)
		{
			print_alias(n_node);
			n_node = n_node->next;
		}
		return (0);
	}
	for (x = 1; information->argv[x]; x++)
	{
		m = _strchr(information->argv[x], '=');
		if (m)
			set_alias(information, information->argv[x]);
		else
			print_alias(node_starts_with(information->alias,
						information->argv[x], '='));
	}

	return (0);
}

/**
 * _myhistory - a function that used to displays the history list.
 * @information: Structure information.
 *  Return: 0.
 */

int _myhistory(info_t *information)
{
	print_list(information->history);
	return (0);
}

/**
 * unset_alias - a function that used to sets alias to string.
 * @information: structure information.
 * @string: string.
 * Return: Always 0 on success, 1 on error
 */

int unset_alias(info_t *information, char *string)
{
	int r;
	char m;
	char *c;

	c = _strchr(string, '=');
	if (!c)
		return (1);
	m = *c;
	*c = 0;
	r = delete_node_at_index(&(information->alias),
		get_node_index(information->alias,
			node_starts_with(information->alias, string, -1)));
	*c = m;
	return (r);
}

/**
 * set_alias - a function that used to sets alias to string.
 * @information: structure information.
 * @string: string.
 * Return: 0 (success) or 1 (error).
 */

int set_alias(info_t *information, char *string)
{
	char *m;

	m = _strchr(string, '=');
	if (!m)
		return (1);
	if (!*++m)
		return (unset_alias(information, string));

	unset_alias(information, string);
	return (add_node_end(&(information->alias), string, 0) == NULL);
}

/**
 * print_alias - a function that used to prints alias string.
 * @n_node: the alias node.
 * Return: 0 (success) or 1 (error).
 */

int print_alias(list_t *n_node)
{
	char *n = NULL;
	char *m = NULL;

	if (n_node)
	{
		m = _strchr(n_node->string, '=');
		for (n = n_node->string; n <= m; n++)
			_putchar(*n);
		_putchar('\'');
		_puts(m + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}
