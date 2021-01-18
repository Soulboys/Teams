/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** info.c
*/

#include <string.h>
#include "server/class.h"
#include "client/class.h"
#include "macro.h"

bool info(server_t *serv, client_t *cli, char **args)
{
    bool success;
    char buffer[1024];
    context_t *c = serv->context;

    (void)args;
    if (c) {
        if (IS(c, team) || IS(c, CONTEXT(team)->subclass))
            sprintf(buffer, "%s\n%s\n%s\n%s", IS(c, team) ? RFC_TEAM :
            RFC_CHANNEL, CUUID(c), CNAME(c), TEXT(c));
        else
            sprintf(buffer, "%s\n%s\n%s\n%ld\n%s\n%s", RFC_THREAD, CUUID(c),
                    USERNAME(cli), CONTEXT(c)->time, CNAME(c), TEXT(c));
    } else if (USER(cli)){
        sprintf(buffer, "%s\n%s\n%s\n%d", RFC_USER, UUID(cli),
                USERNAME(cli), 1);
    }
    success = RFC(cli, USER(cli) ? RFC_INFO : RFC_UNAUTHORIZED,
            USER(cli) ? buffer : NULL);
    return (success);
}