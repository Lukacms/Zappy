/*
** EPITECH PROJECT, 2023
** left_func
** File description:
** zappy
*/

#include <stdio.h>
#include <zappy/server.h>
#include <zappy/server/infos.h>

int left_func(server_t __attribute__((unused)) * server,
              char __attribute__((unused)) * args[], client_node_t *client)
{
    switch (client->stats.orientation) {
    case NORTH:
        client->stats.orientation = WEST;
        dprintf(client->cfd, "ok\n");
        return SUCCESS;
    case SOUTH:
        client->stats.orientation = EAST;
        dprintf(client->cfd, "ok\n");
        return 0;
    case EAST:
        client->stats.orientation = NORTH;
        dprintf(client->cfd, "ok\n");
        return 0;
    case WEST:
        client->stats.orientation = SOUTH;
        dprintf(client->cfd, "ok\n");
        return 0;
        break;
    }
    return 1;
}
