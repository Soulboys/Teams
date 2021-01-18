/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** help.c
*/

#include <string.h>
#include <stdlib.h>
#include "macro.h"
#include "utils.h"
#include "context/context.h"
#include "server/save.h"
#include "server/class.h"
#include "server/members.h"
#include "logging_server.h"
#include "server/answers.h"
#include "server/prototype.h"

static int errors(char **args, bool is)
{
    size_t s = strlen(args[2]);

    return (!is && strlen(args[1]) > MAX_NAME_LENGTH ? 1 :
        !is && (s > MAX_DESCRIPTION_LENGTH || !s) ? 2 :
        is && strlen(args[1]) > MAX_BODY_LENGTH ? 3 : 0);
}

static bool cmp(node_t *node, va_list args)
{
    char *str = va_arg(args, char*);

    if (((class *)node->data)->__size__ == sizeof(message_t))
        return (false);
    return (!strcmp(CNAME(node->data), str));
}

static bool auto_subscribe(server_t *serv, client_t *cli, const char *uuid)
{
    static const char *sub = "subscribe ";
    char **args = NULL;
    bool rvalue;

    if (!rmalloc(sizeof(char*) * 3, &args))
        return (RFC(cli, ERROR_LOCAL, NULL));
    args[0] = malloc(strlen(sub) + strlen(uuid) + 1);
    args[1] = strdup(uuid);
    if (!args[0] || !args[1])
        return (!myfree(args[0]) && !myfree(args[1]) &&
            RFC(cli, ERROR_LOCAL, NULL));
    args[2] = NULL;
    rvalue = WRITE(cli, RFC_END) && subscribe(serv, cli, args);
    return (!myfree_tab(args) && rvalue);
}

static bool notify(server_t *serv, client_t *cli, void *ptr, context_t *cont)
{
    char buffer[1024];
    bool is_t = IS(ptr, team);

    if (is_t || IS(ptr, CONTEXT(team)->subclass)) {
        sprintf(buffer, "%s\n%s\n%s\n%s", is_t ? RFC_TEAM : RFC_CHANNEL,
            CUUID(ptr), CNAME(ptr), TEXT(ptr));
    } else if (IS(ptr, CONTEXT(CONTEXT(team)->subclass)->subclass)) {
        sprintf(buffer, "%s\n%s\n%s\n%ld\n%s\n%s", RFC_THREAD,
            CUUID(ptr), UUID(cli), CONTEXT(ptr)->time, CNAME(ptr), TEXT(ptr));
    } else {
        sprintf(buffer, "%s\n%s\n%s\n%s\n%s", RFC_MSG, CUUID(cont),
            CUUID(serv->context), UUID(cli), MESSAGE(ptr)->message);
        server_event_thread_new_message(CUUID(serv->context), UUID(cli),
            MESSAGE(ptr)->message);
    }
    loop_list(CLIENTS(serv), send_str, cont ? SUBSCRIBED(cont) : USERS(serv),
        RFC_CREATE_MSG, buffer, NULL, IS(ptr, message) ? NULL : UUID(cli));
    return (RFC(cli, RFC_CREATE, buffer) &&
        (!is_t || auto_subscribe(serv, cli, CUUID(ptr))));
}

bool create(server_t *serv, client_t *socket, char **args)
{
    const class *aclass = serv->new_context(serv);
    context_t *t = find_team(aclass, serv);
    void *value;
    bool is = IS(aclass, message);
    int error = errors(args, is);
    char *errors[] = { ERROR_LOCAL, TL_NAME, TL_DESCRIPTION, TL_BODY };
    bool can = !USER(socket) ||
        (t && !get_cmp(SUBSCRIBED(t), cmp_context_uuid, UUID(socket)));

    if (can || get_cmp(*serv->context_list(serv), cmp, args[1]))
        return (RFC(socket, can ? RFC_UNAUTHORIZED : RFC_ALREADY, NULL));
    value = error ? NULL : !is ? new(aclass, false, args[1], args[2], socket,
            serv->context ? CUUID(serv->context) : NULL) :
            new(aclass, USER(socket), NULL, args[1]);
    if (value) {
        add_to_list(serv->context_list(serv), value);
        write_save(serv);
    }
    return (!value ? WRITE(socket, errors[error]) :
        notify(serv, socket, value, t));
}