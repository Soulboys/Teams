/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** utils.c
*/

#ifndef NWP_MYTEAMS_2019_UTILS_H
#define NWP_MYTEAMS_2019_UTILS_H

#include <stdbool.h>
#include "../socket/principe/principe.h"

int myerrno(const char *file, int line);
int ierror(const char *file, int line, const char *str);

bool rmalloc(size_t size, void *ptr);
void *mymalloc(size_t size);
void *myfree(void *ptr);
void *myfree_tab(void *ptr);

#endif //NWP_MYTEAMS_2019_UTILS_H
