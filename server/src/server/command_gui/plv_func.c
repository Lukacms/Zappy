/*
** EPITECH PROJECT, 2023
** plv_func
** File description:
** zappy
*/

#include <zappy/server/infos.h>

int plv_func(server_t *server, char *args[], client_node_t *client)
{
    client_node_t *tmp = server->clients.head;

    if (!args || !args[0] || !args[1] || args[2])
        return 1;
    while (tmp) {
        if (strcmp(args[1], tmp->uuid) == 0) {
            dprintf(client->cfd, "plv %s %li\n", tmp->uuid, tmp->stats.level);
            return 0;
        }
        tmp = tmp->next;
    }
    return 1;
}
