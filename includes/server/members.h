/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** helper.h
*/

#ifndef NWP_MYTEAMS_2019_MEMBERS_H
#define NWP_MYTEAMS_2019_MEMBERS_H

#include "server/class.h"

void clear(node_t *node);
void loop_rfds(node_t *node, va_list list);
void loop_disconnected(node_t *node, va_list list);
void loop_try_handle(node_t *node, va_list list);
void send_str(node_t *node, va_list args);

bool server_ctor(object *this, va_list *args);
void server_dtor(object *this);
bool server_new_client(saddr_in sa, list_t *list, int fd);
bool server_handler(object *this, principe_t *socket);
bool server_reception(object *this);
bool client_rfc_write(client_t *cli, const char *rfc, const char *);
list_t *server_context_list(server_t *serv);
const class *server_new_context(server_t *serv);

#endif //NWP_MYTEAMS_2019_MEMBERS_H
