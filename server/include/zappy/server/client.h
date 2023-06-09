/*
** EPITECH PROJECT, 2023
** server
** File description:
** client
*/

#pragma once

#include <zappy/server/infos.h>

#define INIT_FOOD 10

// exclusively related to client
int add_client_node(client_node_t *new_node, server_t *server);
client_node_t *find_client_by_uuid(const char *uuid, server_t *server);
client_node_t *find_client_by_fd(int fd, server_t *server);
void delete_client_by_fd(int fd, server_t *server);
void delete_client_by_uuid(const char *uuid, server_t *server);
int connect_new_client(server_t *server);

// team related
int add_client_to_team(client_node_t *client, server_t *server,
                       const char *team);
team_t *find_team_by_name(const char *name, server_t *server);
team_t *find_team_by_uuid(const char *uuid, server_t *server);
void delete_client_from_team(client_node_t *client, server_t *server);

// egg related
int create_eggs(server_t *server);
int from_egg_to_player(client_node_t *client, team_t **team);
int add_egg_to_team(client_node_t *client, server_t *server);
int delete_egg_from_team(server_t *server, int id);
egg_t **find_egg_by_nb(server_t *server, int nb);
