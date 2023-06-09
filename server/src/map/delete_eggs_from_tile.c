/*
** EPITECH PROJECT, 2023
** map
** File description:
** delete_eggs_from_tile
*/

#include <stdlib.h>
#include <zappy/server.h>
#include <zappy/server/client.h>

int delete_eggs_from_tile(server_t *server, vector2i_t pos)
{
    if (!server)
        return FAILURE;
    for (u_int i = 0; server->map.tiles[pos.y][pos.x].eggs[i]; i++) {
        delete_egg_from_team(server, server->map.tiles[pos.y][pos.x].eggs[i]);
    }
    free(server->map.tiles[pos.y][pos.x].eggs);
    server->map.tiles[pos.y][pos.x].eggs = NULL;
    return SUCCESS;
}
