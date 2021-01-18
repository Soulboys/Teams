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
#include "client/answers.h"
#include "logging_client.h"
#include "macro.h"

static void print(client_t *cli, bool it, const char *rfc)
{
    char **t = NULL;
    char *endptr;
    int v = it || !strcmp(rfc, RFC_CHANNEL) ? 0 :
            !strcmp(rfc, RFC_THREAD) ? 1 : (strcmp(rfc, RFC_MSG) != 0) + 2;

    t = fill_tab(cli, !v || v == 3 ? 3 : v == 1 ? 5 : 4);
    if (!v) {
        (it ? client_print_team : client_print_channel)(t[0], t[1], t[2]);
    } else if (v == 1) {
        client_print_thread(t[0], t[1],
                strtol(t[2], &endptr, 10), t[3], t[4]);
    } else
        client_print_user(t[0], t[1], (int)strtol(t[2], &endptr, 10));
    myfree_tab(t);
}

bool info(client_t *cli)
{
    char *rfc = NULL;
    bool it;

    if (!READ(cli, rfc))
        return (false);
    it = !strcmp(rfc, RFC_TEAM);
    print(cli, it, rfc);
    myfree(rfc);
    READ(cli, rfc);
    return (!myfree(rfc));
}

static void print_list(client_t *cli, bool it, const char *rfc)
{
    char **t = NULL;
    char *endptr;
    int v = it || !strcmp(rfc, RFC_CHANNEL) ? 0 :
            !strcmp(rfc, RFC_THREAD) ? 1 : (strcmp(rfc, RFC_MSG) != 0) + 2;

    t = fill_tab(cli, !v || v == 3 ? 3 : v == 1 ? 5 : 4);
    if (!v) {
        (it ? client_print_teams : client_team_print_channels)(t[0], t[1],
                t[2]);
    } else if (v == 1) {
        client_channel_print_threads(t[0], t[1],
                strtol(t[2], &endptr, 10), t[3], t[4]);
    } else {
        if (v == 2)
            client_thread_print_replies(t[0], t[1],
                    strtol(t[2], &endptr, 10), t[3]);
        else
            client_print_users(t[0], t[1], (int)strtol(t[2], &endptr, 10));
    }
    myfree_tab(t);
}

bool list(client_t *cli)
{
    char *rfc = NULL;
    bool it;

    if (!READ(cli, rfc))
        return (false);
    it = !strcmp(rfc, RFC_TEAM);
    for (; strcmp(rfc, "END") != 0; free(rfc), READ(cli, rfc))
        print_list(cli, it, rfc);
    return (!myfree(rfc));
}