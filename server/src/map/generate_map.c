/*
** EPITECH PROJECT, 2023
** map
** File description:
** generate_map
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <zappy/server.h>
#include <zappy/server/map_utils.h>

static void randomize_map(server_t *server)
{
    int tmp = 0;
    int init_stock[INVENTORY_SLOTS] = {0};

    for (u_int i = 0; i < INVENTORY_SLOTS; i++) {
        server->map.init_stock[i] =
            server->map.size.x * server->map.size.y * DENSITY_INVENTORY[i];
        init_stock[i] = server->map.init_stock[i];
    }
    while (has_stock_left(init_stock)) {
        tmp = rand() % (INVENTORY_SLOTS + 1);
        server->map
            .tiles[rand() % server->map.size.y][rand() % server->map.size.x]
            .slots[tmp]
            .units +=
            stock(server->map.size, DENSITY_INVENTORY[tmp], &(init_stock[tmp]));
    }
}

int generate_map(server_t *server)
{
    if (!server)
        return FAILURE;
    server->map.tiles = malloc(sizeof(tile_t *) * (server->map.size.y + 1));
    if (!server->map.tiles)
        return FAILURE;
    server->map.tiles[server->map.size.x] = NULL;
    for (unsigned int i = 0; i < server->map.size.y; i++) {
        server->map.tiles[i] = malloc(sizeof(tile_t) * server->map.size.y);
        if (!server->map.tiles[i])
            return FAILURE;
    }
    randomize_map(server);
    return SUCCESS;
}
