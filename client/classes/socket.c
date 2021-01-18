/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** classes.c
*/

#include "prototype.h"
#include "server/tor.h"
#include "client/answers.h"
#include "client/class.h"

static const client_t intern_client = {
    {
        {
            {
                .__size__ = sizeof(client_t),
                .__name__ = "client",
                .__ctor__ = &basic_client_ctor,
                .__dtor__ = &client_dtor,
            },
            {
                .fd = -1,
                .ptr_fd = NULL
            },
            .read = &principe_read,
            .write = &principe_write,
        },
        .online = true,
    },
    .user = NULL
};

const class *client = (const class *)&intern_client;
