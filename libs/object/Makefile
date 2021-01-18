##
# EPITECH PROJECT, 2018
# makefile
# File description:
# make things
##

# COLOR
REDDARK	=	\033[31;2m
RED		=	\033[31;1m
GREEN	=	\033[32;1m
YEL		=	\033[33;1m
BLUE	=	\033[34;1m
PINK	=	\033[35;1m
CYAN	=	\033[36;1m
RES		= 	\033[0m

SRC		=	function.c
OBJ		=	$(SRC:.c=.o)
NAME	=	libobject.a
CFLAGS	= 	-g

%.o:	%.c
	@gcc $(CFLAGS) -o $@ -c $<
	@echo -e "$(CYAN)[DONE] $(BLUE)$@$(RES)"

all: $(NAME)

$(NAME):	$(OBJ)
	@ar	rc	$(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo -e "--------------------"
	@mv $(NAME) ../myteams/
	@echo -e "$(YEL)$@$(RES)"

clean:
	@rm -rf $(OBJ)
	@echo -e "$(GREEN)$@$(RES): $(YEL)$(NAME) $(RES)"

fclean:	clean
		@rm -rf ../myteams/$(NAME)
		@echo -e "$(GREEN)$@$(RES): $(YEL)$(NAME) $(RES)"

re:	fclean	all
