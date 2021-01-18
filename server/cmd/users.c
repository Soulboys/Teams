/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** users.c
*/

#include <string.h>
#include "client/class.h"
#include "server/class.h"
#include "macro.h"

static bool cmp_client_id(node_t *node, va_list list)
{
    client_t *cli = node->data;
    char *str = va_arg(list, char *);

    return (cli->user ? !strcmp(cli->user->uuid, str) : false);
}

void user_accesser(node_t *node, va_list list)
{
    context_id_t *cli_id = node->data;
    client_t *cli = va_arg(list, client_t *);
    list_t clients = va_arg(list, list_t);
    int *connected = va_arg(list, int*);
    char buffer[1024];

    if (*connected) {
        sprintf(buffer, "%s\n%s\n%d", cli_id->uuid,
                cli_id->name,
                get_cmp(clients, cmp_client_id, cli_id->uuid) != NULL);
        *connected = RFC(cli, RFC_USER, buffer);
    }
}

bool users(server_t *serv, client_t *socket, char **args)
{
    int connected = 1;

    if (!USER(socket))
        return (RFC(socket, RFC_UNAUTHORIZED, NULL));
    connected = RFC(socket, RFC_LIST, NULL);
    (void)args;
    if (connected)
        loop_list(USERS(serv), user_accesser, socket, CLIENTS(serv),
                &connected);
    return (connected);
}