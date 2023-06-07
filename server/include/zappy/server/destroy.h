/*
** EPITECH PROJECT, 2023
** server
** File description:
** destroy
*/

#pragma once

#include <zappy/server/infos.h>

void destroy_server(server_t *server);
void destroy_clients(clients_t *clients);
void destroy_teams(team_t **teams);
