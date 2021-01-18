/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** user.c
*/

#include <uuid/uuid.h>
#include <string.h>
#include "client/class.h"
#include "server/class.h"
#include "macro.h"

static bool cmp(node_t *node, va_list list)
{
    char *str = va_arg(list, char*);

    return (!strcmp(str, ((context_id_t *)node->data)->uuid));
}

bool user(server_t *serv, client_t *socket, char **args)
{
    bool connected = true;
    node_t *node = get_cmp(USERS(serv), cmp, args[1]);
    context_id_t *cli_id = node ? node->data : NULL;
    char buffer[1024];

    if (!USER(socket))
        return (RFC(socket, RFC_UNAUTHORIZED, NULL));
    if (cli_id) {
        sprintf(buffer, "%s\n%s\n%s\n%d", RFC_USER, cli_id->uuid,
                cli_id->name, 1);
        connected = RFC(socket, RFC_LIST, buffer);
    } else
        connected = RFC(socket, RFC_BAD_UUID, args[1]);
    return (connected);
}