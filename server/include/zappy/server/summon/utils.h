/*
** EPITECH PROJECT, 2023
** server
** File description:
** summons
*/

#pragma once

#include <zappy/server/infos.h>

int add_summon(char *summon, client_node_t *client);
char *pop_summon(client_node_t *client);
int get_summon(server_t *server, client_node_t *client);
int handle_summon(server_t *server, int cfd);
