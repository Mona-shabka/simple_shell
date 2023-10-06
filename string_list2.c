#include "shell.h"

/**
 * get_node_index - a function that used to gets the node index.
 * @head: head list pointer.
 * @n_node: node pointer.
 * Return: node index or -1.
 */
ssize_t get_node_index(list_t *head, list_t *n_node)
{
	size_t x = 0;

	while (head)
	{
		if (head == n_node)
			return (x);
		head = head->next;
		x++;
	}
	return (-1);
}

/**
 * list_len - a function that used to determines length of linked list.
 * @m: pointer to first node.
 * Return: list size.
 */

size_t list_len(const list_t *m)
{
	size_t x = 0;

	while (m)
	{
		m = m->next;
		x++;
	}
	return (x);
}

/**
 * list_to_strings - a function that used to returns an array.
 * @head: pointer to first node.
 * Return: strings array.
 */

char **list_to_strings(list_t *head)
{
	list_t *n_node = head;
	size_t x = list_len(head);
	size_t y;
	char **n_strs;
	char *n_str;

	if (!head || !x)
		return (NULL);
	n_strs = malloc(sizeof(char *) * (x + 1));
	if (!n_strs)
		return (NULL);
	for (x = 0; n_node; n_node = n_node->next, x++)
	{
		n_str = malloc(_strlen(n_node->string) + 1);
		if (!n_str)
		{
			for (y = 0; y < x; y++)
				free(n_strs[y]);
			free(n_strs);
			return (NULL);
		}

		n_str = _strcpy(n_str, n_node->string);
		n_strs[x] = n_str;
	}
	n_strs[x] = NULL;
	return (n_strs);
}


/**
 * print_list - a function that used to prints all elements.
 * @m: pointer to first node.
 * Return: list size.
 */

size_t print_list(const list_t *m)
{
	size_t x = 0;

	while (m)
	{
		_puts(convert_number(m->number, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(m->string ? m->string : "(nil)");
		_puts("\n");
		m = m->next;
		x++;
	}
	return (x);
}

/**
 * node_starts_with - a function that used to returns node.
 * @n_node: pointer to list head.
 * @pre_fix: string.
 * @character: next character after pre_fix.
 * Return: node or null.
 */

list_t *node_starts_with(list_t *n_node, char *pre_fix, char character)
{
	char *point = NULL;

	while (n_node)
	{
		point = starts_with(n_node->string, pre_fix);
		if (point && ((character == -1) || (*point == character)))
			return (n_node);
		n_node = n_node->next;
	}
	return (NULL);
}
