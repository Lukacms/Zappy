/*
** EPITECH PROJECT, 2023
** eggs
** File description:
** from_egg_to_player
*/

#include <stdlib.h>
#include <zappy/server.h>

int from_egg_to_player(client_node_t *client, team_t **team)
{
    if (!client || !team)
        return FAILURE;
    client->stats.pos = (*team)->eggs[(*team)->spots_free]->pos;
    free((*team)->eggs[(*team)->spots_free]);
    (*team)->eggs[(*team)->spots_free] = NULL;
    return SUCCESS;
}
