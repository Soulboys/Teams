/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** utils.c
*/

#include <string.h>
#include "server/class.h"
#include "context/context.h"
#include "macro.h"

static bool cmp_find_sub_context(node_t *node, va_list list)
{
    context_t *data = node->data;
    context_t *context = va_arg(list, context_t*);
    node_t *n = get(data->list, context, true);
    context_t *value = n ? n->data : NULL;

    if (!value && data->subclass->__size__ == sizeof(context_t)) {
        n = get_cmp(data->list, cmp_find_sub_context, context, value);
        value = n ? n->data : NULL;
    }
    return (value);
}

context_t *find_team(const class *c, server_t *serv)
{
    if (IS(c, team) || IS(c, CONTEXT(team)->subclass))
        return (serv->context);
    return (get_cmp(serv->teams, cmp_find_sub_context, serv->context)->data);
}
