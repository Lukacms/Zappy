/*
** EPITECH PROJECT, 2023
** clock
** File description:
** utils
*/

#pragma once

#include <zappy/server/infos.h>

int gettickselapsed(zappy_clock_t *clock);
void update_ticks(server_t *server);
int add_ticks_occupied(client_node_t *client, int restraint, server_t *server);
