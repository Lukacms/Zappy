/*
** EPITECH PROJECT, 2023
** mct_func
** File description:
** zappy
*/

#include <zappy/server/infos.h>

int mct_func(server_t *server, char *args[], client_node_t *client)
{
    for (int pos_x = 0; server->map.inventory[pos_x] != NULL; pos_x += 1) {
        for (int pos_y = 0; server->map.inventory[pos_x][pos_y] != NULL;
             pos_y += 1) {
            dprintf(
                client->cfd, "bct %i %i %li %li %li %li %li %li %li\n", pos_x, pos_y,
                server->map.inventory[pos_x][pos_y][FOOD].units,
                server->map.inventory[pos_x][pos_y][LINEMATE].units,
                server->map.inventory[pos_x][pos_y][DERAUMERE].units,
                server->map.inventory[pos_x][pos_y][SIBUR].units,
                server->map.inventory[pos_x][pos_y][MENDIANE].units,
                server->map.inventory[pos_x][pos_y][PHIRAS].units,
                server->map.inventory[pos_x][pos_y][THYSTAME].units);
        }
    }
    return 0;
}
