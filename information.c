#include "shell.h"

/**
 * free_info - a function that used to frees info_t struct.
 * @information: struct information.
 * @n_all: true (freed).
 */

void free_info(info_t *information, int n_all)
{
	ffree(information->argv);
	information->argv = NULL;
	information->path = NULL;
	if (n_all)
	{
		if (!information->cmd_buf)
			free(information->arg);
		if (information->env)
			free_list(&(information->env));
		if (information->history)
			free_list(&(information->history));
		if (information->alias)
			free_list(&(information->alias));
		ffree(information->environ);
			information->environ = NULL;
		bfree((void **)information->cmd_buf);
		if (information->readfd > 2)
			close(information->readfd);
		_putchar(BUF_FLUSH);
	}
}

/**
 * clear_info - a function that used to initializes info_t struct.
 * @information: struct information.
 */

void clear_info(info_t *information)
{
	information->arg = NULL;
	information->argv = NULL;
	information->path = NULL;
	information->argc = 0;
}

/**
 * set_info - a function that used to initializes struct.
 * @information: struct information.
 * @n_av: argument vector.
 */

void set_info(info_t *information, char **n_av)
{
	int y = 0;

	information->fname = n_av[0];
	if (information->arg)
	{
		information->argv = strtow(information->arg, " \t");
		if (!information->argv)
		{

			information->argv = malloc(sizeof(char *) * 2);
			if (information->argv)
			{
				information->argv[0] = _strdup(information->arg);
				information->argv[1] = NULL;
			}
		}
		for (y = 0; information->argv && information->argv[y]; y++)
			;
		information->argc = y;

		replace_alias(information);
		replace_vars(information);
	}
}
