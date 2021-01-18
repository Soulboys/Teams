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
LDFLAGS= -L../myteams/ -lobject -llist -lmystring -lmyregex -lutils
ifeq ($(DEBUG),1)
	CFLAGS=-W -Wall -Wextra -Werror -g
else
	CFLAGS=-W -Wall -Wextra
endif

## Compilated Files Names
EXEC_COM=libsocket.a
##Directories
SRC_COM=	principe/principe.c	\
			basic_client/basic_client.c	\
			basic_server/basic_server.c

## Obj Src
OBJ_COM= $(SRC_COM:.c=.o)

##OTHER FLAGS
INCLUDE=-I../object -I../list -I../myregex -I../mystring -I../utils

## Rules
all: $(EXEC_COM)

re: fclean
	@echo -e "--------------------"
	@make --no-print-directory all

$(EXEC_COM): $(OBJ_COM)
	@ar	rc	$(EXEC_COM) $(OBJ_COM)
	@ranlib $(EXEC_COM)
	@echo -e "--------------------"
	@echo -e " $(YEL)$@$(RES)"
	@mv $(EXEC_COM) ../myteams/

clean:
	@rm -rf $(OBJ_COM)
	@echo -e "$(GREEN)$@$(RES): $(YEL)$(EXEC_COM)$(RES)"

fclean:
	@rm -rf $(OBJ_COM)
	@rm -rf $(EXEC_COM)
	@echo -e "$(GREEN)$@$(RES): $(YEL)$(EXEC_COM) $(RES)"

## Defaults Rules
%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS) $(INCLUDE)
	@echo -e "$(CYAN)[DONE] $(BLUE)$@$(RES)"

.PHONY: all clean fclean re
