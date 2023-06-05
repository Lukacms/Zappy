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

static double DENSITY_INVENTORY[INVENTORY_SLOTS] = {
    DENSITY_FOOD,     DENSITY_LINEMATE, DENSITY_DERAUMERE, DENSITY_SIBUR,
    DENSITY_MENDIANE, DENSITY_PHIRAS,   DENSITY_THYSTAME,
};

static int stock(vector2i_t size, double density, int *stock_left)
{
    int div = ceil(size.x * size.y * density / (*stock_left));
    int res = 0;

    if (*stock_left <= 0)
        return 0;
    if (div > *stock_left)
        div = *stock_left;
    if (div <= 1)
        div = 2;
    res = rand() % div;
    (*stock_left) -= res;
    return res;
}

static bool has_stock_left(const int *stock)
{
    for (u_int i = 0; i < INVENTORY_SLOTS; i++)
        if (stock[i] > 0)
            return true;
    return false;
}

static void randomize_map(server_t *server)
{
    int total_stock[INVENTORY_SLOTS] = {0};
    int tmp = 0;

    for (u_int i = 0; i < INVENTORY_SLOTS; i++)
        total_stock[i] =
            server->map.size.x * server->map.size.y * DENSITY_INVENTORY[i];
    while (has_stock_left(total_stock)) {
        tmp = rand() % (INVENTORY_SLOTS + 1);
        server->map
            .tiles[rand() % server->map.size.y][rand() % server->map.size.x]
            .slots[tmp]
            .units += stock(server->map.size, DENSITY_INVENTORY[tmp],
                            &(total_stock[tmp]));
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
