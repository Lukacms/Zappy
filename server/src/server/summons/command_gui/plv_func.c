/*
** EPITECH PROJECT, 2023
** plv_func
** File description:
** zappy
*/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <zappy/server.h>
#include <zappy/server/utils.h>

int plv_func(server_t *server, char *args[], client_node_t *client)
{
    client_node_t *tmp = NULL;

    if (!client || !server || !args || array_len(args) != 3)
        return FAILURE;
    tmp = server->clients.head;
    for (u_int ind = 0; ind < server->clients.length; ind++) {
        if (strcmp(args[1], tmp->uuid) == 0) {
            dprintf(client->cfd, "plv %s %li\n", tmp->uuid, tmp->stats.level);
            return SUCCESS;
        }
        tmp = tmp->next;
    }
    return FAILURE;
}
