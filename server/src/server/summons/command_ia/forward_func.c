/*
** EPITECH PROJECT, 2023
** forward_func
** File description:
** zappy
*/

#include <stdio.h>
#include <zappy/server.h>
#include <zappy/server/clock/utils.h>
#include <zappy/server/utils.h>

int forward_north(server_t *server, client_node_t *client)
{
    if (client->stats.pos.x > 0)
        client->stats.pos.x -= 1;
    else
        client->stats.pos.x = (server->map.size.x - 1);
    return 0;
}

int forward_south(server_t *server, client_node_t *client)
{
    if (client->stats.pos.x < (server->map.size.x - 1))
        client->stats.pos.x += 1;
    else
        client->stats.pos.x = 0;
    return 0;
}

int forward_east(server_t *server, client_node_t *client)
{
    if (client->stats.pos.y < (server->map.size.y - 1))
        client->stats.pos.y += 1;
    else
        client->stats.pos.y = 0;
    return 0;
}

int forward_west(server_t *server, client_node_t *client)
{
    if (client->stats.pos.y > 0)
        client->stats.pos.y -= 1;
    else
        client->stats.pos.y = (server->map.size.y - 1);
    return 0;
}

int forward_func(server_t *server, char *args[], client_node_t *client)
{
    if (!server || !client)
        return FAILURE;
    if (!args || array_len(args) != 2)
        return set_error(client->cfd, INVALID_ACTION, false);
    switch (client->stats.orientation) {
    case NORTH: forward_north(server, client); break;
    case SOUTH: forward_south(server, client); break;
    case EAST: forward_east(server, client); break;
    case WEST: forward_west(server, client); break;
    }
    dprintf(client->cfd, "ok\n");
    add_ticks_occupied(client, RESTRAINT_FORWARD, server);
    return SUCCESS;
}
