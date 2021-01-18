/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** server_helper.c
*/

#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "mystring.h"
#include "myregex.h"
#include "macro.h"
#include "client/class.h"
#include "server/save.h"
#include "server/class.h"
#include "server/members.h"
#include "server/answers.h"

static bool server_new_connection(server_t *this)
{
    socklen_t size = sizeof(saddr_in);
    int fd = accept(FD(this), (saddr *)&SADDR(this), &size);
    client_t *last;

    if (fd >= 0 && !server_new_client(SADDR(this), &CLIENTS(this), fd))
        return (false);
    else if (fd >= 0) {
        last = get_last(CLIENTS(this), true);
        CONNECTION(last);
    }
    return (fd >= 0);
}

static int server_match_cmd(const char *str, match_command_t mcmd, char ***args)
{
    int match = 0;
    char *tmp;
    char *regex_line;

    is_matching(str, mcmd.match_cmd, &match);
    if (!match)
        return (false);
    tmp = mymalloc(strlen(mcmd.match_cmd) + strlen(mcmd.match_args) + 1);
    if (!tmp)
        return (false);
    tmp = strcpy(tmp, mcmd.match_cmd);
    regex_line = must_be_line(strcat(tmp, mcmd.match_args));
    *args = is_matching(str, regex_line, &match);
    if (!myfree(tmp) && !myfree(regex_line) && !match)
        *args = myfree_tab(*args);
    return (match + 1);
}

static bool server_handle_cmd(server_t *serv, client_t *sock, const char *str)
{
    char **args = NULL;
    bool rvalue;
    int v;

    for (int i = 0; MCMD[i].match_cmd; i++) {
        v = server_match_cmd(str, MCMD[i], &args);
        if (v == 2) {
            rvalue = MCMD[i].cmd ? MCMD[i].cmd(serv, sock, args) :
                WRITE(sock, ERROR_UNIMPLEMENTED RFC_END);
            rvalue = rvalue && WRITE(sock, RFC_END);
            return (!myfree_tab(args) && rvalue);
        } else if (v == 1)
            return (WRITE(sock, ERROR_ARGS RFC_END));
    }
    return (WRITE(sock, ERROR_UNKNOWN RFC_END));
}

bool server_handler(object *this, principe_t *socket)
{
    char *buffer = NULL;

    if (FD(this) == FD(socket))
        return (server_new_connection(this));
    if (READ(socket, buffer) && buffer) {
        if (start_with(buffer, "/"))
            ONLINE(socket) = server_handle_cmd(this, CLIENT(socket),
                    buffer + 1);
    } else
        ONLINE(socket) = false;
    return (!myfree(buffer) && ONLINE(socket));
}

bool server_reception(object *this)
{
    struct timeval tv = {.tv_sec = 0, .tv_usec = 1};
    fd_set rfds;
    int value = -1;

    if (this) {
        FD_ZERO(&rfds);
        loop_list(CLIENTS(this), loop_rfds, &rfds, &value);
        value = select(value + 1, &rfds, NULL, NULL, &tv);
        if (value)
            loop_list(CLIENTS(this), loop_try_handle, &rfds, this);
        loop_list(CLIENTS(this), loop_disconnected, &CLIENTS(this));
    }
    return (this);
}