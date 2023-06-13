/*
** EPITECH PROJECT, 2023
** command_ia
** File description:
** fork_func
*/

#include <stdio.h>
#include <zappy/server.h>
#include <zappy/server/client.h>
#include <zappy/server/clock/utils.h>
#include <zappy/server/summon/utils.h>
#include <zappy/server/utils.h>

int fork_func(server_t *server, char *args[], client_node_t *client)
{
    if (!server || !client)
        return FAILURE;
    if (!args || array_len(args) != 1)
        return set_error(client->cfd, INVALID_ACTION, false);
    add_egg_to_team(client, server);
    dprintf(client->cfd, BASIC_VALID);
    add_ticks_occupied(client, RESTRAINT_FORK, server);
    return SUCCESS;
}
