#include "main.h"
/**
 * _printf - function that produces output according to a format.
 * @format: the character string
 * Return: number of characters printed, excluding the null byte
 */

int _printf(const char *format, ...)
{
	int i, printed = 0, char_printed = 0;
	int flags, width, precision, size, buff_index = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buff_index++] = format[i];
			if (buff_index == BUFF_SIZE)
				print_buffer(buffer, &buff_index);
			char_printed++;
		}
		else
		{
			print_buffer(buffer, &buff_index);
			flags = get_flags(format, &i);
			width = get_width(format, &i, list);
			precision = get_precision(format, &i, list);
			size = get_size(format, &i);
			++i;
			printed = handle_print(format, &i, list, buffer,
				flags, width, precision, size);
			if (printed == -1)
				return (-1);
			char_printed += printed;
		}
	}

	print_buffer(buffer, &buff_index);

	va_end(list);

	return (char_printed);
}

/**
 * print_buffer - Prints buffer contents if they exist
 * @buffer: an array of chars
 * @buff_index: index at which to add next char, represents the length.
 */
void print_buffer(char buffer[], int *buff_index)
{
	if (*buff_index > 0)
		write(1, &buffer[0], *buff_index);

	*buff_index = 0;
}
