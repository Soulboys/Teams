/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** login.c
*/

#include <string.h>
#include "utils.h"
#include "client/class.h"
#include "logging_client.h"

bool login(client_t *cli)
{
    char *uuid = NULL;
    char *name = NULL;

    if (!(READ(cli, uuid) && READ(cli, name)))
        return (false);
    if (!cli->user)
        cli->user = new(context_id, true, (char*[]){NULL, name, uuid});
    client_event_loggedin(uuid, name);
    (void)(!myfree(uuid) && !myfree(name));
    (void)(READ(cli, uuid) && myfree(uuid));
    return (true);
}

bool logout(client_t *cli)
{
    char *uuid = NULL;
    char *name = NULL;
    bool rvalue;

    if (!(READ(cli, uuid) && READ(cli, name)))
        return (false);
    client_event_loggedout(uuid, name);
    rvalue = !cli->user || strcmp(uuid, cli->user->uuid) != 0;
    (void)(!myfree(uuid) && !myfree(name));
    (void)(READ(cli, uuid) && myfree(uuid));
    return (rvalue);
}

bool unlogged(client_t *cli)
{
    char *uuid = NULL;

    client_error_unauthorized();
    READ(cli, uuid);
    myfree(uuid);
    return (true);
}