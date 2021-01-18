/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** main.c
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include "function.h"
#include "myregex.h"
#include "../libs/utils/utils.h"
#include "server/encapsulated.h"

static int usage(void)
{
    printf("USAGE: ./myteams_server port\n"
        "port is the port number on which the basic_server"
        " socket listens.\n");
    return (0);
}

static void sighandler(int sig)
{
    if (sig == SIGINT)
        printf("\n");
    delete(encapsulated_server(-1));
    exit(0);
}

static int pre_start(long port)
{
    server_t *lserver = encapsulated_server(port);

    if (!lserver)
        return (84);
    signal(SIGINT, sighandler);
    signal(SIGPIPE, sighandler);
    signal(SIGTERM, sighandler);
    while (encapsulated_can_wait(-1) && RECEPTION(lserver)(lserver));
    delete(encapsulated_server(-1));
    return (0);
}

int main(int ac, char **av)
{
    int res = 0;
    char *endptr;

    if (ac == 2 && !strcmp(av[1], "-h"))
        return (usage());
    else if (ac == 2 && !myfree_tab(is_matching(av[1], "\\d+", &res)) && !res)
        return (pre_start(strtol(av[1], &endptr, 10)));
    return (84);
}
