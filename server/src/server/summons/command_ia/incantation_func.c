/*
** EPITECH PROJECT, 2023
** incantation_func
** File description:
** zappy
*/

#include "zappy/server/client.h"
#include "zappy/server/infos.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <zappy/server.h>
#include <zappy/server/clock/utils.h>
#include <zappy/server/summon/infos.h>
#include <zappy/server/summon/utils.h>
#include <zappy/server/utils.h>

static const char *INCATATION_MENDATORY[] = {"1100000", "2111000", "2201020",
                                             "4112010", "4121300", "6123010",
                                             "6222221"};

static bool check_mendatory_ressources(server_t *server, int x, int y,
                                       int level)
{
    if ((INCATATION_MENDATORY[level - 1][1] - CHAR_INT) <=
            server->map.tiles[x][y].slots[1].units &&
        (INCATATION_MENDATORY[level - 1][2] - CHAR_INT) <=
            server->map.tiles[x][y].slots[2].units &&
        (INCATATION_MENDATORY[level - 1][3] - CHAR_INT) <=
            server->map.tiles[x][y].slots[3].units &&
        (INCATATION_MENDATORY[level - 1][4] - CHAR_INT) <=
            server->map.tiles[x][y].slots[4].units &&
        (INCATATION_MENDATORY[level - 1][5] - CHAR_INT) <=
            server->map.tiles[x][y].slots[5].units &&
        (INCATATION_MENDATORY[level - 1][6] - CHAR_INT) <=
            server->map.tiles[x][y].slots[6].units)
        return true;
    return false;
}

static bool loop_clients_level_up(server_t *server, client_node_t *client)
{
    int nb_player_wlevelup = 0;
    client_node_t *tmp = NULL;
    char **cli_in_tile =
        server->map.tiles[client->stats.pos.x][client->stats.pos.y]
            .players_uuid;

    for (int i = 0; cli_in_tile[i] != NULL; i += 1) {
        tmp = find_client_by_uuid(cli_in_tile[i], server);
        if (tmp->stats.level == client->stats.level)
            nb_player_wlevelup += 1;
    }
    if (nb_player_wlevelup >=
        (INCATATION_MENDATORY[client->stats.level - 1][0] - CHAR_INT))
        return true;
    return false;
}

static void consuption_incantation(server_t *server, int x, int y, int level)
{
    server->map.tiles[x][y].slots[1].units -=
        (INCATATION_MENDATORY[level - 1][1] - CHAR_INT);
    server->map.tiles[x][y].slots[2].units -=
        (INCATATION_MENDATORY[level - 1][2] - CHAR_INT);
    server->map.tiles[x][y].slots[3].units -=
        (INCATATION_MENDATORY[level - 1][3] - CHAR_INT);
    server->map.tiles[x][y].slots[4].units -=
        (INCATATION_MENDATORY[level - 1][4] - CHAR_INT);
    server->map.tiles[x][y].slots[5].units -=
        (INCATATION_MENDATORY[level - 1][5] - CHAR_INT);
    server->map.tiles[x][y].slots[6].units -=
        (INCATATION_MENDATORY[level - 1][6] - CHAR_INT);
}

static void in_incantation(server_t *server, client_node_t *client)
{
    client_node_t *tmp = NULL;
    int idx = (INCATATION_MENDATORY[client->stats.level - 1][0] - CHAR_INT);
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
    if (check_mendatory_ressources(server, client->stats.pos.x,
                                   client->stats.pos.y,
                                   client->stats.level) == true &&
        loop_clients_level_up(server, client) == true) {
        consuption_incantation(server, client->stats.pos.x, client->stats.pos.y,
                               client->stats.level);
        in_incantation(server, client);
        add_ticks_occupied(client, RESTRAINT_INCANTATION, server);
    }
    return set_error(client->cfd, INVALID_ACTION, false);
}
