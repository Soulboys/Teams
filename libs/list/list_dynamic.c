/*
** EPITECH PROJECT, 2018
** NWP_myftp_2019
** File description:
** info.c
*/

#include <stdbool.h>
#include <stdio.h>
#include "list.h"

void add_to_list(list_t *list, void *data)
{
    node_t *begin;

    if (!list)
        return;
    if (!list->size) {
        list->nodes = init_node(data);
        list->size += list->nodes ? 1 : 0;
    } else {
        for (begin = list->nodes; begin->next; begin = begin->next);
        begin->next = init_node(data);
        if (begin->next)
            begin->next->prev = begin;
        list->size += begin->next ? 1 : 0;
    }
}

void remove_from_list(list_t *list, void *ptr, bool is_data,
        node_access_t destroyer)
{
    node_t *node = NULL;

    if (!list || !ptr)
        return;
    node = get(*list, ptr, is_data);
    if (list->nodes == ptr) {
        list->nodes = list->nodes->next;
        if (list->nodes)
            list->nodes->prev = NULL;
    } else if (node) {
        if (node->prev)
            node->prev->next = node->next;
        if (node->next)
            node->next->prev = node->prev;
    }
    if (list->nodes == ptr || node) {
        if (destroyer)
            destroyer(node);
        list->size--;
    }
}

void clear_list(list_t *list, node_access_t destroyer)
{
    list->nodes = get_last(*list, false);
    for (node_t *prev = NULL; list->nodes; list->nodes = prev) {
        prev = list->nodes->prev;
        if (destroyer)
            destroyer(list->nodes);
    }
    list->size = 0;
}