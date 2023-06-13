/*
** EPITECH PROJECT, 2023
** incantation_func
** File description:
** zappy
*/

#include <stdio.h>
#include <string.h>
#include <zappy/server.h>
#include <zappy/server/clock/utils.h>
#include <zappy/server/summon/infos.h>
#include <zappy/server/summon/utils.h>
#include <zappy/server/utils.h>

int incantation_func(server_t *server, char *args[], client_node_t *client)
{
    if (!server || !client)
        return FAILURE;
    if (!args || array_len(args) != 3)
        return set_error(client->cfd, INVALID_ACTION, false);
    for (int i = 0; i < INVENTORY_SLOTS; i += 1) {
        if (client->stats.inventory[i].units != 0 &&
            strcmp(RESOURCES_INVENTORY[i], args[1]) == 0) {
            server->map.tiles[client->stats.pos.x][client->stats.pos.y]
                .slots[i].units += 1;
            client->stats.inventory[i].units -= 1;
            send_toall_guicli(server, DISPATCH_PDR, client->cfd,
                            client->stats.inventory[i].resource);
            dprintf(client->cfd, BASIC_VALID);
            return SUCCESS;
        }
    }
    add_ticks_occupied(client, RESTRAINT_INCANTATION, server);
    return set_error(client->cfd, INVALID_ACTION, false);
}
