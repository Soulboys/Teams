/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** basic_client.c
*/

#include <unistd.h>
#include "../prototype.h"
#include "basic_client.h"

bool basic_client_ctor(object *this, va_list *args)
{
    int is_intern = va_arg(*args, int);
    int fd = !is_intern ? socket(PF_INET, SOCK_STREAM, 0) : va_arg(*args, int);
    long port = va_arg(*args, long);
    in_addr_t addr = va_arg(*args, in_addr_t);
    bool sucess = principe_ctor(this, port, addr, fd);

    if (!is_intern)
        sucess = !connect(FD(this), (saddr *)&SADDR(this), sizeof(saddr_in));
    return (sucess);
}

void basic_client_dtor(object *this)
{
    if (this) {
        if (PTR_FD(this))
            fclose(PTR_FD(this));
        else if (FD(this) > -1)
            close(FD(this));
    }
}