/*
** EPITECH PROJECT, 2023
** server
** File description:
** client
*/

#pragma once

#include <zappy/server/infos.h>

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