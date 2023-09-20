#include "main.h"
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - Printf function
 * @format: format.
 * Return: Printed chars.
 */
int _printf(const char *format, ...)
{
	int c, prnt = 0, prnt_chars = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list lst;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(lst, format);

	for (c = 0; format && format[c] != '\0'; c++)
	{
		if (format[c] != '%')
		{
			buffer[buff_ind++] = format[c];
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);
			/* write(1, &format[c], 1);*/
			prnt_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			flags = get_flags(format, &c);
			width = get_width(format, &c, lst);
			precision = get_precision(format, &c, lst);
			size =  get_size(format, &c);
			++c;
			prnt =  handle_print(format, &c, lst, buffer,
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
 * print_buffer - Prints the contents of the buffer if it exist
 * @buffer: Array of chars
 * @buff_ind: Index at which to add next char, represents the length.
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}
