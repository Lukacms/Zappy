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
    char output[BUFFER_SIZE] = {0};

    dprintf(client->cfd, "%zu\n%zu %zu\n", team->spots_free, server->map.size.x,
            server->map.size.y);
    sprintf(output, DISPATCH_PNW, client->cfd, client->stats.pos.x,
            client->stats.pos.y, client->stats.orientation, client->stats.level,
            team->team_name);
    send_toall_guicli(server, output);
}

int add_client_to_team(client_node_t *client, server_t *server,
                        const char *team_name)
{
    int team_ind = -1;

    if (!client || !server || !team_name)
        return FAILURE;
    if ((team_ind = find_team_by_name(team_name, server)) < 0)
        return set_error(client->cfd, UNKNOWN_COMMAND, false);
    if (server->teams[team_ind]->spots_free <= 0)
        return set_error(client->cfd, INVALID_ACTION, false);
    client->state = AI;
    client->uuid_team = server->teams[team_ind]->uuid;
    server->teams[team_ind]->spots_free--;
    if (from_egg_to_player(client, &server->teams[team_ind], server) != SUCCESS)
        return FAILURE;
    for (unsigned int i = 0; i < server->teams[team_ind]->nb_clients; i++)
        if (!server->teams[team_ind]->uuid_clients[i])
            server->teams[team_ind]->uuid_clients[i] = client->uuid;
    send_infos(server, client, server->teams[team_ind]);
    return SUCCESS;
}
