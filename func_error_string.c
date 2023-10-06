#include "shell.h"

/**
 *_putsfd - a function that used to prints string.
 * @s: string.
 * @file: file that write to.
 * Return: characters numbers.
 */

int _putsfd(char *s, int file)
{
	int l = 0;

	if (!s)
		return (0);
	while (*s)
	{
		l += _putfd(*s++, file);
	}
	return (l);
}

/**
 *_eputs - a function that used to prints string.
 * @s: string.
 * Return: void.
 */

void _eputs(char *s)
{
	int m = 0;

	if (!s)
		return;
	while (s[m] != '\0')
	{
		_eputchar(s[m]);
		m++;
	}
}

/**
 * _eputchar - a function that used to writes character.
 * @character: character.
 * Return: 1 (success), -1 (return).
 */

int _eputchar(char character)
{
	static char buf[WRITE_BUF_SIZE];
	static int m;

	if (character == BUF_FLUSH || m >= WRITE_BUF_SIZE)
	{
		write(2, buf, m);
		m = 0;
	}
	if (character != BUF_FLUSH)
		buf[m++] = character;
	return (1);
}

/**
 * _putfd - a function that used to writes character.
 * @character: character.
 * @file: file that write to.
 * Return: 1 (success), -1 (return).
 */

int _putfd(char character, int file)
{
	static char buf[WRITE_BUF_SIZE];
	static int x;

	if (character == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(file, buf, x);
		x = 0;
	}
	if (character != BUF_FLUSH)
		buf[x++] = character;
	return (1);
}
