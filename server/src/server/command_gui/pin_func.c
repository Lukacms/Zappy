/*
** EPITECH PROJECT, 2023
** pin_func
** File description:
** zappy
*/

#include <zappy/server/infos.h>

int pin_func(server_t *server, char *args[], client_node_t *client)
{
    client_node_t *tmp = server->clients.head;

    if (!args || !args[0] || !args[1] || args[2])
        return 1;
    while (tmp) {
        if (strcmp(args[1], tmp->uuid) == 0) {
            dprintf(
                client->cfd, "pin %s %i %i %li %li %li %li %li %li %li\n", tmp->uuid,
                tmp->stats.pos.x, tmp->stats.pos.y,
                tmp->stats.inventory[FOOD].units,
                tmp->stats.inventory[LINEMATE].units,
                tmp->stats.inventory[DERAUMERE].units,
                tmp->stats.inventory[SIBUR].units,
                tmp->stats.inventory[MENDIANE].units,
                tmp->stats.inventory[PHIRAS].units,
                tmp->stats.inventory[THYSTAME].units);
            return 0;
        }
        tmp = tmp->next;
    }
    return 1;
}
