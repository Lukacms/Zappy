/*
** EPITECH PROJECT, 2023
** eggs
** File description:
** add_egg_to_team
*/

#include <stdlib.h>
#include <zappy/server.h>
#include <zappy/server/client.h>

static egg_t *fill_infos(server_t *server, egg_t *egg, char *const uuid)
{
    egg->nb = ++server->map.last_egg_id;
    egg->team_uuid = uuid;
    egg->pos.x = rand() % server->map.size.x;
    egg->pos.y = rand() % server->map.size.y;
    return egg;
}

int add_egg_to_team(client_node_t *client, server_t *server)
{
    team_t *team = NULL;

    if (!client || !server ||
        !(team = find_team_by_uuid(client->uuid_team, server)))
        return FAILURE;
    team->nb_clients++;
    team->spots_free++;
    if (!(team->eggs =
              realloc(team->eggs, sizeof(egg_t *) * (team->nb_clients + 1))) ||
        !(team->uuid_clients = realloc(
              team->uuid_clients, sizeof(char *) * (team->nb_clients + 1))))
        return FAILURE;
    team->eggs[team->nb_clients] = NULL;
    team->uuid_clients[team->nb_clients] = NULL;
    if (!(team->eggs[team->nb_clients - 1] = malloc(sizeof(egg_t))))
        return FAILURE;
    team->eggs[team->nb_clients - 1] =
        fill_infos(server, team->eggs[team->nb_clients - 1], team->uuid);
    return SUCCESS;
}
