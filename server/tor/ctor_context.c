/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** ctor.c
*/

#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "context/context.h"
#include "server/class.h"
#include "logging_server.h"

bool context_ctor(object *this, va_list *args)
{
    char *name = va_arg(*args, char*);
    char *description = va_arg(*args, char*);

    CID(this) = new(context_id, false, name);
    if (CID(this))
        TEXT(this) = strdup(description);
    if (CID(this) && !TEXT(this))
        CID(this) = myfree(CID(this));
    time(&CONTEXT(this)->time);
    return (CID(this) && TEXT(this));
}

static bool load_ctor(object *this, char **args)
{
    char *endptr = NULL;

    CID(this) = new(context_id, true, args);
    TEXT(this) = strdup(args[3]);
    CONTEXT(this)->time = strtol(args[4], &endptr, 10);
    return (true);
}

bool team_ctor(object *this, va_list *args)
{
    int v = va_arg(*args, int);
    char **argts;

    if (v) {
        argts = va_arg(*args, char**);
        return (load_ctor(this, argts));
    } else if (context_ctor(this, args)) {
        server_event_team_created(CUUID(this), CNAME(this),
            UUID(va_arg(*args, client_t *)));
        return (true);
    }
    return (false);
}

bool channel_ctor(object *this, va_list *args)
{
    int v = va_arg(*args, int);
    char **argts;

    if (v) {
        argts = va_arg(*args, char**);
        return (load_ctor(this, argts));
    } else if (context_ctor(this, args)) {
        va_arg(*args, client_t *);
        server_event_channel_created(va_arg(*args, char*),
            CUUID(this), CNAME(this));
        return (true);
    }
    return (false);
}

bool thread_ctor(object *this, va_list *args)
{
    char *a;
    client_t *cli;
    int v = va_arg(*args, int);
    char **argts;

    if (v) {
        argts = va_arg(*args, char**);
        return (load_ctor(this, argts));
    } else if (context_ctor(this, args)) {
        cli = va_arg(*args, client_t *);
        a = va_arg(*args, char*);
        server_event_thread_created(a, CUUID(this), UUID(cli), TEXT(this));
        v = CONTEXT(this)->list.size;
        add_to_list(&CONTEXT(this)->list,
                new(message, USER(cli), NULL, TEXT(this)));
        return (v < CONTEXT(this)->list.size);
    }
    return (false);
}