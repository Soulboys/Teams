/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** context.c
*/

#include "macro.h"
#include "context/context_id.h"

static const context_id_t intern_id = {
        {
                .__size__ = sizeof(context_id_t),
                .__name__ = "id",
                .__ctor__ = &context_id_ctor,
                .__dtor__ = &context_id_dtor,
                .__regex__ = CID_REGEX,
        },
        .name = NULL
};

const class *context_id = (const class *)&intern_id;