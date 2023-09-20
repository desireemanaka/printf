#include "main.h"

/************************* PRINT CHAR *************************/

/**
 * print_char - Print a char
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_char(va_list typ, char buffer[],
	int flags, int width, int precision, int size)
{
	char c = va_arg(typ, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}
/***** PRINT A STRING ***********/
/**
 * print_string - Print a string
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_string(va_list typ, char buffer[],
	int flags, int width, int precision, int size)
{
	int len = 0, a;
	char *str = va_arg(typ, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[len] != '\0')
		len++;

	if (precision >= 0 && precision < len)
		len = precision;

	if (width > len)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], len);
			for (a = width - len; a > 0; a--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (a = width - len; a > 0; a--)
				write(1, " ", 1);
			write(1, &str[0], len);
			return (width);
		}
	}

	return (write(1, str, len));
}
/******* PRINT PERCENT SIGN *****/
/**
 * print_percent - Print percent sign
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_percent(va_list typ, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(typ);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}
/*********** PRINT INT *******/
/**
 * print_int - Print integer
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_int(va_list typ, char buffer[],
	int flags, int width, int precision, int size)
{
	int v = BUFF_SIZE - 2;
	int is_ngtv = 0;
	long int b = va_arg(typ, long int);
	unsigned long int numb;

	v = convert_size_number(v, size);

	if (b == 0)
		buffer[v--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	numb = (unsigned long int)b;

	if (b < 0)
	{
		numb = (unsigned long int)((-1) * b);
		is_ngtv = 1;
	}

	while (numb > 0)
	{
		buffer[v--] = (numb % 10) + '0';
		numb /= 10;
	}

	v++;

	return (write_number(is_ngtv, v, buffer, flags, width, precision, size));
	}

/**** PRINT BINARY ****/
/**
 * print_binary - Print unsigned numb
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of char printed.
 */
int print_binary(va_list typ, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int a, b, c, result;
	unsigned int i[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	a = va_arg(typ, unsigned int);
	b = 2147483648; /* (2 ^ 31) */
	i[0] = a / b;
	for (c = 1; c < 32; c++)
	{
		b /= 2;
		a[i] = (a / b) % 2;
	}
	for (c = 0, result = 0, count = 0; c < 32; c++)
	{
		result += i[c];
		if (result || c == 31)
		{
			char z = '0' + i[c];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
