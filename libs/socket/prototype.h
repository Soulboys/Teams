/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** prototype.h
*/

#ifndef NWP_MYTEAMS_2019_PROTOTYPE_H
#define NWP_MYTEAMS_2019_PROTOTYPE_H

#include "principe/principe.h"
#include "list.h"

/* PRINCIPE */
bool principe_ctor(object *this, ...);
void principe_dtor(object *this);
bool principe_read(object *this, char **string_ptr);
bool principe_write(object *this, const char *str);

/* CLIENT */
bool basic_client_ctor(object *this, va_list *args);
void basic_client_dtor(object *this);

/* SERVER */
bool basic_server_ctor(object *this, va_list *args);
void basic_server_dtor(object *this);

#endif //NWP_MYTEAMS_2019_PROTOTYPE_H
