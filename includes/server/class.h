/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** class.h
*/

#ifndef NWP_MYTEAMS_2019_CLASS_H
#define NWP_MYTEAMS_2019_CLASS_H

#include "basic_server/basic_server.h"
#include "context/context.h"

typedef struct server_s {
    basic_server_t base;
    list_t users;
    list_t teams;
    list_t messages;
    context_t *context;
    list_t *(*context_list)(struct server_s *);
    const class *(*new_context)(struct server_s *);
} server_t;

typedef struct message_s {
    class base;
    context_id_t *from;
    context_id_t *to;
    char *message;
    time_t time;
} message_t;

#include "client/class.h"

typedef bool (*answer_t)(server_t *, client_t *, char **) ;

extern const class *server;
extern const class *message;

#define SERVER(sock) ((server_t *)sock)
#define USERS(sock) SERVER(sock)->users

#define MESSAGE(obj) ((message_t*)obj)
#define SERVER_START(from) printf("\033[36;1mServer with port %d, " \
"is started.\033[0m\n", PORT(from))
#define CONNECTION(from) printf("\033[32;1mConnection from %s:%hu\033[0m\n", \
IP(from), PORT(from))

#endif //NWP_MYTEAMS_2019_CLASS_H
