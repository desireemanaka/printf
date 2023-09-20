#include "main.h"
#include <stdarg.h>

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - Printf function
 * @format:for format.
 * Return: Printed chars.
 */
int _printf(const char *format, ...)
{
	int a, prnt = 0, prnt_chars = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list lst;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(lst, format);

	for (a = 0; format && format[a] != '\0'; a++)
	{
		if (format[a] != '%')
		{
			buffer[buff_ind++] = format[a];
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);
			/* write(1, &format[i], 1);*/
			prnt_chars++;
		}

		else
		{
			print_buffer(buffer, &buff_ind);
			flags = get_flags(format, &a);
			width = get_width(format, &a, lst);
			precision = get_precision(format, &a, lst);
			size = get_size(format, &a);
			++a;
			prnt = handle_print(format, &a, lst, buffer,
				flags, width, precision, size);
			if (prnt == -1)
				return (-1);
			prnt_chars += prnt;
		}
	}

	print_buffer(buffer, &buff_ind);

	va_end(lst);

	return (prnt_chars);
}

/**
 * print_buffer - It Prints the contents of the buffer if it exist
 * @buffer: An array of chars
 * @buff_ind: Index at which to add next char, represents the length.
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}

