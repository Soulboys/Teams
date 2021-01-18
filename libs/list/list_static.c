/*
** EPITECH PROJECT, 2018
** NWP_myftp_2019
** File description:
** list_static.c
*/

#include <stdbool.h>
#include <stdlib.h>
#include "list.h"

void loop_list(list_t list, node_access_args_t loop, ...)
{
    va_list valist;
    va_list cpy;

    va_start(valist, loop);
    for (node_t *next; list.nodes; list.nodes = next) {
        next = list.nodes->next;
        va_copy(cpy, valist);
        loop(list.nodes, cpy);
    }
    va_end(valist);
}

node_t *get(list_t list, void *ptr, bool is_data)
{
    for (; list.nodes; list.nodes = list.nodes->next)
        if ((is_data ? list.nodes && list.nodes->data == ptr :
            list.nodes && list.nodes == ptr))
            return (list.nodes);
    return (NULL);
}

node_t *get_cmp(list_t list, node_cmp_args_t cmp, ...)
{
    va_list valist;
    va_list cpy;

    va_start(valist, cmp);
    for (node_t *next; list.nodes; list.nodes = next) {
        next = list.nodes->next;
        va_copy(cpy, valist);
        if (cmp(list.nodes, cpy))
            return (list.nodes);
    }
    va_end(valist);
    return (NULL);
}

void *get_at(list_t list, int index, bool is_data)
{
    if (index > list.size)
        return (NULL);
    for (int i = 0; i < index; i++, list.nodes = list.nodes->next);
    return (is_data ? list.nodes->data : list.nodes);
}

void *get_last(list_t list, bool is_data)
{
    if (!list.size)
        return (NULL);
    for (; list.nodes && list.nodes->next; list.nodes = list.nodes->next);
    return (is_data ? list.nodes->data : list.nodes);
}