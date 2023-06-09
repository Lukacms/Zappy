##
## EPITECH PROJECT, 2023
## Zappy/server/Makefile
## File description:
## Makefile
##

SRC	=	src/launch.c	\
		src/utils/strisnum.c	\
		src/utils/set_error.c	\
		src/utils/print_help.c	\
		src/utils/delete_from_array.c	\
		src/utils/char_in_str.c	\
		src/utils/generate_uuid.c	\
		src/utils/strndup_quotes.c	\
		src/utils/free_array.c	\
		src/utils/array_len.c	\
		src/utils/realloc_array.c	\
		src/utils/str_to_word_array.c	\
		src/map/generate_map.c	\
		src/map/change_player_pos.c	\
		src/map/utils_map.c	\
		src/map/update_map.c	\
		src/map/delete_eggs_from_tile.c	\
		src/load/options/f_handler.c	\
		src/load/options/x_handler.c	\
		src/load/options/h_handler.c	\
		src/load/options/c_handler.c	\
		src/load/options/y_handler.c	\
		src/load/options/n_handler.c	\
		src/load/options/p_handler.c	\
		src/load/parse_args.c	\
		src/load/update_server_with_args.c	\
		src/load/create_server.c	\
		src/destroy/destroy_server.c	\
		src/destroy/destroy_teams.c	\
		src/destroy/destroy_clients.c	\
		src/server/eggs/create_eggs.c	\
		src/server/eggs/from_egg_to_player.c	\
		src/server/eggs/find_egg_by_nb.c	\
		src/server/eggs/add_egg_to_team.c	\
		src/server/eggs/delete_egg_from_team.c	\
		src/server/summons/command_ia/dprint_tile.c	\
		src/server/summons/command_ia/inventory_func.c	\
		src/server/summons/command_ia/look_func.c	\
		src/server/summons/command_ia/set_func.c	\
		src/server/summons/command_ia/left_func.c	\
		src/server/summons/command_ia/right_func.c	\
		src/server/summons/command_ia/take_func.c	\
		src/server/summons/command_ia/incantation_func.c	\
		src/server/summons/command_ia/eject_func.c	\
		src/server/summons/command_ia/connect_nbr_func.c	\
		src/server/summons/command_ia/forward_func.c	\
		src/server/summons/add_summon.c	\
		src/server/summons/handle_summon.c	\
		src/server/summons/pop_summon.c	\
		src/server/summons/serv_cli/client_command.c	\
		src/server/summons/serv_cli/send_toall_guicli.c	\
		src/server/summons/command_gui/gui_connect_func.c	\
		src/server/summons/command_gui/sgt_func.c	\
		src/server/summons/command_gui/plv_func.c	\
		src/server/summons/command_gui/ppo_func.c	\
		src/server/summons/command_gui/bct_func.c	\
		src/server/summons/command_gui/sst_func.c	\
		src/server/summons/command_gui/tna_func.c	\
		src/server/summons/command_gui/pin_func.c	\
		src/server/summons/command_gui/mct_func.c	\
		src/server/summons/command_gui/msz_func.c	\
		src/server/summons/get_summon.c	\
		src/server/clock/gettickselapsed.c	\
		src/server/clock/add_ticks_occupied.c	\
		src/server/clock/update_ticks.c	\
		src/server/server_loop.c	\
		src/server/handle_signal.c	\
		src/server/client/delete_client_node.c	\
		src/server/client/delete_client_from_team.c	\
		src/server/client/connect_new_client.c	\
		src/server/client/add_client_node.c	\
		src/server/client/find_team.c	\
		src/server/client/find_client.c	\
		src/server/client/add_client_to_team.c	\

SRC_MAIN	=	src/main.c

OBJ	=	$(SRC:.c=.o) $(SRC_MAIN:.c=.o)

SRC_TESTS	=	tests/redirect.c	\
				tests/template.c	\
				tests/load/tests_arguments.c	\
				tests/load/test_arguments_ptr.c	\
				tests/tests_launch.c	\
				tests/load/tests_create_server.c	\
				tests/tests_utils.c	\

OBJ_TESTS	=	$(SRC:.c=.o)  $(SRC_TESTS:.c=.o)

NAME	=	zappy_server

NAME_TESTS	=	unit_tests

override CFLAGS	=	-W -Wall -Wextra -Wpedantic

override CPPFLAGS	=	-I./include/

override LDLIBS	=	-luuid -lm

all:	../$(NAME)
.PHONY:	all

../$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDLIBS)
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
tests_run::	LDLIBS += -lcriterion -lgcov
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
