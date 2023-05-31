/*
** EPITECH PROJECT, 2023
** msz_func
** File description:
** zappy
*/

#include <zappy/server/infos.h>

int msz_func(server_t *server, char *args[], client_node_t *client)
{
    dprintf(client->cfd, "msz %i %i\n", server->map.size.x, server->map.size.y);
    return 0;
}
