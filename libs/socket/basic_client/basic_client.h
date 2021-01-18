/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** basic_client.h
*/

#ifndef NWP_MYTEAMS_2019_BASIC_CLIENT_H
#define NWP_MYTEAMS_2019_BASIC_CLIENT_H

#include "../principe/principe.h"

typedef struct basic_client_s {
    principe_t interface;
    bool online;
} basic_client_t;

#define BASIC_CLIENT(sock) ((basic_client_t*)sock)
#define ONLINE(sock) BASIC_CLIENT(sock)->online

#endif //NWP_MYTEAMS_2019_BASIC_CLIENT_H
