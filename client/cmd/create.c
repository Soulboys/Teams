/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** login.c
*/

#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "client/class.h"
#include "macro.h"
#include "client/answers.h"
#include "logging_client.h"

void subcreate(const int v[2], char **tab)
{
    char *endptr;

    if (!v[0]) {
        (v[1] ? client_print_team_created : client_print_channel_created)
                (tab[0], tab[1], tab[2]);
    } else if (v[0] == 1) {
        client_print_thread_created(tab[0], tab[1],
                strtol(tab[2], &endptr, 10), tab[3], tab[4]);
    } else
        client_print_reply_created(tab[0], tab[1],
                strtol(tab[2], &endptr, 10), tab[3]);
}

bool create(client_t *cli)
{
    char *rfc = NULL;
    char **tab = NULL;
    int v[2] = {0, 0};

    if (!READ(cli, rfc))
        return (false);
    v[1] = !strcmp(rfc, RFC_TEAM);
    v[0] = v[1] || !strcmp(rfc, RFC_CHANNEL) ? 0 :
            (strcmp(rfc, RFC_THREAD) != 0) + 1;
    tab = fill_tab(cli, !v[0] ? 3 : v[0] == 1 ? 5 : 4);
    subcreate(v, tab);
    (void)(!myfree(rfc) && !myfree_tab(tab) && READ(cli, rfc) && !myfree(rfc));
    return (true);
}

bool event_created(client_t *cli)
{
    char *rfc = NULL;
    char **tab = NULL;
    char *endptr;
    int v[2] = {0, 0};

    if (!READ(cli, rfc))
        return (false);
    v[1] = !strcmp(rfc, RFC_TEAM);
    v[0] = v[1] || !strcmp(rfc, RFC_CHANNEL) ? 0 :
        (strcmp(rfc, RFC_THREAD) != 0) + 1;
    tab = fill_tab(cli, !v[0] ? 3 : v[0] == 1 ? 5 : 4);
    if (!v[0]) {
        (v[1] ? client_event_team_created : client_event_channel_created)
                (tab[0], tab[1], tab[2]);
    } else if (v[0] == 1) {
        client_event_thread_created(tab[0], tab[1],
                strtol(tab[2], &endptr, 10), tab[3], tab[4]);
    } else
        client_event_thread_message_received(tab[0], tab[1], tab[2], tab[3]);
    (void)(!myfree(rfc) && !myfree_tab(tab) && READ(cli, rfc) && !myfree(rfc));
    return (true);
}