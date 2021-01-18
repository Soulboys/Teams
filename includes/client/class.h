/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** class.h
*/

#ifndef NWP_MYTEAMS_2019_CLIENT_CLASS_H
#define NWP_MYTEAMS_2019_CLIENT_CLASS_H

#include <uuid/uuid.h>
#include "basic_client/basic_client.h"

#include "context/context_id.h"

typedef struct client_s {
    basic_client_t base;
    context_id_t *user;
    bool (*rfc_write)(struct client_s *, const char *, const char *);
} client_t;

#define CLIENT(sock) ((client_t *)sock)
#define UUID(sock) CLIENT(sock)->user->uuid
#define USER(sock) CLIENT(sock)->user
#define USERNAME(sock) CLIENT(sock)->user->name
#define RFC(sock, rfc, msg) CLIENT(sock)->rfc_write(CLIENT(sock), rfc, msg)

extern const class *client;

#endif //NWP_MYTEAMS_2019_CLIENT_CLASS_H
