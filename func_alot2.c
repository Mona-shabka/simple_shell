#include "shell.h"

/**
 * remove_comments - a function that used to replaces
 *			first instance of '#' with '\0'.
 * @buffer: string address.
 * Return: 0.
 */

void remove_comments(char *buffer)
{
	int i;

	for (i = 0; buffer[i] != '\0'; i++)
		if (buffer[i] == '#' && (!i || buffer[i - 1] == ' '))
		{
			buffer[i] = '\0';
			break;
		}
}

/**
 * _erratoi - a function that used to converts a string to number.
 * @string: string.
 * Return: -1 (error), 0 (numbers), or converted number otherwise.
 */

int _erratoi(char *string)
{
	unsigned long int get = 0;
	int x = 0;

	if (*string == '+')
		string++;
	for (x = 0;  string[x] != '\0'; x++)
	{
		if (string[x] >= '0' && string[x] <= '9')
		{
			get *= 10;
			get += (string[x] - '0');
			if (get > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (get);
}

/**
 * print_error - a function that used to prints message of error.
 * @m: parameter and give information.
 * @string: string has error.
 * Return: -1 (error), 0 (numbers), or converted number otherwise.
 */

void print_error(info_t *m, char *string)
{
	_eputs(m->fname);
	_eputs(": ");
	print_d(m->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(m->argv[0]);
	_eputs(": ");
	_eputs(string);
}

/**
 * print_d - a function that used to prints a decimal number.
 * @m: input.
 * @file: file.
 * Return: printed characters number.
 */

int print_d(int m, int file)
{
	int x, counter = 0;
	unsigned int a, c;
	int (*__putchar)(char) = _putchar;

	if (file == STDERR_FILENO)
		__putchar = _eputchar;
	if (m < 0)
	{
		a = -m;
		__putchar('-');
		counter++;
	}
	else
		a = m;
	c = a;
	for (x = 1000000000; x > 1; x /= 10)
	{
		if (a / x)
		{
			__putchar('0' + c / x);
			counter++;
		}
		c %= x;
	}
	__putchar('0' + c);
	counter++;
	return (counter);
}

/**
 * convert_number - a function that used to convert function.
 * @number: number.
 * @b: base.
 * @f: argument flags.
 * Return: string.
 */

char *convert_number(long int number, int b, int f)
{
	char m_sign = 0;
	char *pointer;
	unsigned long x = number;
	static char *m_array;
	static char buf[50];

	if (!(f & CONVERT_UNSIGNED) && number < 0)
	{
		x = -number;
		m_sign = '-';
	}
	m_array = f & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	pointer = &buf[49];
	*pointer = '\0';

	do	{
		*--pointer = m_array[x % b];
		x /= b;
	} while (x != 0);

	if (m_sign)
		*--pointer = m_sign;
	return (pointer);
}
