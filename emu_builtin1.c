#include "shell.h"

/**
 * _myhelp - a function that used to changes directory.
 * @information: Structure informations.
 * Return: 0.
 */

int _myhelp(info_t *information)
{
	char **array;

	array = information->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*array); /* temp att_unused workaround */
	return (0);
}

/**
 * _myexit - a function that used to exits the shell.
 * @information: Structure informations.
 * Return: (0) info.argv[0] != "exit".
 */

int _myexit(info_t *information)
{
	int quit;

	if (information->argv[1])  /* If there is an exit arguement */
	{
		quit = _erratoi(information->argv[1]);
		if (quit == -1)
		{
			information->status = 2;
			print_error(information, "Illegal number: ");
			_eputs(information->argv[1]);
			_eputchar('\n');
			return (1);
		}
		information->err_num = _erratoi(information->argv[1]);
		return (-2);
	}
	information->err_num = -1;
	return (-2);
}

/**
 * _mycd - a function that used to changes directory.
 * @information: Structure informations.
 * Return: 0.
 */

int _mycd(info_t *information)
{
	int n_chdir_ret;
	char buffer[1024], *n_dir, *string;

	string = getcwd(buffer, 1024);
	if (!string)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!information->argv[1])
	{
		n_dir = _getenv(information, "HOME=");
		if (!n_dir)
			n_chdir_ret =
				chdir((n_dir = _getenv(information, "PWD=")) ? n_dir : "/");
		else
			n_chdir_ret = chdir(n_dir);
	}
	else if (_strcmp(information->argv[1], "-") == 0)
	{
		if (!_getenv(information, "OLDPWD="))
		{
			_puts(string);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(information, "OLDPWD=")), _putchar('\n');
		n_chdir_ret =
			chdir((n_dir = _getenv(information, "OLDPWD=")) ? n_dir : "/");
	}
	else
		n_chdir_ret = chdir(information->argv[1]);
	if (n_chdir_ret == -1)
	{
		print_error(information, "can't cd to ");
		_eputs(information->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(information, "OLDPWD", _getenv(information, "PWD="));
		_setenv(information, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
