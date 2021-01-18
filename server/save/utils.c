/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** utils.c
*/

#include "client/class.h"
#include "server/save.h"

void padding(FILE *ptr_fd, int padding,
             const char *format, const char *str)
{
    for (int i = 0; i < padding; i++)
        fprintf(ptr_fd, "\t");
    if (str)
        fprintf(ptr_fd, format, str);
    else
        fprintf(ptr_fd, "%s", format);
}

void write_id(context_id_t *id, FILE *ptr_fd, int size)
{
    padding(ptr_fd, size + 1, "<id>\n", NULL);
    padding(ptr_fd, size + 2, "<name>%s</name>\n", id->name);
    padding(ptr_fd, size + 2, "<uuid>%s</uuid>\n", id->uuid);
    padding(ptr_fd, size + 1, "</id>\n", NULL);
}