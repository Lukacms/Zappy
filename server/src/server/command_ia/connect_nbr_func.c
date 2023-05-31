/*
** EPITECH PROJECT, 2023
** connect_nbr_func
** File description:
** zappy
*/

#include <zappy/server/infos.h>

int connect_nbr_func(server_t *server, char *args[], client_node_t *client)
{
    int result = 0;

    for (int i = 0; server->teams[i] != NULL; i += 1) {
        if (server->teams[i]->nb_clients != 0)
            result += 1;
    }
    dprintf(client->cfd, "%i", result);
    return 0;
}
