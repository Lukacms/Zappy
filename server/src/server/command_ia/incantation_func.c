/*
** EPITECH PROJECT, 2023
** incantation
** File description:
** zappy
*/

#include <zappy/server/utils.h>

static const char *RESOURCES_INVENTORY[INVENTORY_SLOTS] = {
    "food", "linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"};

int incantation(server_t *server, char *args[], client_node_t *client)
{
    if (!args || !args[0] || !args[1] || args[2]) {
        dprintf(client->cfd, "ko");
        return 1;
    }
    for (int i = 0; i < INVENTORY_SLOTS; i += 1) {
        if (client->stats.inventory[i].units != 0 &&
            strcmp(RESOURCES_INVENTORY[i], args[1]) == 0) {
            server->map.inventory[client->stats.pos.x][client->stats.pos.y][i]
                .units += 1;
            client->stats.inventory[i].units -= 1;
            send_toall_guicli(server, "pdr %i %i\n", client->uuid,
                              client->stats.inventory[i].resource);
            dprintf(client->cfd, "ok");
            return 0;
        }
    }
    dprintf(client->cfd, "ko");
    return 1;
}
