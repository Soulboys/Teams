/*
** EPITECH PROJECT, 2018
** ftpv2
** File description:
** myregex.h
*/

#ifndef FTPV2_MYREGEX_H
#define FTPV2_MYREGEX_H

#define START(nb) (pmatch[nb].rm_so)
#define END(nb) (pmatch[nb].rm_eo)
#define DIFF(nb) END(nb) - START(nb)

char **is_matching(const char *, const char *, int *);
char *must_be_line(const char *str);

#endif //FTPV2_MYREGEX_H
