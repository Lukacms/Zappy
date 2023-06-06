/*
** EPITECH PROJECT, 2023
** ppo_func
** File description:
** zappy
*/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <zappy/server.h>
#include <zappy/server/utils.h>

int ppo_func(server_t *server, char *args[], client_node_t *client)
{
    client_node_t *tmp = server->clients.head;

    if (!args || array_len(args) != 3)
        return FAILURE;
    for (u_int ind = 0; ind < server->clients.length; ind++) {
        if (strcmp(args[1], tmp->uuid) == 0) {
            dprintf(client->cfd, "ppo %s %zu %zu %i\n", tmp->uuid,
                    tmp->stats.pos.x, tmp->stats.pos.y, tmp->stats.orientation);
            return SUCCESS;
        }
        tmp = tmp->next;
    }
    return FAILURE;
}
