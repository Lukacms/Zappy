/*
** EPITECH PROJECT, 2023
** load
** File description:
** update_server_with_args
*/

#include <stdlib.h>
#include <string.h>
#include <zappy/server.h>
#include <zappy/server/map_utils.h>
#include <zappy/server/utils.h>

static int fill_team_infos(team_t *team, args_config_t *args, u_int ind)
{
    if (!(team->uuid = generate_uuid()))
        return FAILURE;
    team->nb_clients = args->nb_clients_og;
    if (!(team->uuid_clients = malloc(sizeof(char *) * (team->nb_clients + 1))))
        return FAILURE;
    memset(team->uuid_clients, 0, team->nb_clients + 1);
    team->spots_free = team->nb_clients;
    team->team_name = args->team_names[ind];
    return SUCCESS;
}

int update_server_with_args(server_t *server, args_config_t *args)
{
    if (!server || !args || !args->team_names)
        return FAILURE;
    server->map.size = args->world;
    server->teams =
        malloc(sizeof(team_t *) * (array_len(args->team_names) + 1));
    if (!server->teams)
        return FAILURE;
    for (unsigned int i = 0; args->team_names[i]; i++) {
        if (!(server->teams[i] = malloc(sizeof(team_t))))
            return FAILURE;
        if (fill_team_infos(server->teams[i], args, i) != SUCCESS)
            return FAILURE;
    }
    return generate_map(server);
}
