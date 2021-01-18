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
#include <arpa/inet.h>
#include "client/class.h"
#include "myregex.h"
#include "client/answers.h"
#include "utils.h"
#include "client/encapsulated.h"

static int usage(void)
{
    printf("USAGE: ./myteams_server ip port\n"
        "ip is the IPv4 address we want to connect to"
        "port is the port number on which the "
        " socket will connect.\n");
    return (0);
}

static int loop(client_t *cli)
{
    fd_set rfds;
    struct timeval tv = {.tv_sec = 0, .tv_usec = 1};
    int value = FD(cli);
    char *buffer = NULL;
    size_t size = 0;

    FD_ZERO(&rfds);
    FD_SET(0, &rfds);
    FD_SET(FD(cli), &rfds);
    value = select(value + 1, &rfds, NULL, NULL, &tv);
    if (value) {
        if (FD_ISSET(0, &rfds)) {
            getline(&buffer, &size, stdin);
            WRITE(cli, buffer);
            free(buffer);
        } else
            return (handle_cmd(cli));
    }
    return (1);
}

static void sighandler(int sig)
{
    if (sig == SIGINT)
        printf("\n");
    delete(encapsulated_client(-1, 0));
    exit(0);
}

static int pre_start(long port, char *ip)
{
    client_t *lclient = encapsulated_client(port, inet_addr(ip));

    if (!lclient)
        return (84);
    signal(SIGINT, sighandler);
    signal(SIGPIPE, sighandler);
    signal(SIGTERM, sighandler);
    while (encapsulated_can_wait(-1) && loop(lclient));
    delete(encapsulated_client(-1, 0));
    return (0);
}

int main(int ac, char **av)
{
    int res = 0;
    char *endptr;

    if (ac == 2 && !strcmp(av[1], "-h"))
        return (usage());
    else if (ac == 3 && !myfree_tab(is_matching(av[2], "\\d+", &res)) && !res)
        return (pre_start(strtol(av[2], &endptr, 10), av[1]));
    return (84);
}