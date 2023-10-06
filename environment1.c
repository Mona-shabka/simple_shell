#include "shell.h"

/**
 * populate_env_list - a function that used to populates list.
 * @information: Structure information.
 * Return: 0.
 */

int populate_env_list(info_t *information)
{
	size_t x;
	list_t *n_node = NULL;

	for (x = 0; environ[x]; x++)
		add_node_end(&n_node, environ[x], 0);
	information->env = n_node;
	return (0);
}

/**
 * _myenv - a function that used to prints environment.
 * @information: Structure information.
 * Return: 0.
 */

int _myenv(info_t *information)
{
	print_list_str(information->env);
	return (0);
}

/**
 * _getenv - a function that used to gets the value of environment.
 * @information: Structure information.
 * @n_name: environment name.
 * Return: value.
 */

char *_getenv(info_t *information, const char *n_name)
{
	char *m;
	list_t *n_node = information->env;

	while (n_node)
	{
		m = starts_with(n_node->string, n_name);
		if (m && *m)
			return (m);
		n_node = n_node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - a function that used to initialize a new environment variable.
 * @information: Structure information.
 * Return: 0.
 */

int _mysetenv(info_t *information)
{
	if (information->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(information, information->argv[1], information->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - a function that used to remove environment variable.
 * @information: Structure information.
 * Return: 0.
 */

int _myunsetenv(info_t *information)
{
	int x;

	if (information->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (x = 1; x <= information->argc; x++)
		_unsetenv(information, information->argv[x]);

	return (0);
}
