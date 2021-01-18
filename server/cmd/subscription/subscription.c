/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** subscribe.c
*/

#include <string.h>
#include "logging_server.h"
#include "client/class.h"
#include "server/class.h"
#include "server/save.h"
#include "server/members.h"
#include "server/prototype.h"
#include "utils.h"
#include "macro.h"

static void can_subscribe(list_t teams, char **info, node_t **t_node,
        node_t **u_node)
{
    (*t_node) = get_cmp(teams, cmp_cuuid, info[0]);
    (*u_node) = !(*t_node) ? NULL:
        get_cmp(SUBSCRIBED((*t_node)->data), cmp_context_uuid, info[1]);
}

static bool send_bad_uuid(client_t *cli, const char *uuid, int rvalue)
{
    char buffer[1024];
    if (!rvalue)
        return (RFC(cli, RFC_UNAUTHORIZED, NULL));
    else if (rvalue == 2) {
        printf("ici\n");
        return (RFC(cli, RFC_ALREADY, NULL));
    } else {
        sprintf(buffer, "%s\n%s", RFC_TEAM, uuid);
        return (RFC(cli, RFC_BAD_UUID, buffer));
    }
}

static bool notify(context_t *tm, client_t *socket,
        const char *rfc)
{
    char buffer[1024];
    int success = 1;

    sprintf(buffer, "%s\n%s", CUUID(tm), UUID(socket));
    RFC(socket, rfc, buffer);
    return (success);
}

bool subscribe(server_t *serv, client_t *sock, char **a)
{
    node_t *n[] = {NULL, NULL};
    int size;

    can_subscribe(serv->teams, (char *[]) {a[1], UUID(sock)}, &n[0], &n[1]);
    if (!USER(sock) || !n[0] || n[1])
        return (send_bad_uuid(sock, a[1], !USER(sock) ? 0 : !n[0] ? 1 : 2));
    size = SUBSCRIBED(n[0]->data).size;
    add_to_list(&SUBSCRIBED(n[0]->data),
        new(context_id, true, (char*[]){0, USERNAME(sock), UUID(sock)}));
    if (size >= SUBSCRIBED(n[0]->data).size)
        return (WRITE(sock, ERROR_LOCAL));
    server_event_user_join_a_team(CUUID(n[0]->data), UUID(sock));
    size = notify(n[0]->data, sock, RFC_SUB_JOIN);
    write_save(serv);
    return (size);
}

bool unsubscribe(server_t *serv, client_t *sock, char **a)
{
    node_t *n[] = {NULL, NULL};
    int value[2] = {0, 0};

    can_subscribe(serv->teams, (char *[]) {a[1], UUID(sock)}, &n[0], &n[1]);
    if (!USER(sock) || !n[0] || !n[1])
        return (send_bad_uuid(sock, a[1], !USER(sock) ? 0 : !n[0] ? 1 : 2));
    value[0] = SUBSCRIBED(n[0]->data).size;
    server_event_user_leave_a_team(CUUID(n[0]->data), UUID(sock));
    value[1] = notify(n[0]->data, sock, RFC_SUB_LEFT);
    remove_from_list(&SUBSCRIBED(n[0]->data), n[1], false,
                     &node_class_clear);
    if (value[0] <= SUBSCRIBED(n[0]->data).size)
        return (WRITE(sock, ERROR_LOCAL));
    write_save(serv);
    return (value[1]);
}