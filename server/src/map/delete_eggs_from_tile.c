/*
** EPITECH PROJECT, 2023
** map
** File description:
** delete_eggs_from_tile
*/

#include <stdlib.h>
#include <zappy/server.h>
#include <zappy/server/client.h>

static int len_eggs(const int *src)
{
    int size = 0;

    if (!src)
        return -1;
    while (src[size] != -1)
        size++;
    return size;
}

static __attribute__((unused)) int *shorten_array(int *src, int nb)
{
    int size = len_eggs(src);
    int *dest = NULL;
    int flag = 0;

    if (size <= 0 || !(dest = malloc(sizeof(int) * (len_eggs(src)))))
        return NULL;
    for (int i = 0; i < size - 1; i++) {
        if (src[i] == nb)
            flag = 1;
        dest[i] = src[i + flag];
    }
    dest[size - 1] = -1;
    return dest;
}

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
