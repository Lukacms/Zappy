/*
** EPITECH PROJECT, 2023
** connect_nbr_func
** File description:
** zappy
*/

#include <stdio.h>
#include <zappy/server.h>
#include <zappy/server/client.h>
#include <zappy/server/infos.h>
#include <zappy/server/summon/utils.h>
#include <zappy/server/utils.h>

int connect_nbr_func(server_t *server, char *args[], client_node_t *client)
{
    team_t *team = NULL;

    if (!args || array_len(args) != 2 || !server)
        return set_error(client->cfd, INVALID_ACTION, false);
    if (!(team = find_team_by_uuid(client->uuid_team, server)))
        return set_error(client->cfd, INVALID_ACTION, false);
    dprintf(client->cfd, "%zu\n", team->spots_free);
    return SUCCESS;
}
