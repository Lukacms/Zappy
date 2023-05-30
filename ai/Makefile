##
## EPITECH PROJECT, 2023
## zappy
## File description:
## Makefile
##

SRC		=	src/zappy_ai

NAME	=	zappy_ai

all:	$(NAME)

$(NAME):
	cp src/$(NAME) ../
	chmod +x ../$(NAME)

clean:
	@echo "project cleaning is in process [...]"

fclean:	clean
	$(RM) $(NAME)
	$(RM) ../$(NAME)

re:	fclean all

.PHONY: all clean fclean re
