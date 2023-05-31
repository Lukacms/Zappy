/*
** EPITECH PROJECT, 2023
** forward_func
** File description:
** zappy
*/

#include <zappy/server/infos.h>

static int forward_north(server_t *server, client_node_t *client)
{
    if (client->stats.pos.x > 0)
        client->stats.pos.x -= 1;
    else
        client->stats.pos.x = (server->map.size.x - 1);
    dprintf(client->cfd, "ok\n");
    return 0;
}

static int forward_south(server_t *server, client_node_t *client)
{
    if (client->stats.pos.x < server->map.size.x)
        client->stats.pos.x += 1;
    else
        client->stats.pos.x = 0;
    dprintf(client->cfd, "ok\n");
    return 0;
}

static int forward_east(server_t *server, client_node_t *client)
{
    if (client->stats.pos.y > 0)
        client->stats.pos.y -= 1;
    else
        client->stats.pos.y = (server->map.size.y - 1);
    dprintf(client->cfd, "ok\n");
    return 0;
}

static int forward_west(server_t *server, client_node_t *client)
{
    if (client->stats.pos.y < server->map.size.y)
        client->stats.pos.y += 1;
    else
        client->stats.pos.y = 0;
    dprintf(client->cfd, "ok\n");
    return 0;
}

int forward_func(server_t *server, char *args[], client_node_t *client)
{
    switch (client->stats.orientation) {
    case NORTH: return forward_north(server, client);
    case SOUTH: return forward_south(server, client);
    case EAST: return forward_east(server, client);
    case WEST: return forward_west(server, client);
    break;
    }
    return 1;
}
