#include "shell.h"

/**
 * renumber_history - a function that used to renumbers the history.
 * @information: Structure information.
 * Return: the new histcount
 */

int renumber_history(info_t *information)
{
	int x = 0;
	list_t *n_node = information->history;

	while (n_node)
	{
		n_node->number = x++;
		n_node = n_node->next;
	}
	return (information->histcount = x);
}

/**
 * get_history_file - a function that used to gets the history file.
 * @information: struct information.
 * Return: allocated string.
 */

char *get_history_file(info_t *information)
{
	char *n_dir;
	char *buffer;

	n_dir = _getenv(information, "HOME=");
	if (!n_dir)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlen(n_dir) + _strlen(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcpy(buffer, n_dir);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_FILE);
	return (buffer);
}

/**
 * write_history - a function that used to creates a file.
 * @information: struct information.
 * Return: 1 (success) or -1 (fail).
 */

int write_history(info_t *information)
{
	list_t *n_node = NULL;
	ssize_t file;
	char *file_name = get_history_file(information);

	if (!file_name)
		return (-1);
	file = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_name);
	if (file == -1)
		return (-1);
	for (n_node = information->history; n_node; n_node = n_node->next)
	{
		_putsfd(n_node->string, file);
		_putfd('\n', file);
	}
	_putfd(BUF_FLUSH, file);
	close(file);
	return (1);
}

/**
 * read_history - a function that used to reads history from file.
 * @information: struct information.
 * Return: histcount (success), 0 (fail).
 */

int read_history(info_t *information)
{
	int x, lastt = 0, linecounter = 0;
	ssize_t file, rdlength, f_size = 0;
	struct stat st;
	char *buffer = NULL;
	char *file_name = get_history_file(information);

	if (!file_name)
		return (0);

	file = open(file_name, O_RDONLY);
	free(file_name);
	if (file == -1)
		return (0);
	if (!fstat(file, &st))
		f_size = st.st_size;
	if (f_size < 2)
		return (0);
	buffer = malloc(sizeof(char) * (f_size + 1));
	if (!buffer)
		return (0);
	rdlength = read(file, buffer, f_size);
	buffer[f_size] = 0;
	if (rdlength <= 0)
		return (free(buffer), 0);
	close(file);
	for (x = 0; x < f_size; x++)
		if (buffer[x] == '\n')
		{
			buffer[x] = 0;
			build_history_list(information, buffer + lastt, linecounter++);
			lastt = x + 1;
		}
	if (lastt != x)
		build_history_list(information, buffer + lastt, linecounter++);
	free(buffer);
	information->histcount = linecounter;
	while (information->histcount-- >= HIST_MAX)
		delete_node_at_index(&(information->history), 0);
	renumber_history(information);
	return (information->histcount);
}

/**
 * build_history_list - a function that used to adds entry to a history.
 * @information: Structure information.
 * @buffer: buffer.
 * @linecounter: history linecounter.
 * Return: 0.
 */

int build_history_list(info_t *information, char *buffer, int linecounter)
{
	list_t *n_node = NULL;

	if (information->history)
		n_node = information->history;
	add_node_end(&n_node, buffer, linecounter);
	if (!information->history)
		information->history = n_node;
	return (0);
}
