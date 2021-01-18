/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** subscribe.c
*/

#include <string.h>
#include "client/class.h"
#include "macro.h"
#include "server/class.h"
#include "server/prototype.h"

static bool cmp_client_id(node_t *node, va_list list)
{
    client_t *cli = node->data;
    char *str = va_arg(list, char *);

    return (cli->user && !strcmp(cli->user->uuid, str));
}

static void list_subscribed(node_t *node, va_list args)
{
    context_id_t *t = node->data;
    client_t *cli = va_arg(args, client_t *);
    int *success = va_arg(args, int*);
    list_t clients = va_arg(args, list_t);
    char buffer[MAX_NAME_LENGTH + UUID_LENGTH + 4];

    sprintf(buffer, "%s\n%s\n%d", t->uuid, t->name,
            get_cmp(clients, cmp_client_id, t->uuid) != NULL);
    if (*success)
        *success = RFC(cli, RFC_USER, buffer);
}

static void check_present(node_t *node, va_list args)
{
    team_t *t = node->data;
    client_t *cli = va_arg(args, client_t *);
    int *success = va_arg(args, int*);
    char buffer[MAX_NAME_LENGTH + UUID_LENGTH + MAX_DESCRIPTION_LENGTH + 3];

    if (*success && get_cmp(t->subscribed, cmp_context_uuid, UUID(cli))) {
        sprintf(buffer, "%s\n%s\n%s", CUUID(t), CNAME(t), TEXT(t));
        *success = RFC(cli, RFC_TEAM, buffer);
    }
}

bool subscribed(server_t *serv, client_t *socket, char **args)
{
    bool r = true;
    node_t *node;
    char buffer[RFC_LENGTH + UUID_LENGTH + 2];

    if (!USER(socket))
        return (RFC(socket, RFC_UNAUTHORIZED, NULL));
    if (strlen(args[1]) > 0) {
        node = get_cmp(serv->teams, cmp_cuuid, args[1]);
        if (!node) {
            sprintf(buffer, "%s\n%s", RFC_TEAM, args[1]);
            return (RFC(socket, RFC_BAD_UUID, buffer));
        }
        r = RFC(socket, RFC_SUB_LIST, NULL);
        loop_list(SUBSCRIBED(node->data), list_subscribed, socket, &r,
                CLIENTS(serv));
    } else {
        r = RFC(socket, RFC_SUB_LIST, NULL);
        loop_list(serv->teams, check_present, socket, &r);
    }
    return (r);
}
