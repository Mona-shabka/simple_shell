#include "shell.h"

/**
 * replace_string - a function that used to replaces string.
 * @old_str: old string address.
 * @new_str: new string.
 * Return: 1 (found) or 0 (fail).
 */

int replace_string(char **old_str, char *new_str)
{
	free(*old_str);
	*old_str = new_str;
	return (1);
}

/**
 * is_chain - a function that used to test char in buffer is certain or not.
 * @information: struct information.
 * @buffer: buffer.
 * @pointer: position address in buffer.
 * Return: 1 (certained chain), 0 (fail).
 */

int is_chain(info_t *information, char *buffer, size_t *pointer)
{
	size_t x = *pointer;

	if (buffer[x] == '|' && buffer[x + 1] == '|')
	{
		buffer[x] = 0;
		x++;
		information->cmd_buf_type = CMD_OR;
	}
	else if (buffer[x] == '&' && buffer[x + 1] == '&')
	{
		buffer[x] = 0;
		x++;
		information->cmd_buf_type = CMD_AND;
	}
	else if (buffer[x] == ';')
	{
		buffer[x] = 0;
		information->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*pointer = x;
	return (1);
}

/**
 * check_chain - a function that used to checks we should continue chaining.
 * @information: struct information.
 * @buffer: buffer
 * @pointer: position address in buffer
 * @x: starting position in buffer.
 * @length: buffer length.
 * Return: Void
 */

void check_chain(info_t *information, char *buffer,
		size_t *pointer, size_t x, size_t length)
{
	size_t n = *pointer;

	if (information->cmd_buf_type == CMD_AND)
	{
		if (information->status)
		{
			buffer[x] = 0;
			n = length;
		}
	}
	if (information->cmd_buf_type == CMD_OR)
	{
		if (!information->status)
		{
			buffer[x] = 0;
			n = length;
		}
	}
	*pointer = n;
}

/**
 * replace_alias - a function that used to replaces an aliases in string.
 * @information: struct information.
 * Return: 1 (found) or 0 (fail).
 */

int replace_alias(info_t *information)
{
	list_t *n_node;
	char *pointer;
	int x;

	for (x = 0; x < 10; x++)
	{
		n_node = node_starts_with(information->alias, information->argv[0], '=');
		if (!n_node)
			return (0);
		free(information->argv[0]);
		pointer = _strchr(n_node->string, '=');
		if (!pointer)
			return (0);
		pointer = _strdup(pointer + 1);
		if (!pointer)
			return (0);
		information->argv[0] = pointer;
	}
	return (1);
}

/**
 * replace_vars - a function that used to replaces vars in string.
 * @information: struct information.
 * Return: 1 (found) or 0 (fail).
 */

int replace_vars(info_t *information)
{
	list_t *n_node;
	int x = 0;

	for (x = 0; information->argv[x]; x++)
	{
		if (information->argv[x][0] != '$' || !information->argv[x][1])
			continue;

		if (!_strcmp(information->argv[x], "$?"))
		{
			replace_string(&(information->argv[x]),
				_strdup(convert_number(information->status, 10, 0)));
			continue;
		}
		if (!_strcmp(information->argv[x], "$$"))
		{
			replace_string(&(information->argv[x]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		n_node = node_starts_with(information->env, &information->argv[x][1], '=');
		if (n_node)
		{
			replace_string(&(information->argv[x]),
				_strdup(_strchr(n_node->string, '=') + 1));
			continue;
		}
		replace_string(&information->argv[x], _strdup(""));

	}
	return (0);
}
