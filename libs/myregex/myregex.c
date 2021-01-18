/*
** EPITECH PROJECT, 2018
** NWP_myftp_2019
** File description:
** myregex.c
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <regex.h>
#include "myregex.h"

static void *is_matching_error(int value, regex_t preg)
{
    char *errbuff = malloc(sizeof(char) * 4096);

    if (errbuff) {
        regerror(value, &preg, errbuff, 4096);
        fprintf(stderr, "%s\n", errbuff);
        free(errbuff);
    }
    return (NULL);
}

static char **is_matching_convert(const char *str, regmatch_t *pmatch, int nb)
{
    char **tab = NULL;

    if (!nb)
        return (NULL);
    tab = malloc(sizeof(char *) * (nb + 1));
    for (int i = 0; tab && i < nb; i++)
        tab[i] = strndup(str + START(i), DIFF(i));
    if (tab)
        tab[nb] = NULL;
    return (tab);
}

char **is_matching(const char *str, const char *regex, int *founded)
{
    regex_t preg;
    regmatch_t *pmatch = NULL;
    int value = regcomp(&preg, regex, REG_EXTENDED | REG_ICASE);
    char **to_return;

    if (value)
        return (is_matching_error(value, preg));
    pmatch = malloc(sizeof(regmatch_t) * preg.re_nsub);
    if (!pmatch)
        return (NULL);
    value = regexec(&preg, str, preg.re_nsub, pmatch, 0);
    regfree(&preg);
    to_return = !value ? is_matching_convert(str, pmatch, preg.re_nsub) : NULL;
    free(pmatch);
    *founded = !value;
    return (to_return);
}

char *must_be_line(const char *str)
{
    size_t size = strlen(str);
    char *new = malloc(size+ 3);

    if (!new)
        return (NULL);
    new[0] = '^';
    new[1] = '\0';
    new = strcat(new, str);
    new[size + 1] = '$';
    new[size + 2] = '\0';
    return (new);
}