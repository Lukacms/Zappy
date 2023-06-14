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

static int update_team_infos(server_t *server, int ind)
{
    server->teams[ind]->nb_clients++;
    server->teams[ind]->spots_free++;
    server->teams[ind]->eggs =
        realloc(server->teams[ind]->eggs,
                sizeof(egg_t *) * (server->teams[ind]->nb_clients + 1));
    server->teams[ind]->uuid_clients =
        realloc(server->teams[ind]->uuid_clients,
                sizeof(char *) * (server->teams[ind]->nb_clients + 1));
    if (!server->teams[ind]->eggs || !server->teams[ind]->uuid_clients)
        return FAILURE;
    server->teams[ind]->eggs[server->teams[ind]->nb_clients] = NULL;
    server->teams[ind]->uuid_clients[server->teams[ind]->nb_clients] = NULL;
    return SUCCESS;
}

int add_egg_to_team(client_node_t *client, server_t *server)
{
    int ind = -1;

    if (!client || !server ||
        (ind = find_team_by_uuid(client->uuid_team, server)) < 0)
        return FAILURE;
    if (update_team_infos(server, ind) != SUCCESS)
        return FAILURE;
    if (!(server->teams[ind]->eggs[server->teams[ind]->nb_clients - 1] =
              malloc(sizeof(egg_t))))
        return FAILURE;
    server->teams[ind]->eggs[server->teams[ind]->nb_clients - 1] = fill_infos(
        server, server->teams[ind]->eggs[server->teams[ind]->nb_clients - 1],
        server->teams[ind]->uuid);
    return SUCCESS;
}
