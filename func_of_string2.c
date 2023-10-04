#include "shell.h"

/**
 * _putchar - a function that used to writes letters.
 * @m: letter.
 * Return: (1) success or (-1) return.
 */

int _putchar(char m)
{
	static int x;
	static char buffer[WRITE_BUF_SIZE];

	if (m == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(1, buffer, x);
		x = 0;
	}
	if (m != BUF_FLUSH)
		buffer[x++] = m;
	return (1);
}

/**
 *_puts - a function that used to prints string.
 *@string: string.
 * Return: void.
 */

void _puts(char *string)
{
	int x = 0;

	if (!string)
		return;
	while (string[x] != '\0')
	{
		_putchar(string[x]);
		x++;
	}
}

/**
 * _strdup -  a function that used to repated string twice.
 * @string: string to repated twice.
 * Return: repeated string pointer.
 */
char *_strdup(const char *string)
{
	int len = 0;
	char *m;

	if (string == NULL)
		return (NULL);
	while (*string++)
		len++;
	m = malloc(sizeof(char) * (len + 1));
	if (!m)
		return (NULL);
	for (len++; len--;)
		m[len] = *--string;
	return (m);
}

/**
 * _strcpy - a function that used to copy 2 strings.
 * @strin1: 1st string.
 * @strin2: 2nd string.
 * Return: strin1 pointer.
 */

char *_strcpy(char *strin1, char *strin2)
{
	int m = 0;

	if (strin1 == strin2 || strin2 == 0)
		return (strin1);
	while (strin2[m])
	{
		strin1[m] = strin2[m];
		m++;
	}
	strin1[m] = 0;
	return (strin1);
}
