/*
** EPITECH PROJECT, 2023
** left_func
** File description:
** zappy
*/

#include <stdio.h>
#include <zappy/server.h>
#include <zappy/server/clock/utils.h>
#include <zappy/server/summon/utils.h>

static int set_client_orientation(server_t *server, client_node_t *client,
                                orientation_t orientation)
{
    client->stats.orientation = orientation;
    dprintf(client->cfd, BASIC_VALID);
    add_ticks_occupied(client, RESTRAINT_LEFT, server);
    send_toall_guicli(server, DISPATCH_PPO, client->cfd, client->stats.pos.x,
                    client->stats.pos.y, client->stats.orientation);
    return SUCCESS;
}

int right_func(server_t *server, char __attribute__((unused)) * args[],
            client_node_t *client)
{
    if (!server || !client)
        return FAILURE;
    switch (client->stats.orientation) {
        case NORTH: return set_client_orientation(server, client, EAST);
        case SOUTH: return set_client_orientation(server, client, WEST);
        case EAST: return set_client_orientation(server, client, SOUTH);
        case WEST: return set_client_orientation(server, client, NORTH); break;
    }
    return FAILURE;
}
