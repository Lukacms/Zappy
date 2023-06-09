/*
** EPITECH PROJECT, 2023
** map
** File description:
** update_map
*/

#include <stdlib.h>
#include <zappy/server.h>
#include <zappy/server/map_utils.h>

static int find_stocks(map_t map, u_int ind)
{
    int stock = 0;

    for (u_int y = 0; y < map.size.y; y++)
        for (u_int x = 0; x < map.size.x; x++)
            stock += map.tiles[y][x].slots[ind].units;
    return stock;
}

int update_map(server_t *server)
{
    int tmp = 0;
    int stocks[INVENTORY_SLOTS] = {0};

    if (!server)
        return FAILURE;
    for (u_int i = 0; i < INVENTORY_SLOTS; i++)
        stocks[i] = server->map.init_stock[i] - find_stocks(server->map, i);
    while (has_stock_left(stocks)) {
        tmp = rand() % (INVENTORY_SLOTS + 1);
        server->map
            .tiles[rand() % server->map.size.y][rand() % server->map.size.x]
            .slots[tmp]
            .units += stock(server->map.size, DENSITY_INVENTORY[tmp],
                            &(server->map.init_stock[tmp]));
    }
    return SUCCESS;
}