/*
** EPITECH PROJECT, 2023
** tna_func
** File description:
** zappy
*/

#include <stdio.h>
#include <sys/types.h>
#include <zappy/server.h>
#include <zappy/server/utils.h>

int tna_func(server_t *server, char __attribute__((unused)) * args[],
            client_node_t *client)
{
    if (!server)
        return FAILURE;
    for (u_int ind = 0; server->teams[ind]; ind++) {
        dprintf(client->cfd, "tna %s\n", server->teams[ind]->team_name);
    }
    return SUCCESS;
}
