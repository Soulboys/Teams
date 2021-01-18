/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** basic_server.h
*/

#ifndef NWP_MYTEAMS_2019_BASIC_SERVER_H
#define NWP_MYTEAMS_2019_BASIC_SERVER_H

#include "../principe/principe.h"
#include "list.h"

typedef bool (*handler_t)(object *, principe_t *);
typedef bool (*loop_t)(object *);
typedef bool (*new_client_t)(saddr_in, list_t *, int);
typedef void (*clear_client_t)(node_t *node);

typedef struct basic_server_clients_s {
    list_t clients;
    new_client_t new_client;
    clear_client_t clear_clients;
} basic_server_clients_t;

typedef struct basic_server_s {
    principe_t interface;
    basic_server_clients_t server_clients;
    handler_t request_handler;
    loop_t reception;
} basic_server_t;

#define BASIC_SERVER(sock) ((basic_server_t*)sock)
#define CLIENTS(sock) BASIC_SERVER(sock)->server_clients.clients
#define NEW_CLIENT(sock) BASIC_SERVER(sock)->server_clients.new_client
#define CLEAR_CLIENTS(sock) BASIC_SERVER(sock)->server_clients.clear_clients
#define HANDLER(sock) BASIC_SERVER(sock)->request_handler
#define RECEPTION(sock) BASIC_SERVER(sock)->reception

#endif //NWP_MYTEAMS_2019_BASIC_SERVER_H
