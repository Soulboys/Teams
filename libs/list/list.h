/*
** EPITECH PROJECT, 2018
** NWP_myftp_2019
** File description:
** info.h
*/

#ifndef NWP_MYFTP_2019_LIST_H
#define NWP_MYFTP_2019_LIST_H

#include "node.h"
#include <stdbool.h>
#include <stdarg.h>

typedef void (*node_access_t)(node_t *);
typedef void (*node_access_args_t)(node_t *, va_list);
typedef bool (*node_cmp_args_t)(node_t *, va_list);

typedef struct {
    int size;
    node_t *nodes;
} list_t;

void add_to_list(list_t *, void *);
void remove_from_list(list_t *, void *, bool, node_access_t);
void clear_list(list_t *, node_access_t);
void loop_list(list_t, node_access_args_t, ...);
node_t *get(list_t list, void *ptr, bool is_data);
node_t *get_cmp(list_t list, node_cmp_args_t cmp, ...);
void *get_at(list_t list, int index, bool is_data);
void *get_last(list_t list, bool is_data);
#endif //NWP_MYFTP_2019_LIST_H
