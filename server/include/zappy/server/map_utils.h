/*
** EPITECH PROJECT, 2023
** server
** File description:
** map_utils
*/

#pragma once

#include <zappy/server/infos.h>

#define DENSITY_FOOD 0.5
#define DENSITY_LINEMATE 0.3
#define DENSITY_DERAUMERE 0.15
#define DENSITY_SIBUR 0.1
#define DENSITY_MENDIANE 0.1
#define DENSITY_PHIRAS 0.08
#define DENSITY_THYSTAME 0.05

int generate_map(server_t *server);
int update_map(server_t *server);
