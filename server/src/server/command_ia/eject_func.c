/*
** EPITECH PROJECT, 2023
** eject_func
** File description:
** zappy
*/

#include "zappy/config/arguments.h"
#include <stdbool.h>
#include <zappy/server/utils.h>

static bool same_tile(vector2i_t a, vector2i_t b)
{
    if (a.x == b.x && a.y == b.y)
        return true;
    return false;
}

int eject_func(server_t *server, char *args[], client_node_t *client)
{
    client_node_t *tmp = server->clients.head;

    if (!args || !args[0] || args[1] || !server) {
        dprintf(client->cfd, "ko");
        return 1;
    }
    while (tmp) {
        if (same_tile(tmp->stats.pos, client->stats.pos) == true &&
            tmp->uuid != client->uuid) {
            dprintf(tmp->cfd, "eject: %i\n", client->stats.orientation + 1);
            switch (client->stats.orientation) {
            case NORTH: forward_north(server, tmp);
            case SOUTH: forward_south(server, tmp);
            case EAST: forward_east(server, tmp);
            case WEST: forward_west(server, tmp); break;
            }
        }
    }
    return 0;
}
