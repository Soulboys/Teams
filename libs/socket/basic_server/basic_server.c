/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** basic_server.c
*/

#include "basic_server.h"
#include "../prototype.h"

bool basic_server_ctor(object *this, va_list *args)
{
    long port = va_arg(*args, long);
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    int good = 1;
    bool success = !setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &good,
        sizeof(int)) &&
        principe_ctor(this, port, INADDR_ANY, fd) &&
        bind(fd, (saddr *)&SADDR(this), sizeof(saddr_in)) >= 0 &&
        listen(fd, 4096) >= 0;

    return (success && NEW_CLIENT(this) ?
        NEW_CLIENT(this)(SADDR(this), &CLIENTS(this), fd) : false);
}

void basic_server_dtor(object *this)
{
    if (this)
        clear_list(&CLIENTS(this), CLEAR_CLIENTS(this));
}