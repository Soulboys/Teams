/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** utils.c
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void *mymalloc(size_t size)
{
    void *value = malloc(size);

    if (!value)
        printf("Memory allocation error !");
    return (value);
}

bool rmalloc(size_t size, void *ptr)
{
    void **n = ptr;

    *n = mymalloc(size);
    return (*n);
}

void *myfree(void *ptr)
{
    free(ptr);
    return (NULL);
}

void *myfree_tab(void *ptr)
{
    void **tab = ptr;

    for (int i = 0; ptr && tab[i]; i++)
        myfree(tab[i]);
    myfree(ptr);
    return (NULL);
}