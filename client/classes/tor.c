/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** classes.c
*/

#include "prototype.h"
#include "client/class.h"

void client_dtor(object *this)
{
    basic_client_dtor(this);
    if (this && CLIENT(this)->user)
        delete(CLIENT(this)->user);
}