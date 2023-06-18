/*
** EPITECH PROJECT, 2023
** take_func
** File description:
** zappy
*/

#include <stdio.h>
#include <string.h>
#include <zappy/server.h>
#include <zappy/server/clock/utils.h>
#include <zappy/server/summon/utils.h>
#include <zappy/server/utils.h>

static void send_infos(server_t *server, client_node_t *client, int ind)
{
    char output[BUFFER_SIZE] = {0};

    sprintf(output, DISPATCH_PGT, client->cfd,
            client->stats.inventory[ind].resource);
    send_toall_guicli(server, output);
    dprintf(client->cfd, BASIC_VALID);
}

int take_func(server_t *server, char *args[], client_node_t *client)
{
    if (!server || client)
        return FAILURE;
    if (!args || array_len(args) != 2)
        return set_error(client->cfd, INVALID_ACTION, false);
    for (int i = 0; i < INVENTORY_SLOTS; i += 1) {
        if (server->map.tiles[client->stats.pos.x][client->stats.pos.y]
                    .slots[i]
                    .units != 0 &&
            strcmp(RESOURCES_INVENTORY[i], args[1]) == 0) {
            client->stats.inventory[i].units +=
                server->map.tiles[client->stats.pos.x][client->stats.pos.y]
                    .slots[i]
                    .units;
            server->map.tiles[client->stats.pos.x][client->stats.pos.y]
                .slots[i]
                .units = 0;
            send_infos(server, client, i);
            add_ticks_occupied(client, RESTRAINT_TAKE, server);
            return SUCCESS;
        }
    }
    return set_error(client->cfd, INVALID_ACTION, false);
}
