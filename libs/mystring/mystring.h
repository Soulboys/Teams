/*
** EPITECH PROJECT, 2018
** ftpv2
** File description:
** mystring.h
*/

#ifndef FTPV2_MYSTRING_H
#define FTPV2_MYSTRING_H

#include <stdbool.h>

bool end_with(const char *, const char *);
bool start_with(const char *, const char *);
char *trim_end(char *, const char *);
char *trim_begin(char *, const char *);
char *trim(char *, const char *);
char *get_between_strings(char **tags, char *str, size_t *size);
#endif //FTPV2_MYSTRING_H
