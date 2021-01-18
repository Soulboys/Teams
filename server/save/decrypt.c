/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** write.c
*/

#include <string.h>
#include <stdlib.h>
#include "myregex.h"
#include "mystring.h"
#include "client/class.h"
#include "server/class.h"
#include "server/save.h"
#include "server/prototype.h"
#include "utils.h"
#include "macro.h"

static char *get_value(const class *c, int findex, char *str, size_t *size)
{
    static const char *formats[][2] = {{"<%s>", "</%s>"}, {"<%ss>", "</%ss>"}};
    char *tags[2] = { malloc(1024), malloc(1024) };
    char *newstr;

    sprintf(tags[0], formats[findex][0], c->__name__);
    sprintf(tags[1], formats[findex][1], c->__name__);
    newstr = get_between_strings(tags, str, size);
    (void)(!myfree(tags[0]) && myfree(tags[1]));
    return (newstr);
}

static size_t load_part(char *value, const class *c, list_t *list)
{
    size_t r = 0;
    char **a = NULL;
    class *b = NULL;

    a = is_matching(value, c->__regex__, (int*)&r);
    if (r)
        add_to_list(list, new(c, 1, a));
    r = strlen(a[0]);
    b = get_last(*list, 1);
    if (b && r < strlen(value)) {
        if (b->__size__ == sizeof(context_t) || b->__size__ == sizeof(team_t))
            r += decrypt_part(value + r, CONTEXT(b)->subclass,
                    &CONTEXT(b)->list, true);
        if (b->__size__ == sizeof(team_t))
            r += decrypt_part(value + r, context_id, &SUBSCRIBED(b), true);
    }
    return (myfree_tab(a), r);
}

static size_t load_msg(char *value, list_t *list)
{
    size_t r[3] = {0, 0, 0};
    static char *tags[2] = { "<string>", "</string>"};
    char **a = is_matching(value, context_id->__regex__, (int*)&r[0]);
    char *msg = NULL;
    context_id_t *ids[2] = { NULL, NULL };

    if (r[0]) {
        ids[0] = new(context_id, 1, a);
        r[0] = strlen(a[0]) + 9;
        myfree_tab(a);
        a = is_matching(value + r[0], context_id->__regex__, (int*)&r[1]);
        if (r[1]) {
            ids[1] = new(context_id, 1, a);
            r[1] = strlen(a[0]) + 9;
        }
        myfree_tab(a);
        msg = get_between_strings(tags, value + r[0] + r[1], &r[2]);
    }
    if (msg)
        add_to_list(list, new(message, ids[0], ids[1], msg));
    return (myfree(msg), delete(ids[0]), delete(ids[1]), r[1] + r[2] + r[0]);
}

size_t decrypt_part(char *str, const class *c, list_t *list, bool multiple)
{
    size_t size = 0;
    char *value = get_value(c, multiple, str, &size);

    if (value && multiple) {
        decrypt_part(value, c, list, false);
    } else if (value) {
        c == message ? load_msg(value, list) : load_part(value, c, list);
        if (strlen(str + size) > 0)
            decrypt_part(str + size, c, list, false);
    }
    myfree(value);
    return (size);
}

void decrypt(char *arr[2], server_t *serv)
{
    size_t s;

    arr[1] = get_value(server, 0, arr[0] + strlen(XML_HEADER), NULL);
    if (strlen(arr[1]) > 0) {
        s = decrypt_part(arr[1], context_id, &USERS(serv), true);
        if (strlen(arr[1] + s) > 0)
            s += decrypt_part(arr[1] + s, team, &serv->teams, true);
        if (strlen(arr[1] + s) > 0)
            decrypt_part(arr[1] + s, message, &serv->messages, true);
    }
}

