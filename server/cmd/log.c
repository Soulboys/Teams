/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** help.c
*/

#include <string.h>
#include "utils.h"
#include "macro.h"
#include "server/prototype.h"
#include "server/save.h"
#include "client/class.h"
#include "server/answers.h"
#include "logging_server.h"
#include "server/members.h"

static bool cmp(node_t *node, va_list list)
{
    char *str = va_arg(list, char*);

    return (!strcmp(str, ((context_id_t *)node->data)->name));
}

static bool write_info(server_t *serv, client_t *socket, bool login)
{
    char uuid[UUID_LENGTH + 1 + MAX_NAME_LENGTH + 2];
    int success = 1;

    if (USER(socket))
        sprintf(uuid, "%s\n%s", UUID(socket), USERNAME(socket));
    loop_list(CLIENTS(serv), send_str, USERS(serv), login ? RFC_LOGIN :
        RFC_LOGOUT, USER(socket) ? uuid : NULL, &success, UUID(socket));
    return (RFC(socket, login ? RFC_LOGIN : RFC_LOGOUT,
            USER(socket) ? uuid : NULL));
}

bool login(server_t *serv, client_t *socket, char **args)
{
    node_t *node = NULL;

    if (strlen(args[1]) > MAX_NAME_LENGTH)
        return (WRITE(socket, TL_NAME));
    node = get_cmp(USERS(serv), cmp, args[1]);
    USER(socket) = node ? node->data : NULL;
    if (!USER(socket)) {
        USER(socket) = new(context_id, false, args[1]);
        if (!USER(socket))
            return (WRITE(socket, ERROR_LOCAL));
        add_to_list(&USERS(serv), USER(socket));
        if (server_event_user_created(UUID(socket), USERNAME(socket)) == -1)
            return (WRITE(socket, ERROR_LOCAL));
    }
    write_save(serv);
    server_event_user_logged_in(UUID(socket));
    return (write_info(serv, socket, 1));
}

bool logout(server_t *serv, client_t *socket, char **args)
{
    (void)serv;
    (void)args;
    if (USER(socket))
        server_event_user_logged_out(UUID(socket));
    write_info(serv, socket, 0);
    return (false);
}