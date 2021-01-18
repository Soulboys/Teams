/*
** EPITECH PROJECT, 2018
** NWP
** File description:
** macro.c
*/

#ifndef NWP_MYTEAMS_2019_MACRO_H
#define NWP_MYTEAMS_2019_MACRO_H

#define MAX_NAME_LENGTH 32
#define MAX_DESCRIPTION_LENGTH 255
#define MAX_BODY_LENGTH 512
#define RFC_LENGTH 3

#define XML_HEADER "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
#define CID_REGEX "<name>([[:alnum:][:space:]]+)</name>" \
    "<uuid>(([[:alnum:]-]+))</uuid>"
#define ID_REGEX "<name>([[:alnum:][:space:]]+)</name>" \
    "<uuid>([[:alnum:]-]+)</uuid>"
#define CONTEXT_REGEX "<id>" ID_REGEX "</id><text>([[:alnum:][:space:]]+)"  \
    "</text><time>(([[:alnum:]-]+))</time>"

/*************  RFC  **************/

#define RFC_NO_RETURN "NOR"
#define RFC_END "END\n"

// ERROR
#define RFC_INTERNAL_ERROR "ERI"
#define RFC_UNKNOWN_CMD "ERC"
#define RFC_ARGUMENT_ERROR "ERA"
#define RFC_BAD_UUID "ERU"
#define RFC_ALREADY "ERD"

//RFC_UUID_TYPE
#define RFC_MSG "MSG"
#define RFC_TEAM "TEA"
#define RFC_CHANNEL "CHA"
#define RFC_THREAD "THR"
#define RFC_USER "USR"

// TOO LONG
#define RFC_TL_NAME "TLN"
#define RFC_TL_BODY "TLB"
#define RFC_TL_DESC "TLD"

// LOG
#define RFC_LOGIN "LGI"
#define RFC_LOGOUT "LGO"
#define RFC_UNAUTHORIZED "LGE"

//SUB
#define RFC_SUB_LIST "SBI"
#define RFC_SUB_JOIN "SBJ"
#define RFC_SUB_LEFT "SBL"

#define RFC_INFO "IFO"
#define RFC_LIST "LST"

//CREATE
#define RFC_CREATE "CRT"
#define RFC_CREATE_MSG "CRM"

//MESSAGES
#define RFC_SEND "MGS"
#define RFC_CONVERSATION "MGC"

/*********************************/

#define IS(c, c2) (!strcmp(((class *)c)->__name__, ((class *)c2)->__name__))

//ERROR
#define ERROR_LOCAL RFC_INTERNAL_ERROR "\nA local error occured...\n"
#define ERROR_UNIMPLEMENTED RFC_INTERNAL_ERROR "\nUnimplemented command !\n"
#define ERROR_UNKNOWN RFC_UNKNOWN_CMD "\nUnknown command (try \"/help\") !\n"
#define ERROR_ARGS RFC_ARGUMENT_ERROR "\nError on the arguments" \
    " (missing quotes or number) !\n"

//TOO LONG
#define TL_NAME RFC_TL_NAME "\nName is too long !\n"
#define TL_BODY RFC_TL_BODY "\nBody is too long !\n"
#define TL_DESCRIPTION RFC_TL_DESC "\nDescription is too long !\n"

#endif //NWP_MYTEAMS_2019_MACRO_H
