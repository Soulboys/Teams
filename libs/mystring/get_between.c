/*
** EPITECH PROJECT, 2018
** ftpv2
** File description:
** mystring.c
*/

#include <string.h>
#include <stdio.h>
#include "mystring.h"

char *get_between_strings(char **tags, char *str, size_t *size)
{
    int j = 0;
    size_t s;
    char *rvalue = NULL;

    if (start_with(str, tags[0])) {
        s = strlen(tags[0]);
        for (char *n = str + s; n[j] && !start_with(&n[j], tags[1]); j++);
        rvalue = strndup(str + s, j);
        if (rvalue && size)
            *size = (int)(strlen(tags[0]) + strlen(rvalue) + strlen(tags[1]));
    }
    return (rvalue);
}