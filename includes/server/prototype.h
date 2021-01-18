/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** prototype.h
*/

#ifndef NWP_MYTEAMS_2019_SERVER_PROTOTYPE_H
#define NWP_MYTEAMS_2019_SERVER_PROTOTYPE_H

#include "client/class.h"
#include "context/context.h"
#include "server/class.h"

int tab_size(void *ptr);
bool cmp_cuuid(node_t *node, va_list args);
bool cmp_context_uuid(node_t *node, va_list args);
void node_class_clear(node_t *node);
char *replace(char *prev);

context_t *find_team(const class *c, server_t *serv);
#endif //NWP_MYTEAMS_2019_SERVER_PROTOTYPE_H
