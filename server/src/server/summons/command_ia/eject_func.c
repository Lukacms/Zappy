/*
** EPITECH PROJECT, 2023
** eject_func
** File description:
** zappy
*/

#include <stdbool.h>
#include <stdio.h>
#include <zappy/server.h>
#include <zappy/server/summon/utils.h>
#include <zappy/server/utils.h>

static bool same_tile(vector2i_t a, vector2i_t b)
{
    if (a.x == b.x && a.y == b.y)
        return true;
    return false;
}

int eject_func(server_t *server, char *args[], client_node_t *client)
{
    client_node_t *tmp = NULL;

    if (!args || array_len(args) != 2 || !server ||
        !(tmp = server->clients.head))
        return set_error(client->cfd, "ko", false);
    for (unsigned int ind = 0; ind < server->clients.length; tmp = tmp->next) {
        if (same_tile(tmp->stats.pos, client->stats.pos) == true &&
            tmp->uuid != client->uuid) {
            dprintf(tmp->cfd, "eject: %i\n", client->stats.orientation + 1);
            switch (client->stats.orientation) {
            case NORTH: forward_north(server, tmp); break;
            case SOUTH: forward_south(server, tmp); break;
            case EAST: forward_east(server, tmp); break;
            case WEST: forward_west(server, tmp); break;
            }
        }
    }
    return SUCCESS;
}
