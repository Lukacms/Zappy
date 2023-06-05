/*
** EPITECH PROJECT, 2023
** connect_nbr_func
** File description:
** zappy
*/

#include <stdio.h>
#include <zappy/server.h>
#include <zappy/server/infos.h>
#include <zappy/server/summon/infos.h>
#include <zappy/server/utils.h>

int connect_nbr_func(server_t *server, char *args[], client_node_t *client)
{
    int result = 0;

    if (!args || array_len(args) != 2 || !server)
        return set_error(client->cfd, INVALID_ACTION, false);
    for (int i = 0; server->teams[i] != NULL; i += 1) {
        if (server->teams[i]->nb_clients != 0)
            result += 1;
    }
    dprintf(client->cfd, "%i", result);
    return SUCCESS;
}
