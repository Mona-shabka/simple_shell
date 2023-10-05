#include "shell.h"

/**
 *_atoi - a function that used to converts a string number.
 *@string: converted string.
 *Return: 0 (no number) or converted number.
 */

int _atoi(char *string)
{
	unsigned int get = 0;
	int s = 1, f = 0;
	int x, o;

	for (x = 0;  string[x] != '\0' && f != 2; x++)
	{
		if (string[x] == '-')
			s *= -1;

		if (string[x] >= '0' && string[x] <= '9')
		{
			f = 1;
			get *= 10;
			get += (string[x] - '0');
		}
		else if (f == 1)
			f = 2;
	}

	if (s == -1)
		o = -get;
	else
		o = get;

	return (o);
}

/**
 * interactive - a function that used to back true in interactive mode.
 * @m: address of structure.
 * Return: 1 (interactive) or 0 (fail).
 */

int interactive(info_t *m)
{
	return (isatty(STDIN_FILENO) && m->readfd <= 2);
}

/**
 * is_delim - a function that used to checks certain character.
 * @character: chected charachter.
 * @certain: certain string.
 * Return: 1 (true) or 0 (false).
 */

int is_delim(char character, char *certain)
{
	while (*certain)
		if (*certain++ == character)
			return (1);
	return (0);
}

/**
 *_isalpha - a function that used to checks alphabetic character.
 *@character: character.
 *Return: 1 (alphabetic) or 0 (fail).
 */

int _isalpha(int character)
{
	if ((character >= 'a' && character <= 'z')
			|| (character >= 'A' && character <= 'Z'))
		return (1);
	else
		return (0);
}
