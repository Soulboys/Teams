/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** principe.h
*/

#ifndef NWP_MYTEAMS_2019_PRINCIPE_H
#define NWP_MYTEAMS_2019_PRINCIPE_H

#include <stdio.h>
#include <arpa/inet.h>
#include "object.h"
#include "function.h"

typedef bool (*read_t)(object *this, char **string_ptr);
typedef bool (*write_t)(object *this, const char *str);
typedef struct sockaddr_in saddr_in;
typedef struct sockaddr saddr;

typedef struct datas_s {
    int fd;
    FILE *ptr_fd;
    saddr_in sa;
} datas_t;

typedef struct principe_s {
    class base;
    datas_t data;
    read_t read;
    write_t write;
} principe_t;

#define FD(obj) (((principe_t *)obj)->data.fd)
#define PTR_FD(obj) (((principe_t *)obj)->data.ptr_fd)
#define SADDR(obj) (((principe_t *)obj)->data.sa)
#define PORT(obj) (ntohs(SADDR(obj).sin_port))
#define IP(obj) (inet_ntoa(SADDR(obj).sin_addr))
#define READ(obj, str) (((principe_t *)obj)->read((principe_t *)obj, &str))
#define WRITE(obj, str) (((principe_t *)obj)->write((principe_t *)obj, str))

#endif //NWP_MYTEAMS_2019_PRINCIPE_H
