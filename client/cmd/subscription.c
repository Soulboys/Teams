/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** subscription.c
*/

#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "client/class.h"
#include "client/answers.h"
#include "logging_client.h"
#include "macro.h"

bool subscribe(client_t *cli)
{
    char *uuid = NULL;
    char *user_uuid = NULL;

    if (!(READ(cli, uuid) && READ(cli, user_uuid)))
        return (false);
    client_print_subscribed(user_uuid, uuid);
    (void)(!myfree(uuid) && !myfree(user_uuid));
    (void)(READ(cli, uuid) && myfree(uuid));
    return (true);
}

bool unsubscribe(client_t *cli)
{
    char *uuid = NULL;
    char *user_uuid = NULL;

    if (!(READ(cli, uuid) && READ(cli, user_uuid)))
        return (false);
    client_print_unsubscribed(user_uuid, uuid);
    (void)(!myfree(uuid) && !myfree(user_uuid));
    (void)(READ(cli, uuid) && myfree(uuid));
    return (true);
}

bool subscribed(client_t *cli)
{
    char *rfc = NULL;
    char **tab = NULL;
    bool is_team;

    if (!READ(cli, rfc))
        return (false);
    for (; rfc && strcmp(rfc, "END") != 0; free(rfc), READ(cli, rfc)) {
        is_team = !strcmp(rfc, RFC_TEAM);
        tab = fill_tab(cli, 3);
        if (tab)
            is_team ? client_print_teams(tab[0], tab[1], tab[2]) :
                client_print_users(tab[0], tab[1], !strcmp(tab[2], "1"));
        myfree_tab(tab);
    }
    return (!myfree(rfc) && rfc);
}