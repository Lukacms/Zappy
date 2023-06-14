/*
** EPITECH PROJECT, 2023
** map
** File description:
** from_egg_to_player_tile
*/

#include <stdio.h>
#include <stdlib.h>
#include <zappy/server.h>
#include <zappy/server/map_utils.h>
#include <zappy/server/utils.h>

static int *shorten_array(int *src, int nb)
{
    int size = len_eggs(src);
    int *dest = NULL;
    int flag = 0;

    if (size <= 0 || !(dest = malloc(sizeof(int) * (size))))
        return NULL;
    for (int i = 0; i < size - 1; i++) {
        if (src[i] == nb)
            flag = 1;
        dest[i] = src[i + flag];
    }
    dest[size - 1] = -1;
    return dest;
}

int from_egg_to_player_tile(server_t *s, client_node_t *client, egg_t *e)
{
    ssize_t size = 0;

    if (!s || !client || !e)
        return FAILURE;
    if ((size = array_len(s->map.tiles[e->pos.y][e->pos.x].players_uuid)) < 0)
        size = 0;
    s->map.tiles[e->pos.y][e->pos.x].players_uuid =
        realloc(s->map.tiles[e->pos.y][e->pos.x].players_uuid,
                sizeof(char *) * (size + 1));
    if (!s->map.tiles[e->pos.y][e->pos.x].players_uuid)
        return FAILURE;
    s->map.tiles[e->pos.y][e->pos.x].players_uuid[size] = client->uuid;
    for (u_int i = 0; s->map.tiles[e->pos.y][e->pos.x].eggs &&
         s->map.tiles[e->pos.y][e->pos.x].eggs[i] != -1;
         i++) {
        if (s->map.tiles[e->pos.y][e->pos.x].eggs[i] == e->nb) {
            s->map.tiles[e->pos.y][e->pos.x].eggs =
                shorten_array(s->map.tiles[e->pos.y][e->pos.x].eggs, i);
            break;
        }
    }
    return SUCCESS;
}
