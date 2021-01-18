/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** info.c
*/

#include <string.h>
#include "server/class.h"
#include "server/prototype.h"
#include "macro.h"

static void list_big(node_t *node, va_list args)
{
    client_t *cli = va_arg(args, client_t*);
    int *connected = va_arg(args, int*);
    char buffer[1024];

    if (!*connected)
        return;
    sprintf(buffer, "%s\n%s\n%s", CUUID(node->data), CNAME(node->data),
            TEXT(node->data));
    *connected = RFC(cli, IS(node->data, team) ? RFC_TEAM : RFC_CHANNEL,
            buffer);
}

static void list_thread(node_t *node, va_list args)
{
    client_t *cli = va_arg(args, client_t*);
    int *connected = va_arg(args, int*);
    char buffer[1024];

    if (!*connected)
        return;
    sprintf(buffer, "%s\n%s\n%ld\n%s\n%s", CUUID(node->data), USERNAME(cli),
            CONTEXT(node->data)->time, CNAME(node->data), TEXT(node->data));
    *connected = RFC(cli, RFC_THREAD, buffer);
}

static void list_reply(node_t *node, va_list args)
{
    client_t *cli = va_arg(args, client_t*);
    int *connected = va_arg(args, int*);
    context_t *context = va_arg(args, context_t*);
    char buffer[1024];

    if (!*connected)
        return;
    sprintf(buffer, "%s\n%s\n%ld\n%s", CUUID(context), UUID(cli),
            MESSAGE(node->data)->time, MESSAGE(node->data)->message);
    *connected = RFC(cli, RFC_MSG, buffer);
}

bool list(server_t *serv, client_t *socket, char **args)
{
    list_t list = *serv->context_list(serv);
    bool b = RFC(socket, !USER(socket) ? RFC_UNAUTHORIZED : RFC_LIST, NULL);
    const class *c = serv->new_context(serv);
    node_access_args_t access;
    int success = 1;

    (void)args;
    if (!b || !list.size || !USER(socket))
        return (b);
    access = IS(c, team) || IS(c, CONTEXT(team)->subclass) ? list_big :
        IS(c, CONTEXT(CONTEXT(team)->subclass)->subclass) ? list_thread :
        list_reply;
    loop_list(list, access, socket, &success, serv->context);
    return (success);
}