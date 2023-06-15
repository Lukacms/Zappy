/*
** EPITECH PROJECT, 2023
** bct_func
** File description:
** zappy
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zappy/server.h>
#include <zappy/server/infos.h>
#include <zappy/server/utils.h>

int bct_func(server_t *server, char *args[], client_node_t *client)
{
    int pos_x = 0;
    int pos_y = 0;

    if (!args || array_len(args) != 3 || !server || !client)
        return FAILURE;
    pos_x = atoi(args[1]);
    pos_y = atoi(args[2]);
    if (pos_x < 0 || !strisnum(args[1]) || pos_y < 0 || !strisnum(args[2]))
        return FAILURE;
    dprintf(client->cfd, DISPATCH_BCT, pos_x, pos_y,
            server->map.tiles[pos_x][pos_y].slots[FOOD].units,
            server->map.tiles[pos_x][pos_y].slots[LINEMATE].units,
            server->map.tiles[pos_x][pos_y].slots[DERAUMERE].units,
            server->map.tiles[pos_x][pos_y].slots[SIBUR].units,
            server->map.tiles[pos_x][pos_y].slots[MENDIANE].units,
            server->map.tiles[pos_x][pos_y].slots[PHIRAS].units,
            server->map.tiles[pos_x][pos_y].slots[THYSTAME].units);
    return SUCCESS;
}
