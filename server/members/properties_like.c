/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** properties_like.c
*/

#include "server/class.h"

list_t *server_context_list(server_t *serv)
{
    return (serv->context ? &serv->context->list : &serv->teams);
}

const class *server_new_context(server_t *serv)
{
    return (serv->context ? serv->context->subclass : team);
}