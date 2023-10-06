#include "shell.h"

/**
 * _setenv - a function that used to initialize a new environment variable.
 * @information: Structure information.
 * @variable: string variable.
 * @n_value: string value.
 *  Return: 0.
 */

int _setenv(info_t *information, char *variable, char *n_value)
{
	list_t *n_node;
	char *pointer;
	char *buffer = NULL;

	if (!variable || !n_value)
		return (0);

	buffer = malloc(_strlen(variable) + _strlen(n_value) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, variable);
	_strcat(buffer, "=");
	_strcat(buffer, n_value);
	n_node = information->env;
	while (n_node)
	{
		pointer = starts_with(n_node->string, variable);
		if (pointer && *pointer == '=')
		{
			free(n_node->string);
			n_node->string = buffer;
			information->env_changed = 1;
			return (0);
		}
		n_node = n_node->next;
	}
	add_node_end(&(information->env), buffer, 0);
	free(buffer);
	information->env_changed = 1;
	return (0);
}

/**
 * get_environ - a function that used to returns the string array.
 * @information: Structure information.
 * Return: 0.
 */

char **get_environ(info_t *information)
{
	if (!information->environ || information->env_changed)
	{
		information->environ = list_to_strings(information->env);
		information->env_changed = 0;
	}

	return (information->environ);
}

/**
 * _unsetenv - a function that used to remove environment.
 * @information: Structure information.
 * @variable: the string env var property.
 * Return: 1 (delete) or 0 (fail).
 */

int _unsetenv(info_t *information, char *variable)
{
	size_t x = 0;
	char *pointer;
	list_t *n_node = information->env;

	if (!n_node || !variable)
		return (0);

	while (n_node)
	{
		pointer = starts_with(n_node->string, variable);
		if (pointer && *pointer == '=')
		{
			information->env_changed = delete_node_at_index(&(information->env), x);
			x = 0;
			n_node = information->env;
			continue;
		}
		n_node = n_node->next;
		x++;
	}
	return (information->env_changed);
}
