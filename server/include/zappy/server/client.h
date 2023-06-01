/*
** EPITECH PROJECT, 2023
** server
** File description:
** client
*/

#pragma once

#include <zappy/server.h>
#include <zappy/server/infos.h>

int add_client_node(client_node_t *new_node, server_t *server);
client_node_t *find_client_by_uuid(const char *uuid, server_t *server);
client_node_t *find_client_by_fd(int fd, server_t *server);
void delete_client_by_fd(int fd, server_t *server);
void delete_client_by_uuid(const char *uuid, server_t *server);
int connect_new_client(server_t *server);
