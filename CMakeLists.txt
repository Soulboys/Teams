cmake_minimum_required(VERSION 3.16)
project(NWP_myteams_2019 C)

set(CMAKE_C_STANDARD 99)

set(INCLUDES
        ./includes
        ./libs/object
        ./libs/list
        ./libs/myregex
        ./libs/mystring
        ./libs/utils
        ./libs/socket
        ./libs/myteams
        teams)

include_directories(${INCLUDES})

add_library(list STATIC
        libs/list/list.h
        libs/list/list_dynamic.c
        libs/list/list_static.c
        libs/list/node.c
        libs/list/node.h commun/context_id.c commun/tor.c)

add_library(myregex STATIC
        libs/myregex/myregex.c
        libs/myregex/myregex.h)

add_library(object STATIC
        libs/object/function.c
        libs/object/function.h
        libs/object/macro.h
        libs/object/object.h)

add_library(mystring STATIC
        libs/mystring/mystring.c
        libs/mystring/mystring.h libs/mystring/get_between.c)

add_library(socket STATIC
        libs/socket/basic_client/basic_client.c
        libs/socket/basic_client/basic_client.h
        libs/socket/prototype.h
        libs/socket/basic_server/basic_server.h
        libs/socket/basic_server/basic_server.c
        libs/socket/principe/principe.c
        libs/socket/principe/principe.h)

add_library(utils STATIC
        libs/utils/myerror.c
        libs/utils/memory.c)

add_executable(myteams_server
        libs/myteams/logging_client.h
        libs/myteams/logging_server.h
        includes/macro.h
        server/main.c
        server/encapsulated.c
        includes/server/encapsulated.h
        includes/server/class.h
        includes/client/class.h
        includes/server/prototype.h
        includes/server/members.h
        server/cmd/help.c
        server/cmd/log.c
        server/save/read.c
        server/save/write.c
        server/utils.c
        includes/server/save.h
        server/cmd/users.c
        server/classes/socket.c
        server/members/loop.c
        server/members/methods.c
        includes/server/answers.h
        server/cmd/user.c
        includes/context/context_id.h
        includes/context/context.h
        server/cmd/create.c
        server/cmd/use.c
        server/classes/context.c
        server/tor/ctor_utils.c
        server/tor/dtor.c
        includes/server/tor.h
        server/cmd/list.c
        server/cmd/subscription/subscription.c
        server/cmd/subscription/list.c
        server/cmd/info.c
        server/cmd/messages.c
        server/tor/ctor_context.c
        server/save/accesser.c server/save/utils.c server/save/decrypt.c server/tor/tor_socket.c server/utils_extended.c server/members/properties_like.c)

add_executable(myteams_client
        includes/client/encapsulated.h
        includes/client/answers.h
        client/main.c
        client/classes/socket.c
        client/encapsulated.c
        client/cmd.c
        client/cmd/log.c client/cmd/uuid.c client/cmd/create.c client/cmd/list.c client/cmd/subscription.c client/cmd/messages.c client/classes/tor.c)

target_link_libraries(myteams_server LINK_PUBLIC
        mystring
        myregex
        object
        list
        utils
        socket)