/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** encapsulated.c
*/

#ifndef NWP_MYTEAMS_2019_ENCAPSULATED_H
#define NWP_MYTEAMS_2019_ENCAPSULATED_H

#include "class.h"

client_t *encapsulated_client(long port, in_addr_t addr);
bool encapsulated_can_wait(int value);

#endif //NWP_MYTEAMS_2019_ENCAPSULATED_H
