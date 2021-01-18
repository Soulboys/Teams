/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** read.c
*/

#include <sys/stat.h>
#include <string.h>
#include "utils.h"
#include "server/class.h"
#include "server/save.h"
#include "server/prototype.h"
#include "logging_server.h"

static char *read_file(void)
{
    static const char *save = "myteams.xml";
    FILE *fd = fopen(save, "r");
    struct stat buf;
    char *str = NULL;

    if (stat(save, &buf) == -1 || !fd || !rmalloc(buf.st_size + 1, &str))
        return (NULL);
    fread(str, buf.st_size, 1, fd);
    fclose(fd);
    str[buf.st_size] = '\0';
    str = replace(str);
    return (str);
}

static void logged_access(node_t *node, va_list list)
{
    context_id_t *id = node->data;

    (void)list;
    server_event_user_loaded(id->uuid, id->name);
}

void read_save(server_t *serv)
{
    char *arr[2] = { read_file(), NULL};

    if (arr[0]) {
        decrypt(arr, serv);
        loop_list(USERS(serv), logged_access);
    }
    myfree(arr[0]);
    myfree(arr[1]);
}