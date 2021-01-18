/*
** EPITECH PROJECT, 2018
** NWP_myftp_2019
** File description:
** node.c
*/


#include <stdlib.h>
#include "node.h"

node_t *init_node(void *data)
{
    node_t *node = malloc(sizeof(node_t));

    if (!node)
        return (NULL);
    node->data = data;
    node->next = NULL;
    node->prev = NULL;
    return (node);
}