/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** principe.c
*/

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "principe.h"
#include "mystring.h"

bool principe_ctor(object *this, ...)
{
    principe_t *principe = this;
    va_list list;

    va_start(list, this);
    principe->data.sa.sin_family = AF_INET;
    principe->data.sa.sin_port = htons(va_arg(list, long));
    principe->data.sa.sin_addr.s_addr = va_arg(list, in_addr_t);
    principe->data.fd = va_arg(list, int);
    va_end(list);
    return (true);
}

void principe_dtor(object *this)
{
    (void)this;
}

static char *erase(char *buffer, const char *str)
{
    char *tmp;

    tmp = buffer;
    buffer = trim_end(tmp, str);
    free(tmp);
    return (buffer);
}

bool principe_read(object *this, char **string_ptr)
{
    size_t size;
    principe_t *sock = this;
    char *buffer = NULL;
    int rvalue;

    if (!sock->data.ptr_fd)
        sock->data.ptr_fd = fdopen(sock->data.fd, "r");
    rvalue = getline(&buffer, &size, sock->data.ptr_fd);
    *string_ptr = rvalue == -1 ? NULL: erase(erase(buffer, "\r\n"), "\n");
    if (rvalue == -1)
        free(buffer);
    return (rvalue != -1);
}

bool principe_write(object *this, const char *str)
{
    return (write(((principe_t *)this)->data.fd, str, strlen(str)) >= 0);
}