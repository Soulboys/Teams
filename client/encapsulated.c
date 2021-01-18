/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** encapsulated.c
*/

#include "client/class.h"

client_t *encapsulated_client(long port, in_addr_t addr)
{
    static client_t *cli = NULL;

    if (!cli && port)
        cli = new(client, 0, port, addr);
    return (cli);
}

bool encapsulated_can_wait(int value)
{
    static bool can_wait = true;

    if (value != -1)
        can_wait = value;
    return (can_wait);
}