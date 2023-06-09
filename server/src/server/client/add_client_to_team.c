/*
** EPITECH PROJECT, 2023
** client
** File description:
** add_client_to_team
*/

#include <stdio.h>
#include <zappy/server.h>
#include <zappy/server/client.h>
#include <zappy/server/summon/utils.h>
#include <zappy/server/utils.h>

static void send_infos(server_t *server, client_node_t *client, team_t *team)
{
    dprintf(client->cfd, "%zu\n%zu %zu\n", team->spots_free, server->map.size.x,
            server->map.size.y);
    send_toall_guicli(server, DISPATCH_PNW, client->cfd, client->stats.pos.x,
                      client->stats.pos.y, client->stats.orientation,
                      client->stats.level, team->team_name);
}

int add_client_to_team(client_node_t *client, server_t *server,
                       const char *team_name)
{
    team_t *team = NULL;

    if (!client || !server || !team_name)
        return FAILURE;
    if (!(team = find_team_by_name(team_name, server)))
        return set_error(client->cfd, UNKNOWN_COMMAND, false);
    if (team->spots_free <= 0)
        return set_error(client->cfd, INVALID_ACTION, false);
    client->state = AI;
    client->uuid_team = team->uuid;
    team->spots_free--;
    if (from_egg_to_player(client, &team) != SUCCESS)
        return FAILURE;
    for (unsigned int i = 0; i < team->nb_clients; i++)
        if (!team->uuid_clients[i])
            team->uuid_clients[i] = client->uuid;
    send_infos(server, client, team);
    return SUCCESS;
}