/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** ctor.c
*/

#include <string.h>
#include "utils.h"
#include "server/class.h"
#include "context/context.h"

bool msg_ctor(object *this, va_list *args)
{
    context_id_t *ids[2] = {va_arg(*args, context_id_t*),
                            va_arg(*args, context_id_t*)};
    char *str = va_arg(*args, char*);

    MESSAGE(this)->from = new(context_id, true,
            (char *[]){NULL, ids[0]->name, ids[0]->uuid});
    MESSAGE(this)->to = ids[1] ?
            new(context_id, true,
            (char *[]){NULL, ids[1]->name, ids[1]->uuid}) : NULL;
    MESSAGE(this)->message = strdup(str);
    time(&MESSAGE(this)->time);
    return (MESSAGE(this)->from &&
        MESSAGE(this)->message);
}