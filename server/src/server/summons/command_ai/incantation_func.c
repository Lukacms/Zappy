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
#include <zappy/server/summon/utils.h>
#include <zappy/server/utils.h>

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
            add_ticks_occupied(tmp, RESTRAINT_INCANTATION, server);
            tmp->stats.action.type = INCANTATION;
            dprintf(tmp->cfd, IN_INCANT);
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
