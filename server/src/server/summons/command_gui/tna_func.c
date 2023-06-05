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
    client_node_t *tmp = NULL;

    if (!server || !(tmp = server->clients.head))
        return FAILURE;
    for (u_int ind = 0; ind < server->clients.length; tmp = tmp->next) {
        dprintf(client->cfd, "tna %s\n", tmp->uuid_team);
    }
    return SUCCESS;
}
