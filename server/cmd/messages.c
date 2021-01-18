/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** send.h
*/

#include <string.h>
#include "server/class.h"
#include "client/class.h"
#include "server/prototype.h"
#include "logging_server.h"
#include "server/save.h"
#include "macro.h"

static bool cmp_client(node_t *node, va_list list)
{
    client_t *cli = node->data;
    char *uuid = va_arg(list, char*);

    return (USER(cli) && !strcmp(UUID(cli), uuid));
}

void notify_clients(client_t *cli, message_t *msg, client_t *ncli)
{
    char buffer[2048];

    if (ncli) {
        sprintf(buffer, "%s\n%s\nEND", UUID(cli), msg->message);
        RFC(ncli, RFC_SEND, buffer);
    }
    server_event_private_message_sended(UUID(cli), msg->to->uuid,
            msg->message);
}

bool send_msg(server_t *serv, client_t *cli, char **args)
{
    node_t *node = get_cmp(USERS(serv), cmp_context_uuid, args[1]);
    int size = serv->messages.size;
    node_t *ncli = node ? get_cmp(CLIENTS(serv), cmp_client,
            CTID(node->data)->uuid) : NULL;
    message_t *msg;

    if (!cli->user || !node)
        return (RFC(cli, !cli->user ? RFC_UNAUTHORIZED : RFC_BAD_UUID,
                !cli->user ? NULL : RFC_USER));
    msg = new(message, USER(cli), node->data, args[2]);
    add_to_list(&serv->messages, msg);
    if (size >= serv->messages.size)
        return (WRITE(cli, ERROR_LOCAL));
    notify_clients(cli, msg, ncli ? ncli->data : NULL);
    write_save(serv);
    return (RFC(cli, RFC_NO_RETURN, NULL));
}

static void loop_message_uuid(node_t *node, va_list list)
{
    message_t *m = node->data;
    char *uuid = va_arg(list, char*);
    client_t *cli = va_arg(list, client_t *);
    int *ret = va_arg(list, int*);
    char buffer[1024];

    if ((!strcmp(m->from->uuid, uuid) || !strcmp(m->to->uuid, uuid)) && *ret) {
        sprintf(buffer, "%s\n%s\n%s\n%ld\n", RFC_MSG,
                m->from->uuid, m->message, m->time);
        *ret = WRITE(cli, buffer);
    }
}

bool messages(server_t *serv, client_t *cli, char **args)
{
    int ret = 1;
    char buffer[UUID_LENGTH + 30];

    if (!cli->user)
        return (RFC(cli, RFC_UNAUTHORIZED, NULL));
    if (!get_cmp(USERS(serv), cmp_context_uuid, args[1])) {
        sprintf(buffer, "%s\n%s", RFC_USER, args[1]);
        return (RFC(cli, RFC_BAD_UUID, buffer));
    }
    ret = RFC(cli, RFC_CONVERSATION, NULL);
    loop_list(serv->messages, loop_message_uuid, args[1], cli, &ret);
    return (ret);
}