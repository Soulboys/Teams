/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** encapsulated.c
*/

#include "server/class.h"

server_t *encapsulated_server(long port)
{
    static server_t *serv = NULL;

    if (!serv && port)
        serv = new(server, port);
    return (serv);
}

bool encapsulated_can_wait(int value)
{
    static bool can_wait = true;

    if (value != -1)
        can_wait = value;
    return (can_wait);
}