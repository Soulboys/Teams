##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Use to compile Cpp code
##

## Colors
REDDARK	=	\033[31;2m
RED		=	\033[31;1m
GREEN	=	\033[32;1m
YEL		=	\033[33;1m
BLUE	=	\033[34;1m
PINK	=	\033[35;1m
CYAN	=	\033[36;1m
RES		=	\033[0m

## Parameters
DEBUG=1
CC=gcc
LDFLAGS= -lmyteams -luuid -L./libs/myteams -lsocket -lmystring -lmyregex -lobject -llist -lutils
ifeq ($(DEBUG),1)
	CFLAGS=-W -Wall -Wextra -Werror -g
else
	CFLAGS=-W -Wall -Wextra
endif

## Compilated Files Names
EXEC_SERVER=myteams_server
EXEC_CLIENT=myteams_cli
EXEC_LIB=libraries
EXEC_ALL= $(EXEC_LIB) $(EXEC_SERVER) $(EXEC_CLIENT)
##Directories
DIR_SERVER=server/
DIR_CLIENT=client/
DIR_COMMUN=commun/

SRC_COMMUN= context_id.c	\
			tor.c			\

SRC_SERVER=	main.c				\
			encapsulated.c		\
			utils.c				\
			utils_extended.c	\
			classes/socket.c	\
			classes/context.c	\
			tor/ctor_context.c	\
			tor/ctor_utils.c	\
			tor/tor_socket.c	\
			tor/dtor.c			\
			members/loop.c		\
			members/methods.c	\
			members/properties_like.c	\
			save/write.c		\
			save/accesser.c		\
			save/decrypt.c		\
			save/utils.c		\
			save/read.c			\
			cmd/help.c			\
			cmd/log.c			\
			cmd/users.c			\
			cmd/user.c			\
			cmd/create.c		\
			cmd/use.c			\
			cmd/list.c			\
			cmd/info.c			\
			cmd/messages.c		\
			cmd/subscription/subscription.c	\
			cmd/subscription/list.c			\

SRC_CLIENT =	main.c				\
				encapsulated.c		\
				cmd.c				\
				classes/socket.c	\
				classes/tor.c		\
				cmd/log.c			\
				cmd/uuid.c			\
				cmd/create.c		\
				cmd/subscription.c	\
				cmd/list.c			\
				cmd/messages.c		\

## Dirs Src Files
DIRS_SRC_SERVER=$(addprefix $(DIR_SERVER), $(SRC_SERVER))
DIRS_SRC_CLIENT=$(addprefix $(DIR_CLIENT), $(SRC_CLIENT))
DIRS_SRC_COMMUN=$(addprefix $(DIR_COMMUN), $(SRC_COMMUN))
## Obj Src
OBJ_SERVER= $(DIRS_SRC_SERVER:.c=.o) $(DIRS_SRC_COMMUN:.c=.o)
OBJ_CLIENT= $(DIRS_SRC_CLIENT:.c=.o) $(DIRS_SRC_COMMUN:.c=.o)
OBJ_ALL = $(OBJ_SERVER) $(OBJ_CLIENT)

##OTHER FLAGS
INCLUDE=-I./includes -I./libs/object -I./libs/list -I./libs/myregex -I./libs/mystring -I./libs/utils -I./libs/socket/ -I./libs/myteams

MAKE_RULE=make --no-print-directory -C $(dir) ;
MAKE_CLEAN=make clean --no-print-directory -C $(dir) ;
MAKE_FCLEAN=make fclean --no-print-directory -C $(dir) ;
FIND_SUB_DIR_LIBS=$(wildcard ./libs/*/)

## Rules
all: $(EXEC_ALL)

re: fclean
	@echo -e "--------------------"
	@make --no-print-directory all

$(EXEC_SERVER): $(OBJ_SERVER)
	@$(CC) -o $(EXEC_SERVER) $^ $(LDFLAGS)
	@echo -e "--------------------"
	@echo -e " $(YEL)$@$(RES)"

$(EXEC_CLIENT): $(OBJ_CLIENT)
	@$(CC) -o $(EXEC_CLIENT) $^ $(LDFLAGS)
	@echo -e "--------------------"
	@echo -e " $(YEL)$@$(RES)"

$(EXEC_LIB):
	@$(foreach dir, $(FIND_SUB_DIR_LIBS), $(MAKE_RULE))

clean:
	@rm -rf $(OBJ_ALL)
	@rm -rf vg*
	@$(foreach dir, $(FIND_SUB_DIR_LIBS), $(MAKE_CLEAN))
	@echo -e "$(GREEN)$@$(RES): $(YEL)$(EXEC_CORE)$(RES)"

fclean:
	@rm -rf $(OBJ_ALL)
	@rm -rf vg*
	@rm -rf $(EXEC_ALL)
	@$(foreach dir, $(FIND_SUB_DIR_LIBS), $(MAKE_FCLEAN))
	@echo -e "$(GREEN)$@$(RES): $(YEL)$(EXEC_SERVER) $(EXEC_CLIENT)$(RES)"

## Defaults Rules
%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS) $(INCLUDE)
	@echo -e "$(CYAN)[DONE] $(BLUE)$@$(RES)"

.PHONY: all clean fclean re
