/*
** EPITECH PROJECT, 2023
** forward_func
** File description:
** zappy
*/

#include <zappy/server/infos.h>

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
    if (client->stats.pos.x <  (server->map.size.x - 1))
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
    if (!args || !args[0] || args[1]) {
        dprintf(client->cfd, "ko");
        return 1;
    }
    switch (client->stats.orientation) {
    case NORTH: forward_north(server, client);
    case SOUTH: forward_south(server, client);
    case EAST: forward_east(server, client);
    case WEST: forward_west(server, client);
    break;
    }
    dprintf(client->cfd, "ok\n");
    return 0;
}
