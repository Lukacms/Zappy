/*
** EPITECH PROJECT, 2023
** eject_func
** File description:
** zappy
*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <zappy/server.h>
#include <zappy/server/clock/utils.h>
#include <zappy/server/map_utils.h>
#include <zappy/server/summon/utils.h>
#include <zappy/server/utils.h>

bool same_tile(vector2i_t a, vector2i_t b)
{
    return (a.x == b.x && a.y == b.y);
}

static void check_orientation(server_t *server, client_node_t *tmp)
{
    switch (tmp->stats.orientation) {
        case NORTH: forward_north(server, tmp); break;
        case SOUTH: forward_south(server, tmp); break;
        case EAST: forward_east(server, tmp); break;
        case WEST: forward_west(server, tmp); break;
    }
}

int eject_func(server_t *server, char *args[], client_node_t *client)
{
    client_node_t *tmp = NULL;

    if (!args || array_len(args) != 2 || !server ||
        !(tmp = server->clients.head))
        return set_error(client->cfd, INVALID_ACTION, false);
    for (unsigned int ind = 0; ind < server->clients.length; ind++) {
        if (same_tile(tmp->stats.pos, client->stats.pos) &&
            strcmp(tmp->uuid, client->uuid) != SUCCESS) {
            dprintf(tmp->cfd, AI_EJECT, client->stats.orientation + 1);
            check_orientation(server, tmp);
        }
        tmp = tmp->next;
    }
    delete_eggs_from_tile(server, client->stats.pos);
    add_ticks_occupied(client, RESTRAINT_EJECT, server);
    return SUCCESS;
}
