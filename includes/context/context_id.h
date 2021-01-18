/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** class.h
*/

#ifndef NWP_MYTEAMS_2019_CONTEXT_ID_H
#define NWP_MYTEAMS_2019_CONTEXT_ID_H

#include <uuid/uuid.h>
#include "object.h"

#define UUID_LENGTH 36

typedef struct context_id_s {
    class base;
    uuid_t binuuid;
    char uuid[UUID_LENGTH];
    char *name;
} context_id_t;

bool context_id_ctor(object *this, va_list *args);
void context_id_dtor(object *this);

#define CTID(ptr) ((context_id_t*)ptr)
extern const class *context_id;

#endif //NWP_MYTEAMS_2019_CONTEXT_ID_H
