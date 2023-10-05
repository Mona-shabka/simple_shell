#include "shell.h"

/**
 * ffree - a function that used to frees string.
 * @string: string.
 */

void ffree(char **string)
{
	char **m = string;

	if (!string)
		return;
	while (*string)
		free(*string++);
	free(m);
}

/**
 * _realloc - a function that used to reallocates memory.
 * @pointer: previous mallocated pointer.
 * @old: previous block size.
 * @new: new block size.
 * Return: pointer.
 */

void *_realloc(void *pointer, unsigned int old, unsigned int new)
{
	char *m;

	if (!pointer)
		return (malloc(new));
	if (!new)
		return (free(pointer), NULL);
	if (new == old)
		return (pointer);

	m = malloc(new);
	if (!m)
		return (NULL);

	old = old < new ? old : new;
	while (old--)
		m[old] = ((char *)pointer)[old];
	free(pointer);
	return (m);
}

/**
 **_memset - a function that used to complete memory with bytes.
 *@m: the memory area pointer.
 *@m_byte: byte to fill.
 *@amount: the bytes amount.
 *Return: a memory area pointer.
 */

char *_memset(char *m, char m_byte, unsigned int amount)
{
	unsigned int x;

	for (x = 0; x < amount; x++)
		m[x] = m_byte;
	return (m);
}
