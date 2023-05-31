/*
** EPITECH PROJECT, 2023
** sgt_func
** File description:
** zappy
*/

#include <stdint.h>
#include <zappy/server/infos.h>

int sgt_func(server_t *server, char *args[], client_node_t *client)
{
    dprintf(client->cfd, "sgt %li\n", server->time);
    return 0;
}
