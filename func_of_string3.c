#include "shell.h"

/**
 **_strchr - a function that used to show where character found in a string.
 *@string: string.
 *@ch: character.
 *Return: pointer.
 */

char *_strchr(char *string, char ch)
{
	do {
		if (*string == ch)
			return (string);
	} while (*string++ != '\0');

	return (NULL);
}

/**
 **_strncat - a function that used to add two strings to each other.
 *@strin1: 1st string.
 *@strin2: 2nd string.
 *@m: the length of letters to be used.
 *Return: string.
 */

char *_strncat(char *strin1, char *strin2, int m)
{
	int x, y;
	char *str = strin1;

	x = 0;
	y = 0;
	while (strin1[x] != '\0')
		x++;
	while (strin2[y] != '\0' && y < m)
	{
		strin1[x] = strin2[y];
		x++;
		y++;
	}
	if (y < m)
		strin1[x] = '\0';
	return (str);
}

/**
 **_strncpy - a function that used to copy a string.
 *@strin1: 1st string.
 *@strin2: original string.
 *@m: the length of characters to be copied.
 *Return: copied string.
 */

char *_strncpy(char *strin1, char *strin2, int m)
{
	int x, y;
	char *str = strin1;

	x = 0;
	while (strin2[x] != '\0' && x < m - 1)
	{
		strin1[x] = strin2[x];
		x++;
	}
	if (x < m)
	{
		y = x;
		while (y < m)
		{
			strin1[y] = '\0';
			y++;
		}
	}
	return (str);
}
