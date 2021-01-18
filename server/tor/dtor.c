/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** dtor.c
*/

#include "server/class.h"
#include "context/context.h"
#include "server/prototype.h"
#include "utils.h"

void context_dtor(object *this)
{
    delete(((context_t*)this)->id);
    clear_list(&LIST(this), node_class_clear);
    myfree(TEXT(this));
}

void team_dtor(object *this)
{
    context_dtor(this);
    clear_list(&TEAM(this)->subscribed, node_class_clear);
}

void msg_dtor(object *this)
{
    if (this) {
        myfree(MESSAGE(this)->message);
        delete(MESSAGE(this)->from);
        delete(MESSAGE(this)->to);
    }
}