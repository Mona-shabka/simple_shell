#include "shell.h"

/**
 * find_path - a function that used to finds cmd in path.
 * @n_info: info structure.
 * @n_path: path.
 * @n_cmd: finf cmd.
 * Return: NULL or cmd full path.
 */

char *find_path(info_t *n_info, char *n_path, char *n_cmd)
{
	char *x_path;
	int x = 0;
	int cuurr_pos = 0;

	if (!n_path)
		return (NULL);
	if ((_strlen(n_cmd) > 2) && starts_with(n_cmd, "./"))
	{
		if (is_cmd(n_info, n_cmd))
			return (n_cmd);
	}
	while (1)
	{
		if (!n_path[x] || n_path[x] == ':')
		{
			x_path = dup_chars(n_path, cuurr_pos, x);
			if (!*x_path)
				_strcat(x_path, n_cmd);
			else
			{
				_strcat(x_path, "/");
				_strcat(x_path, n_cmd);
			}
			if (is_cmd(n_info, x_path))
				return (x_path);
			if (!n_path[x])
				break;
			cuurr_pos = x;
		}
		x++;
	}
	return (NULL);
}

/**
 * is_cmd - a function that used to determines if file is executable or not.
 * @n_info: info structure.
 * @n_path: file path.
 * Return: 1 (true) or 0 (false).
 */

int is_cmd(info_t *n_info, char *n_path)
{
	struct stat st;

	(void)n_info;
	if (!n_path || stat(n_path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - a function that used to duplicates characters.
 * @path: string path.
 * @begin: 1st index.
 * @end: end index.
 * Return: new buffer pointer.
 */

char *dup_chars(char *path, int begin, int end)
{
	int x = 0;
	int y = 0;
	static char buffer[1024];

	for (y = 0, x = begin; x < end; x++)
		if (path[x] != ':')
			buffer[y++] = path[x];
	buffer[y] = 0;
	return (buffer);
}
