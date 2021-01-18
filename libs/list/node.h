/*
** EPITECH PROJECT, 2018
** NWP_myftp_2019
** File description:
** node.h
*/

#ifndef NWP_MYFTP_2019_NODE_H
#define NWP_MYFTP_2019_NODE_H

typedef struct node_s {
    void *data;
    struct node_s *next;
    struct node_s *prev;
} node_t;

node_t *init_node(void *data);

#endif //NWP_MYFTP_2019_NODE_H
