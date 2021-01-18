/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** write.c
*/

#include "utils.h"
#include "macro.h"
#include "server/class.h"
#include "server/save.h"

void write_save(server_t *serv)
{
    FILE *ptr_fd = fopen("myteams.xml", "w");

    if (!ptr_fd)
        return;
    fprintf(ptr_fd, "%s\n", XML_HEADER);
    fprintf(ptr_fd, "<server>\n");
    write_list((list_writer_t){USERS(serv), user_access, ptr_fd, 1});
    write_list((list_writer_t) {serv->teams, context_access, ptr_fd, 1});
    write_list((list_writer_t){serv->messages, msg_access, ptr_fd, 1});
    fprintf(ptr_fd, "</server>");
    fclose(ptr_fd);
}