/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** write.c
*/

#include <string.h>
#include "client/class.h"
#include "server/class.h"
#include "server/save.h"
#include "macro.h"

void write_list(list_writer_t writer)
{
    const char *str = writer.list.size ?
    ((class *)writer.list.nodes->data)->__name__ : NULL;

    if (str) {
        padding(writer.ptr_fd, writer.padding, "<%ss>\n", str);
        loop_list(writer.list, writer.access, writer);
        padding(writer.ptr_fd, writer.padding, "</%ss>\n", str);
    }
}

void user_access(node_t *node, va_list list)
{
    list_writer_t writer = va_arg(list, list_writer_t);

    write_id(node->data, writer.ptr_fd, writer.padding);
}

void msg_access(node_t *node, va_list list)
{
    list_writer_t w = va_arg(list, list_writer_t);
    message_t *msg = node->data;

    padding(w.ptr_fd, w.padding + 1, "<%s>\n", msg->base.__name__);
    write_id(msg->from, w.ptr_fd, w.padding + 1);
    if (msg->to)
        write_id(msg->to, w.ptr_fd, w.padding + 1);
    padding(w.ptr_fd, w.padding + 2, "<string>%s</string>\n", msg->message);
    padding(w.ptr_fd, w.padding + 1, "</%s>\n", msg->base.__name__);
}

void context_access(node_t *node, va_list list)
{
    list_writer_t w = va_arg(list, list_writer_t);
    context_t *c = node->data;

    padding(w.ptr_fd, w.padding + 1, "<%s>\n", c->base.__name__);
    write_id(c->id, w.ptr_fd, w.padding + 1);
    padding(w.ptr_fd, w.padding + 2, "<text>%s</text>\n", c->text);
    padding(w.ptr_fd, w.padding + 2, "<time>", NULL);
    fprintf(w.ptr_fd, "%ld</time>\n", c->time);
    write_list((list_writer_t) {c->list, IS(c->subclass, message) ?
        msg_access : context_access, w.ptr_fd, w.padding + 2});
    if (c->base.__size__ == sizeof(team_t))
        write_list((list_writer_t){TEAM(c)->subscribed, user_access,
            w.ptr_fd, w.padding + 2});
    padding(w.ptr_fd, w.padding + 1, "</%s>\n", c->base.__name__);
}