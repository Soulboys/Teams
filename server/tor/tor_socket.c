/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** ctor.c
*/

#include "prototype.h"
#include "server/save.h"
#include "server/class.h"
#include "server/prototype.h"
#include "basic_server/basic_server.h"

bool server_new_client(saddr_in sa, list_t *list, int fd)
{
    client_t *cli = new(client, 1, fd, ntohs(sa.sin_port), sa.sin_addr.s_addr);
    int size = list->size;

    if (!cli) {
        fprintf(stdout, "teams:[%s, %d]: \033[31;1m%s\033[0m\n",
                __FILE__, __LINE__, "unable to create a new basic_client");
        return (false);
    }
    add_to_list(list, cli);
    if (size >= list->size) {
        delete(cli);
        fprintf(stdout, "teams:[%s, %d]: \033[31;1m%s\033[0m\n",
                __FILE__, __LINE__, "unable to create a new node");
        return (false);
    }
    return (true);
}

bool server_ctor(object *this, va_list *args)
{
    bool b = basic_server_ctor(this, args);

    if (b) {
        read_save(this);
        SERVER_START(this);
    }
    return (b);
}

void server_dtor(object *this)
{
    basic_server_dtor(this);
    if (this) {
        clear_list(&USERS(this), node_class_clear);
        clear_list(&SERVER(this)->teams, node_class_clear);
        clear_list(&SERVER(this)->messages, node_class_clear);
    }
}

bool client_rfc_write(client_t *cli, const char *rfc, const char *msg)
{
    bool success = WRITE(cli, rfc) && WRITE(cli, "\n");

    if (success && msg)
        success = WRITE(cli, msg) && WRITE(cli, "\n");
    return (success);
}
