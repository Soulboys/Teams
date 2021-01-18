/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** save.h
*/

#ifndef NWP_MYTEAMS_2019_SAVE_H
#define NWP_MYTEAMS_2019_SAVE_H

#include "list.h"
#include "server/class.h"
#include <stdio.h>

typedef struct list_writer_s {
    list_t list;
    node_access_args_t access;
    FILE *ptr_fd;
    int padding;
} list_writer_t;

void padding(FILE *, int, const char *, const char *);
void write_id(context_id_t *, FILE *, int);
void write_save(server_t *);

void write_list(list_writer_t);
void user_access(node_t *, va_list);
void context_access(node_t *, va_list);
void msg_access(node_t *, va_list);

void decrypt(char *arr[2], server_t *serv);
void read_save(server_t *);
size_t decrypt_part(char *str, const class *c, list_t *list, bool multiple);

#endif //NWP_MYTEAMS_2019_SAVE_H
