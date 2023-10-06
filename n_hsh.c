#include "shell.h"

/**
 * fork_cmd - a function that used to forks thread to run cmd.
 * @information: struct information.
 * Return: void.
 */

void fork_cmd(info_t *information)
{
	pid_t n_child_pid;

	n_child_pid = fork();
	if (n_child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (n_child_pid == 0)
	{
		if (execve(information->path, information->argv,
					get_environ(information)) == -1)
		{
			free_info(information, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(information->status));
		if (WIFEXITED(information->status))
		{
			information->status = WEXITSTATUS(information->status);
			if (information->status == 126)
				print_error(information, "Permission denied\n");
		}
	}
}

/**
 * hsh - a function that used to main shell loop.
 * @information: struct information.
 * @n_av: .argument vector.
 * Return: 0 (success), 1 (error), or error code.
 */

int hsh(info_t *information, char **n_av)
{
	int builtin_rret = 0;
	ssize_t x = 0;

	while (x != -1 && builtin_rret != -2)
	{
		clear_info(information);
		if (interactive(information))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		x = get_input(information);
		if (x != -1)
		{
			set_info(information, n_av);
			builtin_rret = find_builtin(information);
			if (builtin_rret == -1)
				find_cmd(information);
		}
		else if (interactive(information))
			_putchar('\n');
		free_info(information, 0);
	}
	write_history(information);
	free_info(information, 1);
	if (!interactive(information) && information->status)
		exit(information->status);
	if (builtin_rret == -2)
	{
		if (information->err_num == -1)
			exit(information->status);
		exit(information->err_num);
	}
	return (builtin_rret);
}

/**
 * find_builtin - a function that used to finds a builtin command.
 * @information: struct information.
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */

int find_builtin(info_t *information)
{
	int x, built_in_rret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (x = 0; builtintbl[x].type; x++)
		if (_strcmp(information->argv[0], builtintbl[x].type) == 0)
		{
			information->line_count++;
			built_in_rret = builtintbl[x].func(information);
			break;
		}
	return (built_in_rret);
}

/**
 * find_cmd - a function that used to finds a command in PATH.
 * @information: struct information.
 * Return: void.
 */

void find_cmd(info_t *information)
{
	int x, n;
	char *path = NULL;

	information->path = information->argv[0];
	if (information->linecount_flag == 1)
	{
		information->line_count++;
		information->linecount_flag = 0;
	}
	for (x = 0, n = 0; information->arg[x]; x++)
		if (!is_delim(information->arg[x], " \t\n"))
			n++;
	if (!n)
		return;

	path = find_path(information, _getenv(information, "PATH="),
			information->argv[0]);
	if (path)
	{
		information->path = path;
		fork_cmd(information);
	}
	else
	{
		if ((interactive(information) || _getenv(information, "PATH=")
			|| information->argv[0][0] == '/')
				&& is_cmd(information, information->argv[0]))
			fork_cmd(information);
		else if (*(information->arg) != '\n')
		{
			information->status = 127;
			print_error(information, "not found\n");
		}
	}
}
