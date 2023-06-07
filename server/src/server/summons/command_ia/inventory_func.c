/*
** EPITECH PROJECT, 2023
** inventory_func
** File description:
** zappy
*/

#include <stdio.h>
#include <zappy/server.h>
#include <zappy/server/clock/utils.h>
#include <zappy/server/infos.h>

int inventory_func(server_t *server, char *args[], client_node_t *client)
{
    if (!args || !args[0] || args[1] || !server) {
        dprintf(client->cfd, "ko");
        return FAILURE;
    }
    dprintf(client->cfd, "[food %li, linemate %li, deraumere %li, sibur %li, \
            mendiane %li, phiras %li, thystame %li]",
            client->stats.inventory[FOOD].units,
            client->stats.inventory[LINEMATE].units,
            client->stats.inventory[DERAUMERE].units,
            client->stats.inventory[SIBUR].units,
            client->stats.inventory[MENDIANE].units,
            client->stats.inventory[PHIRAS].units,
            client->stats.inventory[THYSTAME].units);
    add_ticks_occupied(client, RESTRAINT_INVENTORY, server);
    return SUCCESS;
}
