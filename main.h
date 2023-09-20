#ifndef MAIN_H
#define MAIN_H

int print_char(va_list typ, char buffer[],
        int flags, int width, int precision, int size);

int print_string(va_list typ, char buffer[],
        int flags, int width, int precision, int size);

int print_percent(va_list typ, char buffer[],
        int flags, int width, int precision, int size);

int print_int(va_list typ, char buffer[],
        int flags, int width, int precision, int size);

int print_binary(va_list typ, char buffer[],
        int flags, int width, int precision, int size)

#endif
