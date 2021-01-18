/*
** EPITECH PROJECT, 2018
** NWP_myftp_2019
** File description:
** function.c
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "object.h"
#include "macro.h"

static void *raise(const char *message)
{
    fprintf(stderr, "%s: %u: %s\n", __FILE__, __LINE__, message);
    return (NULL);
}

void *delete(object *ptr)
{
    if (ptr && ((class*)ptr)->__dtor__)
        ((class*)ptr)->__dtor__(ptr);
    free(ptr);
    return (NULL);
}

static object *va_new(const class *class, va_list *ap)
{
    object *new = NULL;

    if (!class)
        return (raise(CLASS_NULL));
    new = malloc(class->__size__);
    if (!new)
        return (raise(MALLOC_FAILED));
    memcpy(new, class, class->__size__);
    if (class->__ctor__ && !class->__ctor__(new, ap)) {
        delete(new);
        new = NULL;
    }
    return (new);
}

object *new(const class *class, ...)
{
    object *new = NULL;
    va_list args;

    va_start(args, class);
    new = va_new(class, &args);
    va_end(args);
    return (new);
}