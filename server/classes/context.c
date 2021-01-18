/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** context.c
*/

#include "server/tor.h"
#include "server/class.h"
#include "context/context.h"
#include "macro.h"

static const message_t intern_message = {
        {
                .__size__ = sizeof(message_t),
                .__name__ = "message",
                .__ctor__ = &msg_ctor,
                .__dtor__ = &msg_dtor,
                .__regex__ = NULL,
        },
        .from = NULL,
        .to = NULL,
        .message = NULL,
};

static const context_t intern_thread= {
    {
        .__size__ = sizeof(context_t),
        .__name__ = "thread",
        .__ctor__ = &thread_ctor,
        .__dtor__ = &context_dtor,
        .__regex__ = CONTEXT_REGEX,
    },
    .subclass = (const class *)&intern_message,
    .id = NULL,
    {
        .size = 0,
        .nodes = NULL
    },
    .text = NULL,
    .time = 0,
};

static const context_t intern_channel= {
    {
        .__size__ = sizeof(context_t),
        .__name__ = "channel",
        .__ctor__ = &channel_ctor,
        .__dtor__ = &context_dtor,
        .__regex__ = CONTEXT_REGEX,
    },
    .subclass = (const class *)&intern_thread,
    .id = NULL,
    {
        .size = 0,
        .nodes = NULL
    },
    .text = NULL,
    .time = 0,
};

static const team_t intern_team = {
    {
        {
            .__size__ = sizeof(team_t),
            .__name__ = "team",
            .__ctor__ = &team_ctor,
            .__dtor__ = &team_dtor,
            .__regex__ = CONTEXT_REGEX,
        },
        .subclass = (const class *)&intern_channel,
        .id = NULL,
        {
            .size = 0,
            .nodes = NULL
        },
        .text = NULL,
        .time = 0,
    },
    {
        0,
        NULL,
    },
};

const class *team = (const class *)&intern_team;
const class *message = (const class *)&intern_message;
