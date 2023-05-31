/*
** EPITECH PROJECT, 2023
** ppo_func
** File description:
** zappy
*/

#include <zappy/server/infos.h>

int ppo_func(server_t *server, char *args[], client_node_t *client)
{
    client_node_t *tmp = server->clients.head;

    if (!args || !args[0] || !args[1] || args[2])
        return 1;
    while (tmp) {
        if (strcmp(args[1], tmp->uuid) == 0) {
            dprintf(client->cfd, "ppo %s %i %i %i\n", tmp->uuid, tmp->stats.pos.x,
                    tmp->stats.pos.y, tmp->stats.orientation);
            return 0;
        }
        tmp = tmp->next;
    }
    return 1;
}
