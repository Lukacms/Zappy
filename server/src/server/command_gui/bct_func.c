/*
** EPITECH PROJECT, 2023
** bct_func
** File description:
** zappy
*/

#include <zappy/server/infos.h>

int bct_func(server_t *server, char *args[], client_node_t *client)
{
    int pos_x = 0;
    int pos_y = 0;

    if (!args || !args[0] || !args[1] || !args[2] || args[3])
        return 1;
    pos_x = atoi(args[1]);
    pos_y = atoi(args[2]);
    if ((pos_x == 0 && (strlen(args[1]) != 1 || args[1][0] != '0')) ||
        (pos_y == 0 && (strlen(args[2]) != 1 || args[2][0] != '0')))
        return 1;
    dprintf(client->cfd, "bct %i %i %li %li %li %li %li %li %li\n", pos_x, pos_y,
            server->map.inventory[pos_x][pos_y][FOOD].units,
            server->map.inventory[pos_x][pos_y][LINEMATE].units,
            server->map.inventory[pos_x][pos_y][DERAUMERE].units,
            server->map.inventory[pos_x][pos_y][SIBUR].units,
            server->map.inventory[pos_x][pos_y][MENDIANE].units,
            server->map.inventory[pos_x][pos_y][PHIRAS].units,
            server->map.inventory[pos_x][pos_y][THYSTAME].units);
    return 0;
}
