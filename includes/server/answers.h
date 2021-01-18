/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** server_answers.h
*/

#ifndef NWP_MYTEAMS_2019_ANSWERS_H
#define NWP_MYTEAMS_2019_ANSWERS_H

#include "client/class.h"
#include "server/class.h"

typedef struct {
    char *match_cmd;
    char *match_args;
    answer_t cmd;
    int help_index;
} match_command_t;

bool help(server_t *, client_t *socket, char **args);
bool login(server_t *serv, client_t *socket, char **args);
bool logout(server_t *serv, client_t *socket, char **args);
bool users(server_t *serv, client_t *socket, char **args);
bool user(server_t *serv, client_t *socket, char **args);
bool create(server_t *serv, client_t *socket, char **args);
bool use(server_t *serv, client_t *socket, char **args);
bool list(server_t *serv, client_t *socket, char **args);
bool subscribe(server_t *serv, client_t *sock, char **a);
bool unsubscribe(server_t *serv, client_t *sock, char **a);
bool subscribed(server_t *serv, client_t *socket, char **args);
bool info(server_t *serv, client_t *cli, char **args);
bool send_msg(server_t *serv, client_t *cli, char **args);
bool messages(server_t *serv, client_t *cli, char **args);

#define LALL "\\s+\"((.+))\""
#define ALNUM "\\s+\"([[:alnum:][:space:]]+)\""
#define LALNUM "\\s+\"(([[:alnum:][:space:]]+))\""
#define LUNALNUM "\\s*\"*(([[:alnum:][:space:]]*))\"*"
#define MYUUID "\\s+\"([[:alnum:]-]+)\""
#define LMYUUID "\\s+\"(([[:alnum:]-]+))\""
#define UNMYUUID "\\s*\"*([[:alnum:]-]*)\"*"
#define LUNMYUUID "\\s*\"*(([[:alnum:]-]*))\"*"

static const match_command_t MCMD[] = {
    {"help", "", &help, 0},
    {"login", LALNUM, &login, 1},
    {"logout", "", &logout, 2},
    {"users", "", &users, 3},
    {"user", LMYUUID, &user, 4},
    {"send", MYUUID LALL, &send_msg, 5},
    {"messages", LMYUUID, &messages, 6},
    {"subscribed", LUNMYUUID, &subscribed, 8},
    {"unsubscribe", LMYUUID, &unsubscribe, 9},
    {"subscribe", LMYUUID, &subscribe, 7},
    {"use", UNMYUUID UNMYUUID LUNMYUUID, &use, 10},
    {"create", ALNUM LUNALNUM, &create, 11},
    {"list", "", &list, 12},
    {"info", "", &info, 13},
    {NULL, NULL, NULL, -1}
};

#endif //NWP_MYTEAMS_2019_ANSWERS_H
