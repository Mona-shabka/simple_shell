#include "shell.h"

/**
 * free_list - a function that used to frees all nodes.
 * @head_pointer: address pointer to head node.
 * Return: void.
 */

void free_list(list_t **head_pointer)
{
	list_t *n_node, *next_n_node, *head_node;

	if (!head_pointer || !*head_pointer)
		return;
	head_node = *head_pointer;
	n_node = head_node;
	while (n_node)
	{
		next_n_node = n_node->next;
		free(n_node->string);
		free(n_node);
		n_node = next_n_node;
	}
	*head_pointer = NULL;
}

/**
 * add_node - a function that used to adds a node to begin of the list.
 * @head: address pointer to head node.
 * @string: string.
 * @number: node index.
 * Return: list size.
 */

list_t *add_node(list_t **head, const char *string, int number)
{
	list_t *neww_head;

	if (!head)
		return (NULL);
	neww_head = malloc(sizeof(list_t));
	if (!neww_head)
		return (NULL);
	_memset((void *)neww_head, 0, sizeof(list_t));
	neww_head->number = number;
	if (string)
	{
		neww_head->string = _strdup(string);
		if (!neww_head->string)
		{
			free(neww_head);
			return (NULL);
		}
	}
	neww_head->next = *head;
	*head = neww_head;
	return (neww_head);
}

/**
 * add_node_end - a function that used to adds a node to the end of the list.
 * @head: address pointer to head.
 * @string: string.
 * @number: node index.
 * Return: list size.
 */

list_t *add_node_end(list_t **head, const char *string, int number)
{
	list_t *neww_node;
	list_t *n_node;

	if (!head)
		return (NULL);

	n_node = *head;
	neww_node = malloc(sizeof(list_t));
	if (!neww_node)
		return (NULL);
	_memset((void *)neww_node, 0, sizeof(list_t));
	neww_node->number = number;
	if (string)
	{
		neww_node->string = _strdup(string);
		if (!neww_node->string)
		{
			free(neww_node);
			return (NULL);
		}
	}
	if (n_node)
	{
		while (n_node->next)
			n_node = n_node->next;
		n_node->next = neww_node;
	}
	else
		*head = neww_node;
	return (neww_node);
}

/**
 * print_list_str - a function that used to prints only the string element.
 * @m: pointer to first node.
 * Return: list size.
 */

size_t print_list_str(const list_t *m)
{
	size_t x = 0;

	while (m)
	{
		_puts(m->string ? m->string : "(nil)");
		_puts("\n");
		m = m->next;
		x++;
	}
	return (x);
}

/**
 * delete_node_at_index - a function that used to deletes node at given point.
 * @head: address pointer to first node.
 * @point: node point to delete.
 * Return: 1 (success) or 0 (fail).
 */

int delete_node_at_index(list_t **head, unsigned int point)
{
	list_t *n_node;
	list_t *previous_node;
	unsigned int x = 0;

	if (!head || !*head)
		return (0);

	if (!point)
	{
		n_node = *head;
		*head = (*head)->next;
		free(n_node->string);
		free(n_node);
		return (1);
	}
	n_node = *head;
	while (n_node)
	{
		if (x == point)
		{
			previous_node->next = n_node->next;
			free(n_node->string);
			free(n_node);
			return (1);
		}
		x++;
		previous_node = n_node;
		n_node = n_node->next;
	}
	return (0);
}
