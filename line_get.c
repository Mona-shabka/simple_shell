#include "shell.h"

/**
 * sigintHandler - a function that used to blocks ctrl-C.
 * @sig_num: signal number.
 * Return: void.
 */

void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

/**
 * input_buf - a function that used to buffers chained commands.
 * @information: struct information.
 * @buffer: buffer address.
 * @length: length address.
 * Return: bytes.
 */

ssize_t input_buf(info_t *information, char **buffer, size_t *length)
{
	size_t length_p = 0;
	ssize_t s = 0;

	if (!*length)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		s = getline(buffer, &length_p, stdin);
#else
		s = _getline(information, buffer, &length_p);
#endif
		if (s > 0)
		{
			if ((*buffer)[s - 1] == '\n')
			{
				(*buffer)[s - 1] = '\0';
				s--;
			}
			information->linecount_flag = 1;
			remove_comments(*buffer);
			build_history_list(information, *buffer, information->histcount++);
			{
				*length = s;
				information->cmd_buf = buffer;
			}
		}
	}
	return (s);
}

/**
 * get_input - a function that used to gives line minus the newline.
 * @information: struct information.
 * Return: bytes.
 */

ssize_t get_input(info_t *information)
{
	static char *buffer;
	static size_t x, y, length;
	ssize_t m = 0;
	char **buffer_p = &(information->arg), *p;

	_putchar(BUF_FLUSH);
	m = input_buf(information, &buffer, &length);
	if (m == -1)
		return (-1);
	if (length)
	{
		y = x;
		p = buffer + x;

		check_chain(information, buffer, &y, x, length);
		while (y < length)
		{
			if (is_chain(information, buffer, &y))
				break;
			y++;
		}

		x = y + 1;
		if (x >= length)
		{
			x = length = 0;
			information->cmd_buf_type = CMD_NORM;
		}
		*buffer_p = p;
		return (_strlen(p));
	}
	*buffer_p = buffer;
	return (m);
}

/**
 * read_buf - a function that used to reads buffer.
 * @information: information of struct.
 * @buffer: buffer.
 * @m: size.
 * Return: n.
 */

ssize_t read_buf(info_t *information, char *buffer, size_t *m)
{
	ssize_t n = 0;

	if (*m)
		return (0);
	n = read(information->readfd, buffer, READ_BUF_SIZE);
	if (n >= 0)
		*m = n;
	return (n);
}

/**
 * _getline - a function that used to gives the next line of input.
 * @information: struct information.
 * @pointer: pointer address to buffer.
 * @n_length: size of pointer buffer.
 * Return: m.
 */

int _getline(info_t *information, char **pointer, size_t *n_length)
{
	static size_t x, n_len;
	size_t y;
	ssize_t z = 0, m = 0;
	static char buffer[READ_BUF_SIZE];
	char *ptr = NULL, *new_ptr = NULL, *character;

	ptr = *pointer;
	if (ptr && n_length)
		m = *n_length;
	if (x == n_len)
		x = n_len = 0;

	z = read_buf(information, buffer, &n_len);
	if (z == -1 || (z == 0 && n_len == 0))
		return (-1);

	character = _strchr(buffer + x, '\n');
	y = character ? 1 + (unsigned int)(character - buffer) : n_len;
	new_ptr = _realloc(ptr, m, m ? m + y : y + 1);
	if (!new_ptr)
		return (ptr ? free(ptr), -1 : -1);

	if (m)
		_strncat(new_ptr, buffer + x, y - x);
	else
		_strncpy(new_ptr, buffer + x, y - x + 1);

	m += y - x;
	x = y;
	ptr = new_ptr;

	if (n_length)
		*n_length = m;
	*pointer = ptr;
	return (m);
}
