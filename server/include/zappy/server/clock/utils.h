/*
** EPITECH PROJECT, 2023
** clock
** File description:
** utils
*/

#pragma once

#include <zappy/server/infos.h>

int gettickselapsed(zappy_clock_t *clock);
void update_ticks_clients(server_t *server);
