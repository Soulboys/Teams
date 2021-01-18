/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** context.c
*/

#include <string.h>
#include <stdbool.h>
#include "utils.h"
#include "context/context_id.h"

bool context_id_ctor(object *this, va_list *args)
{
    context_id_t *obj = this;
    int i = va_arg(*args, int);
    char *str;
    char **argts;

    if (!i) {
        str = va_arg(*args, char*);
        uuid_generate_random(obj->binuuid);
        uuid_unparse(obj->binuuid, obj->uuid);
    } else {
        argts = va_arg(*args, char **);
        str = argts[1];
        uuid_parse(argts[2], obj->binuuid);
        uuid_unparse(obj->binuuid, obj->uuid);
    }
    obj->name = strdup(str);
    return (obj->name);
}

void context_id_dtor(object *this)
{
    context_id_t *id = this;

    myfree(id->name);
}