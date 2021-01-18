/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** answer.h
*/

#ifndef NWP_MYTEAMS_2019_ANSWERS_H
#define NWP_MYTEAMS_2019_ANSWERS_H

#include "client/class.h"

typedef struct answer_s {
    const char *rfc;
    bool (*function)(client_t *);
} answer_t;

typedef struct unknown_s {
    const char *rfc;
    int (*function)(const char *);
} unknown_t;

void client_dtor(object *cli);

bool handle_cmd(client_t *cli);
char **fill_tab(client_t *cli, int nb);
bool print_rest(client_t *cli);

bool login(client_t *cli);
bool logout(client_t *cli);
bool unlogged(client_t *cli);

bool already(client_t *cli);
bool bad_uuid(client_t *cli);

bool create(client_t *cli);
bool event_created(client_t *cli);

bool info(client_t *cli);
bool list(client_t *cli);

bool subscribe(client_t *cli);
bool unsubscribe(client_t *cli);
bool subscribed(client_t *cli);

bool sended(client_t *cli);
bool conversation(client_t *cli);

bool no_return(client_t *cli);
#endif //NWP_MYTEAMS_2019_ANSWERS_H
