#pragma once
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include "String.h"

String to_string(int n)
{
    char* s = new char[(int)((ceil(log10(n))+1)*sizeof(char))];
    sprintf(s, "%d", n);
    String st(s);
    delete[] s;
    return st;
}

String to_string(char const* s)
{
    return String(s);
}

#define LOGGER(device, type, col)                                            \
void type ## _recurse(char const* format)                                    \
{                                                                            \
    fprintf(device, "%s", format);                                           \
}                                                                            \
                                                                             \
template<typename T, typename... Targs>                                      \
void type ## _recurse(char const* format, T value, Targs... Fargs)           \
{                                                                            \
    for (; *format != '\0'; ++format) {                                      \
        if (*format == '{' && *(format+1) != '\0' && *++format == '}') {     \
            fprintf(device, "%s", to_string(value).c_str());                 \
            type ## _recurse(format+1, Fargs...);                            \
            return;                                                          \
        }                                                                    \
        fprintf(device, "%c", *format);                                      \
    }                                                                        \
}                                                                            \
                                                                             \
void type(char const* format)                                                \
{                                                                            \
    fprintf(device, "\033[" #col "m[" #type "]\033[30m %s", format);         \
}                                                                            \
                                                                             \
template<typename T, typename... Targs>                                      \
void type(char const* format, T value, Targs... Fargs)                       \
{                                                                            \
    fprintf(device, "\033[" #col "m[" #type "]\033[30m ");                   \
    type ## _recurse(format, value, Fargs...);                               \
    fprintf(device, "\n");                                                   \
}                                                                            \

LOGGER(stderr, error, 31)
LOGGER(stdout, log, 34)