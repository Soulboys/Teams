/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** bad_uuid.c
*/

#include <string.h>
#include "utils.h"
#include "client/answers.h"
#include "client/class.h"
#include "logging_client.h"
#include "macro.h"

static const unknown_t UNKNOWN[] = {
    {RFC_TEAM, &client_error_unknown_team},
    {RFC_CHANNEL, &client_error_unknown_channel},
    {RFC_THREAD, &client_error_unknown_thread},
    {RFC_USER, &client_error_unknown_user},
    {NULL, NULL},
};

bool bad_uuid(client_t *cli)
{
    char *rfc = NULL;
    char *uuid = NULL;

    if (!(READ(cli, rfc) && READ(cli, uuid)))
        return (false);
    for (int i = 0; UNKNOWN[i].rfc; i++)
        if (!strcmp(UNKNOWN[i].rfc, rfc))
            UNKNOWN[i].function(uuid);
    (void)(!myfree(rfc) && !myfree(uuid));
    (void)(READ(cli, uuid) && !myfree(uuid));
    return (true);
}

bool already(client_t *cli)
{
    char *uuid = NULL;

    client_error_already_exist();
    (void)(READ(cli, uuid) && !myfree(uuid));
    return (true);
}