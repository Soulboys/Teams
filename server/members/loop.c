/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** clear.c
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "server/class.h"
#include "server/prototype.h"
#include "client/class.h"
#include "macro.h"

void clear(node_t *node)
{
    long port = ntohs(SADDR(node->data).sin_port);
    struct in_addr inaddr = SADDR(node->data).sin_addr;
    char *addr = inet_ntoa(inaddr);

    delete(node->data);
    if (inaddr.s_addr)
        printf("\033[36;1mDeconnection from %s:%ld.\033[0m\n", addr, port);
    else
        printf("\033[36;1mServer with port %ld, is shutting down.\033[0m\n",
            port);
    free(node);
}

void loop_rfds(node_t *node, va_list list)
{
    fd_set *fds = va_arg(list, fd_set *);
    int *biggest = va_arg(list, int *);
    client_t *cli = node->data;

    FD_SET(FD(cli), fds);
    *biggest = FD(cli) > *biggest ? FD(cli) : *biggest;
}

void loop_disconnected(node_t *node, va_list list)
{
    list_t *clients = va_arg(list, list_t *);

    if (!ONLINE(node->data))
        remove_from_list(clients, node, false, clear);
}

void loop_try_handle(node_t *node, va_list list)
{
    fd_set *lfds = va_arg(list, fd_set *);
    client_t *cli = node->data;
    server_t *serv = va_arg(list, server_t *);

    if (FD_ISSET(FD(cli), lfds)) {
        HANDLER(serv)(serv, node->data);
        FD_CLR(FD(cli), lfds);
    }
}

void send_str(node_t *node, va_list args)
{
    list_t list = va_arg(args, list_t);
    char *rfc = va_arg(args, char*);
    char *str = va_arg(args, char *);
    int *success = va_arg(args, int *);
    client_t *c = node->data;
    void *v = c->user ? get_cmp(list, cmp_context_uuid, c->user->uuid) : NULL;
    char *uuid = va_arg(args, char*);

    if (!USER(c) || (uuid && !strcmp(UUID(c), uuid)))
        return;
    if (success && *success && v) {
        *success = RFC(node->data, rfc, str) && WRITE(node->data, RFC_END);
    } else if (!success && v) {
        RFC(node->data, rfc, str);
        WRITE(node->data, RFC_END);
    }
}