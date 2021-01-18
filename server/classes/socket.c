/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** classes.c
*/

#include "prototype.h"
#include "server/tor.h"
#include "server/class.h"
#include "server/members.h"
#include "client/class.h"

static const client_t intern_client = {
    {
        {
            {
                .__size__ = sizeof(client_t),
                .__name__ = "client",
                .__ctor__ = &basic_client_ctor,
                .__dtor__ = &basic_client_dtor,
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
    .user = NULL,
    .rfc_write = &client_rfc_write
};

static const server_t intern_server = {
    {
        {
            {
                .__size__ = sizeof(server_t),
                .__name__ = "server",
                .__ctor__ = &server_ctor,
                .__dtor__ = &server_dtor,
                .__regex__ = NULL,
            },
            {
                .fd = -1,
                .ptr_fd = NULL
            },
            .read = &principe_read,
            .write = &principe_write,
        },
        {
            .new_client = &server_new_client,
            .clear_clients = &clear,
        },
        .request_handler = &server_handler,
        .reception = &server_reception,
    },
    {
        .size = 0,
        .nodes = NULL,
    },
    {
        .size = 0,
        .nodes = NULL,
    },
    {
        .size = 0,
        .nodes = NULL,
    },
    .context = NULL,
    .context_list = &server_context_list,
    .new_context = &server_new_context,
};

const class *client = (const class *)&intern_client;
const class *server = (const class *)&intern_server;
