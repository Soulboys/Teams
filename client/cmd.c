/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** cmd.c
*/

#include <stdlib.h>
#include <string.h>
#include "client/answers.h"
#include "macro.h"
#include "utils.h"

static const answer_t ANSWERS[] = {
    {RFC_LOGIN, &login },
    {RFC_LOGOUT, &logout },
    {RFC_UNAUTHORIZED, &unlogged },
    {RFC_BAD_UUID, &bad_uuid },
    {RFC_ALREADY, &already },
    {RFC_CREATE, &create },
    {RFC_CREATE_MSG, &event_created},
    {RFC_INFO, &info },
    {RFC_LIST, &list },
    {RFC_SUB_LIST, &subscribed },
    {RFC_SUB_JOIN, &subscribe },
    {RFC_SUB_LEFT, &unsubscribe },
    {RFC_SEND, &sended },
    {RFC_CONVERSATION, &conversation },
    {RFC_NO_RETURN, &no_return},
    {NULL, NULL}
};

bool no_return(client_t *cli)
{
    char *end = NULL;

    return (READ(cli, end) && !myfree(end));
}

char **fill_tab(client_t *cli, int nb)
{
    char **tab = NULL;

    if (!rmalloc(sizeof(char *) * (nb + 1), &tab))
        return (NULL);
    for (int i = 0; i < nb; i++)
        READ(cli, tab[i]);
    tab[nb] = NULL;
    return (tab);
}

bool print_rest(client_t *cli)
{
    char *buffer = NULL;

    for (READ(cli, buffer); buffer && strcmp(buffer, "END") != 0;
        READ(cli, buffer)) {
        printf("%s\n", buffer);
        free(buffer);
    }
    return (!myfree(buffer) && buffer);
}

bool handle_cmd(client_t *cli)
{
    char *rfc = NULL;
    bool b;

    READ(cli, rfc);
    if (!rfc)
        return (false);
    for (int i = 0; ANSWERS[i].rfc; i++)
        if (!strcmp(ANSWERS[i].rfc, rfc)) {
            b = ANSWERS[i].function(cli);
            return (!myfree(rfc) && b);
        }
    return (!myfree(rfc) && print_rest(cli));
}