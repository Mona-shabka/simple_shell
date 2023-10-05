#include "shell.h"

/**
 * bfree - a function that used to frees pointer.
 * @pointer: pointer address used to free.
 * Return: 0 (fail) or 1 (freed).
 */

int bfree(void **pointer)
{
	if (pointer && *pointer)
	{
		free(*pointer);
		*pointer = NULL;
		return (1);
	}
	return (0);
}
