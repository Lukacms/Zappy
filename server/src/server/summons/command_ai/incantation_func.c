/*
** EPITECH PROJECT, 2023
** incantation_func
** File description:
** zappy
*/

#include <stdio.h>
#include <zappy/server.h>
#include <zappy/server/client.h>
#include <zappy/server/clock/utils.h>
#include <zappy/server/utils.h>

static const char *INCANTATION_MANDATORY[] = {
    "1100000", "2111000", "2201020", "4112010", "4121300", "6123010", "6222221",
};

static bool mandatory_resources(server_t *server, vector2i_t pos, int lvl)
{
    tile_t tile = server->map.tiles[pos.y][pos.x];

    return (
        (INCANTATION_MANDATORY[lvl - 1][1] - CHAR_INT) <= tile.slots[1].units &&
        (INCANTATION_MANDATORY[lvl - 1][2] - CHAR_INT) <= tile.slots[2].units &&
        (INCANTATION_MANDATORY[lvl - 1][3] - CHAR_INT) <= tile.slots[3].units &&
        (INCANTATION_MANDATORY[lvl - 1][4] - CHAR_INT) <= tile.slots[4].units &&
        (INCANTATION_MANDATORY[lvl - 1][5] - CHAR_INT) <= tile.slots[5].units &&
        (INCANTATION_MANDATORY[lvl - 1][6] - CHAR_INT) <= tile.slots[6].units);
}

static bool loop_clients_level_up(server_t *server, client_node_t *client)
{
    int players_able = 0;
    client_node_t *tmp = NULL;
    char **cli_in_tile =
        server->map.tiles[client->stats.pos.x][client->stats.pos.y]
            .players_uuid;

    for (int i = 0; cli_in_tile[i] != NULL; i += 1) {
        tmp = find_client_by_uuid(cli_in_tile[i], server);
        if (tmp->stats.level == client->stats.level)
            players_able += 1;
    }
    return players_able >=
        (INCANTATION_MANDATORY[client->stats.level - 1][0] - CHAR_INT);
}

static void in_incantation(server_t *server, client_node_t *client)
{
    client_node_t *tmp = NULL;
    int idx = (INCANTATION_MANDATORY[client->stats.level - 1][0] - CHAR_INT);
    char **cli_in_tile =
        server->map.tiles[client->stats.pos.x][client->stats.pos.y]
            .players_uuid;

    for (int i = 0; cli_in_tile[i] != NULL && idx > 0; i += 1) {
        tmp = find_client_by_uuid(cli_in_tile[i], server);
        if (tmp->stats.level == client->stats.level) {
            tmp->stats.action.type = INCANTATION;
            idx -= 1;
        }
    }
}

int incantation_func(server_t *server, char *args[], client_node_t *client)
{
    if (!server || !client)
        return FAILURE;
    if (!args || array_len(args) != 1)
        return set_error(client->cfd, INVALID_ACTION, false);
    if (mandatory_resources(server, client->stats.pos, client->stats.level) &&
        loop_clients_level_up(server, client)) {
        add_ticks_occupied(client, RESTRAINT_INCANTATION, server);
        in_incantation(server, client);
    }
    return set_error(client->cfd, INVALID_ACTION, false);
}
