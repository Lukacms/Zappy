/*
** EPITECH PROJECT, 2023
** tna_func
** File description:
** zappy
*/

#include <zappy/server/infos.h>

int tna_func(server_t *server, char *args[], client_node_t *client)
{
    client_node_t *tmp = server->clients.head;

    while (tmp) {
        dprintf(client->cfd, "tna %s\n", tmp->uuid_team);
        tmp = tmp->next;
    }
    return 0;
}
