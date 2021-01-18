/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** myerror.c
*/

#include <string.h>
#include <errno.h>
#include <stdio.h>

int myerrno(const char *file, int line)
{
    fprintf(stdout, "teams:[%s, %d]: \033[31;1m%s\033[0m\n",
            file, line, strerror(errno));
    return (84);
}

int ierror(const char *file, int line, const char *str)
{
    fprintf(stdout, "teams:[%s, %d]: \033[31;1m%s\033[0m\n",
            file, line, str);
    return (84);
}