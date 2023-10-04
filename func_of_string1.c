#include "shell.h"

/**
 * _strcat - a function that used to add string to each other.
 * @strin1: 1st string.
 * @strin2: 2nd string.
 *
 * Return: 2nf string pointer.
 */

char *_strcat(char *strin1, char *strin2)
{
	char *m = strin1;

	while (*strin1)
		strin1++;
	while (*strin2)
		*strin1++ = *strin2++;
	*strin1 = *strin2;
	return (m);
}

/**
 * starts_with - a function that used to checks if strin2 begin with strin1.
 * @strin1: 1st string.
 * @strin2: strin2 to check if find in strin1 or not.
 *
 * Return: NULL or address of strin1.
 */

char *starts_with(const char *strin1, const char *strin2)
{
	while (*strin2)
		if (*strin2++ != *strin1++)
			return (NULL);
	return ((char *)strin1);
}

/**
 * _strcmp - a function that used to compare between 2 strings.
 * @x: 1st string.
 * @y: 2nd string.
 * Return: (-1) 1st string less than 2nd string
 *			or (1) 1st string is bigger than 2nd string
 *			or (0) 1st and 2nd string are equal each other.
 */

int _strcmp(char *x, char *y)
{
	while (*x && *y)
	{
		if (*x != *y)
			return (*x - *y);
		x++;
		y++;
	}
	if (*x == *y)
		return (0);
	else
		return (*x < *y ? -1 : 1);
}

/**
 * _strlen - a function that used to get the string length.
 * @m: string.
 *
 * Return: string length.
 */

int _strlen(char *m)
{
	int n = 0;

	if (!m)
		return (0);
	while (*m++)
		n++;
	return (n);
}
