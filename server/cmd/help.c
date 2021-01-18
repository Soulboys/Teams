/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** help.c
*/

#include "server/answers.h"

static const char *HELP_STR[] = {
    "\thelp\n",
    "\tlogin\n",
    "\tlogout\n",
    "\tusers\n",
    "\tuser\n",
    "\tsend\n",
    "\tmessages\n",
    "\tsubscribe\n",
    "\tsubscribed\n",
    "\tunsubscribe\n",
    "\tuse\n",
    "\tcreate\n",
    "\tlist\n",
    "\tinfo\n"
};

bool help(server_t *serv, client_t *socket, char **args)
{
    bool success = WRITE(socket,
            "HLP\nThe followings commands are recognized.\n");

    (void)serv;
    (void)args;
    for (int i = 0; success && MCMD[i].help_index != -1; i++)
        success = WRITE(socket, HELP_STR[MCMD[i].help_index]);
    return (success);
}