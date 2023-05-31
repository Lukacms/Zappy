/*
** EPITECH PROJECT, 2023
** sst_func
** File description:
** zappy
*/

#include <stdint.h>
#include <zappy/server/infos.h>

int sst_func(server_t *server, char *args[], client_node_t *client)
{
    uint64_t tmp = 0;

    if (!args || !args[0] || !args[1] || args[2])
        return 1;
    tmp = atoi(args[1]);
    if (tmp == 0 && (strlen(args[1]) != 1 || args[1][0] != '0'))
        return 1;
    server->time = tmp;
    dprintf(client->cfd, "sst %li\n", server->time);
    return 0;
}
