##
## EPITECH PROJECT, 2023
## Zappy/server/Makefile
## File description:
## Makefile
##

SRC	=	src/launch.c	\

SRC_MAIN	=	src/main.c

OBJ	=	$(SRC:.c=.o) $(SRC_MAIN:.c=.o)

SRC_TESTS	=	tests/redirect.c	\
				tests/template.c	\

OBJ_TESTS	=	$(SRC:.c=.o)  $(SRC_TESTS:.c=.o)

NAME	=	zappy_server

NAME_TESTS	=	unit_tests

override CFLAGS	=	-W -Wall -Wextra -Wpedantic

override CPPFLAGS	=	-I./include/

override LDLIBS	=	-lcriterion -lgcov

all:	../$(NAME)
.PHONY:	all

../$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ)
	mv $(NAME) ..

debug: fclean
debug: CFLAGS += -g
debug: ../$(NAME)
.PHONY:	debug

clean:
	@rm -f $(OBJ) $(OBJ_TESTS)
	@find -name "*.gcno" -delete
	@find -name "*.gcda" -delete
.PHONY:	clean

fclean:	clean
	@rm -f ../$(NAME)
	@rm -f $(NAME_TESTS)
.PHONY:	fclean

tests_run::	CPPFLAGS	+=	--coverage
tests_run::	CFLAGS	+=	-fprofile-arcs -ftest-coverage
tests_run::	fclean $(OBJ_TESTS)
	gcc -o $(NAME_TESTS) $(OBJ_TESTS) $(LDLIBS)
	-./$(NAME_TESTS)
tests_run:: coverage
.PHONY:	tests_run

coverage:
	gcovr --exclude tests
	gcovr --exclude tests --branches
.PHONY:	coverage

re::	fclean
re::	all
.PHONY:	re
