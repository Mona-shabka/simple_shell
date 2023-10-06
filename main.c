#include "shell.h"

/**
 * main - a function that used to entry point.
 * @ac: argument counter.
 * @av: argument vector.
 * Return: 0 (success) or 1 (error).
 */

int main(int ac, char **av)
{
	int file = 2;
	info_t n_info[] = { INFO_INIT };

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (file)
		: "r" (file));

	if (ac == 2)
	{
		file = open(av[1], O_RDONLY);
		if (file == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		n_info->readfd = file;
	}
	populate_env_list(n_info);
	read_history(n_info);
	hsh(n_info, av);
	return (EXIT_SUCCESS);
}
