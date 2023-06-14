/*
** EPITECH PROJECT, 2023
** command_ai
** File description:
** check_incantation_end
*/

#include <zappy/server.h>
#include <zappy/server/summon/utils.h>

static const incantation_t REQUIREMENTS[] = {
    {.required_lvl = 1,
     .nb_players = 1,
     .resources = {{LINEMATE, 1},
                   {DERAUMERE, 0},
                   {SIBUR, 0},
                   {MENDIANE, 0},
                   {PHIRAS, 0},
                   {THYSTAME, 0}}},
    {.required_lvl = 2,
     .nb_players = 2,
     .resources = {{LINEMATE, 1},
                   {DERAUMERE, 1},
                   {SIBUR, 1},
                   {MENDIANE, 0},
                   {PHIRAS, 0},
                   {THYSTAME, 0}}},
    {.required_lvl = 3,
     .nb_players = 2,
     .resources = {{LINEMATE, 2},
                   {DERAUMERE, 0},
                   {SIBUR, 1},
                   {MENDIANE, 0},
                   {PHIRAS, 2},
                   {THYSTAME, 0}}},
    {.required_lvl = 4,
     .nb_players = 4,
     .resources = {{LINEMATE, 1},
                   {DERAUMERE, 1},
                   {SIBUR, 2},
                   {MENDIANE, 0},
                   {PHIRAS, 1},
                   {THYSTAME, 0}}},
    {.required_lvl = 5,
     .nb_players = 4,
     .resources = {{LINEMATE, 1},
                   {DERAUMERE, 2},
                   {SIBUR, 1},
                   {MENDIANE, 3},
                   {PHIRAS, 0},
                   {THYSTAME, 0}}},
    {.required_lvl = 6,
     .nb_players = 6,
     .resources = {{LINEMATE, 1},
                   {DERAUMERE, 2},
                   {SIBUR, 3},
                   {MENDIANE, 0},
                   {PHIRAS, 1},
                   {THYSTAME, 0}}},
    {.required_lvl = 7,
     .nb_players = 6,
     .resources = {{LINEMATE, 2},
                   {DERAUMERE, 2},
                   {SIBUR, 2},
                   {MENDIANE, 2},
                   {PHIRAS, 2},
                   {THYSTAME, 2}}},
    {.required_lvl = -1},
};

int check_incantation_end(server_t *server, client_node_t *client)
{
    if (!server || !client)
        return FAILURE;
    return SUCCESS;
}
