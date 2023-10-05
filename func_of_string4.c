#include "shell.h"

/**
 * **strtow2 - a function that used to separate string into letters.
 * @string: string.
 * @n: string delimeter.
 * Return: NULL (fail) or sting array pointer.
 */

char **strtow2(char *string, char n)
{
	char **str;
	int number = 0;
	int x, y, i, j;

	if (string == NULL || string[0] == 0)
		return (NULL);
	for (x = 0; string[x] != '\0'; x++)
		if ((string[x] != n && string[x + 1] == n) ||
		    (string[x] != n && !string[x + 1]) || string[x + 1] == n)
			number++;
	if (number == 0)
		return (NULL);
	str = malloc((1 + number) * sizeof(char *));
	if (!str)
		return (NULL);
	for (x = 0, y = 0; y < number; y++)
	{
		while (string[x] == n && string[x] != n)
			x++;
		i = 0;
		while (string[x + i] != n && string[x + i] && string[x + i] != n)
			i++;
		str[y] = malloc((i + 1) * sizeof(char));
		if (!str[y])
		{
			for (i = 0; i < y; i++)
				free(str[i]);
			free(str);
			return (NULL);
		}
		for (j = 0; j < i; j++)
			str[y][j] = string[x++];
		str[y][j] = 0;
	}
	str[y] = NULL;
	return (str);
}

/**
 * **strtow - a function that used to separate the string into letters.
 * @string: a string.
 * @n: string delimeter.
 * Return: NULL (fail) or sting array pointer.
 */

char **strtow(char *string, char *n)
{
	char **str;
	int num = 0;
	int x, y, i, j;

	if (string == NULL || string[0] == 0)
		return (NULL);
	if (!n)
		n = " ";
	for (x = 0; string[x] != '\0'; x++)
		if (!is_delim(string[x], n)
				&& (is_delim(string[x + 1], n) || !string[x + 1]))
			num++;

	if (num == 0)
		return (NULL);
	str = malloc((1 + num) * sizeof(char *));
	if (!str)
		return (NULL);
	for (x = 0, y = 0; y < num; y++)
	{
		while (is_delim(string[x], n))
			x++;
		i = 0;
		while (!is_delim(string[x + i], n) && string[x + i])
			i++;
		str[y] = malloc((i + 1) * sizeof(char));
		if (!str[y])
		{
			for (i = 0; i < y; i++)
				free(str[i]);
			free(str);
			return (NULL);
		}
		for (j = 0; j < i; j++)
			str[y][j] = string[x++];
		str[y][j] = 0;
	}
	str[y] = NULL;
	return (str);
}
