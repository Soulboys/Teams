/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** help.c
*/

#include <string.h>
#include "utils.h"
#include "client/class.h"
#include "server/class.h"
#include "context/context.h"
#include "macro.h"

static bool cmp(node_t *node, va_list list)
{
    char *str = va_arg(list, char*);

    return (!strcmp(str, CUUID(node->data)));
}

static bool get_context(list_t list, const char *str, context_t **context)
{
    node_t *node;
    bool b = strcmp(str, "") != 0;

    if (b) {
        node = get_cmp(list, cmp, str);
        *context = node ? node->data : *context;
    }
    return (!b || node);
}

bool send_bad_uuid(client_t *cli, const char *rfc, const char *uuid)
{
    char buffer[RFC_LENGTH + 1 + UUID_LENGTH + 1];

    sprintf(buffer, "%s\n%s", rfc, uuid);
    return (RFC(cli, RFC_BAD_UUID, buffer));
}

bool use(server_t *serv, client_t *socket, char **args)
{
    context_t *context = NULL;

    if (!USER(socket))
        return (RFC(socket, RFC_UNAUTHORIZED, NULL));
    else if (!strcmp(args[1], "")) {
        serv->context = NULL;
        return (RFC(socket, "CTX", "Context set"));
    }
    if (!get_context(serv->teams, args[1], &context))
        return (send_bad_uuid(socket, RFC_TEAM, args[1]));
    else if (!get_context(context->list, args[2], &context))
        return (send_bad_uuid(socket, RFC_CHANNEL, args[2]));
    else {
        if (!get_context(context->list, args[3], &context))
            return (send_bad_uuid(socket, RFC_THREAD, args[3]));
    }
    serv->context = context;
    return (RFC(socket, "CTX", "Context set"));
}