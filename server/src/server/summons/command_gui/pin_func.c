/*
** EPITECH PROJECT, 2023
** pin_func
** File description:
** zappy
*/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <zappy/server.h>
#include <zappy/server/utils.h>

int pin_func(server_t *server, char *args[], client_node_t *client)
{
    client_node_t *tmp = server->clients.head;

    if (!args || array_len(args) != 3)
        return FAILURE;
    for (u_int ind = 0; ind < server->clients.length; ind++) {
        if (strcmp(args[1], tmp->uuid) == 0) {
            dprintf(client->cfd, "pin %s %zu %zu %li %li %li %li %li %li %li\n",
                    tmp->uuid, tmp->stats.pos.x, tmp->stats.pos.y,
                    tmp->stats.inventory[FOOD].units,
                    tmp->stats.inventory[LINEMATE].units,
                    tmp->stats.inventory[DERAUMERE].units,
                    tmp->stats.inventory[SIBUR].units,
                    tmp->stats.inventory[MENDIANE].units,
                    tmp->stats.inventory[PHIRAS].units,
                    tmp->stats.inventory[THYSTAME].units);
            return SUCCESS;
        }
        tmp = tmp->next;
    }
    return FAILURE;
}
