/*
** EPITECH PROJECT, 2023
** eggs
** File description:
** add_egg_to_team
*/

#include <stdlib.h>
#include <zappy/server.h>
#include <zappy/server/client.h>

int add_egg_to_team(client_node_t *client, server_t *server)
{
    team_t *team = NULL;

    if (!client || !server ||
        !(team = find_team_by_uuid(client->uuid_team, server)))
        return FAILURE;
    team->nb_clients++;
    team->eggs = realloc(team->eggs, sizeof(egg_t *) * (team->nb_clients + 1));
    if (!team->eggs)
        return FAILURE;
    team->eggs[team->nb_clients] = NULL;
    if (!(team->eggs[team->nb_clients - 1] = malloc(sizeof(egg_t))))
        return FAILURE;
    team->eggs[team->nb_clients - 1]->nb = ++server->map.last_egg_id;
    team->eggs[team->nb_clients - 1]->team_uuid = team->uuid;
    team->eggs[team->nb_clients - 1]->pos.x = rand() % server->map.size.x;
    team->eggs[team->nb_clients - 1]->pos.y = rand() % server->map.size.y;
    return SUCCESS;
}
