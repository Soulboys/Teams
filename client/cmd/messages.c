/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** subscription.c
*/

#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "client/class.h"
#include "logging_client.h"

bool sended(client_t *cli)
{
    char *uuid = NULL;
    char *body = NULL;

    if (!(READ(cli, uuid) && READ(cli, body)))
        return (false);
    client_event_private_message_received(uuid, body);
    (void)(!myfree(uuid) && !myfree(body));
    (void)(READ(cli, uuid) && myfree(uuid));
    return (true);
}

bool conversation(client_t *cli)
{
    char *uuid = NULL;
    char *body = NULL;
    char *time = NULL;
    char *rfc = NULL;
    char *endptr = NULL;

    for (; READ(cli, rfc) && strcmp(rfc, "END") != 0; rfc = myfree(rfc)) {
        if (!(READ(cli, uuid) && READ(cli, body) && READ(cli, time))) {
            (void)(!myfree(uuid) && !myfree(body) && !myfree(time));
            return (false);
        }
        client_private_message_print_messages(uuid,
                strtol(time, &endptr, 10), body);
        (void)(!myfree(uuid) && !myfree(body) && !myfree(time));
    }
    myfree(rfc);
    return (rfc);
}