/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** prototypes.h
*/

#ifndef NWP_MYTEAMS_2019_TOR_H
#define NWP_MYTEAMS_2019_TOR_H

#include "object.h"

bool team_ctor(object *this, va_list *args);
bool channel_ctor(object *this, va_list *args);
bool thread_ctor(object *this, va_list *args);
bool msg_ctor(object *this, va_list *args);

void context_dtor(object *this);
void team_dtor(object *this);
void msg_dtor(object *this);
#endif //NWP_MYTEAMS_2019_TOR_H
