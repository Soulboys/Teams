/*
** EPITECH PROJECT, 2018
** ftpv2
** File description:
** mystring.c
*/

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool end_with(const char *str, const char *end)
{
    int send = (int)strlen(end);
    int sstr = (int)strlen(str);

    if (sstr < send)
        return (false);
    for (int i = send - 1, j = sstr -1; i > -1; i--, j--)
        if (str[j] != end[i])
            return (false);
    return (str);
}

bool start_with(const char *str, const char *start)
{
    if (strlen(str) < strlen(start))
        return (false);
    for (int i = 0; start[i]; i++)
        if (str[i] != start[i])
            return (false);
    return (true);
}

char *trim_end(char *str, const char *end)
{
    char *buff = str ? strdup(str) : NULL;
    size_t size = 0;

    if (!buff || !end_with(str, end))
        return (buff);
    size = strlen(str) - strlen(end);
    buff = realloc(buff, size + 1);
    if (buff) {
        buff = strncpy(buff, str, size);
        buff[size] = '\0';
    }
    return (buff);
}

char *trim_begin(char *str, const char *begin)
{
    char *buff = str ? strdup(str) : NULL;
    size_t size = 0;
    size_t strsize = 0;

    if (!buff || !start_with(str, begin))
        return (buff);
    size = strlen(begin);
    strsize = strlen(str);
    buff = realloc(buff, strsize - size + 1);
    if (buff) {
        buff = strcpy(buff, str + size);
        buff[strsize - size] = '\0';
    }
    return (buff);
}

char *trim(char *str, const char *pattern)
{
    char *buff = trim_begin(str, pattern);
    char *buff2 = trim_end(buff, pattern);

    free(buff);
    return (buff2);
}