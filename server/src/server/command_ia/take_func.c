/*
** EPITECH PROJECT, 2023
** take_func
** File description:
** zappy
*/

#include <zappy/server/utils.h>

static const char *RESOURCES_INVENTORY[INVENTORY_SLOTS] = {
    "food", "linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"};

int take_func(server_t *server, char *args[], client_node_t *client)
{
    if (!args || !args[0] || !args[1] || args[2]) {
        dprintf(client->cfd, "ko");
        return 1;
    }
    for (int i = 0; i < INVENTORY_SLOTS; i += 1) {
        if (server->map.inventory[client->stats.pos.x][client->stats.pos.y][i]
                    .units != 0 &&
            strcmp(RESOURCES_INVENTORY[i], args[1]) == 0) {
            client->stats.inventory[i].units +=
                server->map
                    .inventory[client->stats.pos.x][client->stats.pos.y][i]
                    .units;
            server->map.inventory[client->stats.pos.x][client->stats.pos.y][i]
                .units = 0;
            send_toall_guicli(server, "pgt %i %i\n", client->uuid,
                              client->stats.inventory[i].resource);
            dprintf(client->cfd, "ok");
            return 0;
        }
    }
    dprintf(client->cfd, "ko");
    return 1;
}
