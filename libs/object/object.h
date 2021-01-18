/*
** EPITECH PROJECT, 2018
** NWP_myftp_2019
** File description:
** object.h
*/

#ifndef NWP_MYFTP_2019_OBJECT_H
#define NWP_MYFTP_2019_OBJECT_H

#include <stdbool.h>
#include <sys/types.h>
#include <stdarg.h>

typedef void object;
typedef bool (*ctor_t)(object *this, va_list *args);
typedef void (*dtor_t)(object *this);

typedef struct {
    const size_t __size__;
    const char * __name__;
    ctor_t __ctor__;
    dtor_t __dtor__;
    const char *__regex__;
} class;

#endif //NWP_MYFTP_2019_OBJECT_H
