/*
** EPITECH PROJECT, 2023
** dprint_tile
** File description:
** zappy
*/

#include <stddef.h>
#include <stdio.h>
#include <zappy/server/utils.h>

static size_t check_cord(size_t csize, size_t cord)
{
    size_t result = cord;

    if (cord > csize)
        result = cord - csize;
    return result;
}

void dprint_tile(map_t map, size_t cord_x, size_t cord_y, client_node_t *client)
{
    size_t idx_x = check_cord(map.size.x, cord_x);
    size_t idx_y = check_cord(map.size.y, cord_y);

    if (!client)
        return;
    for (int i = 0; i < INVENTORY_SLOTS; i += 1) {
        for (ssize_t user = array_len(map.tiles[idx_x][idx_y].players_uuid);
             user > 0; user -= 1)
            dprintf(client->cfd, " player");
        for (ssize_t obj = map.tiles[idx_x][idx_y].slots[i].units; obj > 0;
             obj -= 1)
            dprintf(
                client->cfd, " %s",
                RESOURCES_INVENTORY[map.tiles[idx_x][idx_y].slots[i].resource]);
    }
}
