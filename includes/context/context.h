/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** class.h
*/

#ifndef NWP_MYTEAMS_2019_CONTEXT_H
#define NWP_MYTEAMS_2019_CONTEXT_H

#include "object.h"
#include "context_id.h"
#include "list.h"

typedef struct context_s {
    class base;
    time_t time;
    const class *subclass;
    context_id_t *id;
    list_t list;
    char *text;
} context_t;

#define CONTEXT(context) ((context_t *)context)
#define CID(context) CONTEXT(context)->id
#define CBINUUID(context) CID(context)->binuuid
#define CUUID(context) CID(context)->uuid
#define CNAME(context) CID(context)->name
#define TEXT(context) CONTEXT(context)->text
#define LIST(context) CONTEXT(context)->list

typedef struct team_s {
    context_t base;
    list_t subscribed;
} team_t;

#define TEAM(team) ((team_t *)team)
#define SUBSCRIBED(team) (TEAM(team)->subscribed)
extern const class *team;

#endif //NWP_MYTEAMS_2019_CONTEXT_H
