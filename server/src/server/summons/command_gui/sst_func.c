/*
** EPITECH PROJECT, 2023
** sst_func
** File description:
** zappy
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zappy/server.h>
#include <zappy/server/utils.h>

int sst_func(server_t *server, char *args[], client_node_t *client)
{
    uint64_t tmp = 0;

    if (!args || array_len(args) != 3 || !server || !client)
        return FAILURE;
    tmp = atoi(args[1]);
    if (tmp == 0 && (strlen(args[1]) != 1 || args[1][0] != '0'))
        return FAILURE;
    server->clock.freq = tmp;
    dprintf(client->cfd, "sst %i\n", server->clock.freq);
    return SUCCESS;
}
