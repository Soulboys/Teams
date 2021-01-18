/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** utils.c
*/

#include <string.h>
#include "utils.h"
#include "client/class.h"
#include "context/context.h"

int tab_size(void *ptr)
{
    void **tab = ptr;
    int i = 0;

    if (!ptr)
        return (i);
    for (; tab[i]; i++);
    return (i);
}

bool cmp_cuuid(node_t *node, va_list args)
{
    char *str = va_arg(args, char*);

    return (!strcmp(CUUID(node->data), str));
}

bool cmp_context_uuid(node_t *node, va_list args)
{
    char *str = va_arg(args, char*);

    return (!strcmp(((context_id_t*)node->data)->uuid, str));
}

void node_class_clear(node_t *node)
{
    delete(node->data);
    myfree(node);
}

char *replace(char *prev)
{
    size_t size = strlen(prev);
    char *new_str = NULL;
    int i = 0;

    for (; prev[i] && prev[i] != '\t' && prev[i] != '\n'; i++);
    if (prev[i] == '\t' || prev[i] == '\n') {
        new_str = mymalloc(size);
        if (new_str) {
            new_str = strncpy(new_str, prev, i);
            new_str[i] = '\0';
            new_str = strcat(new_str, prev + i + 1);
            myfree(prev);
            return (replace(new_str));
        }
    }
    return (prev);
}