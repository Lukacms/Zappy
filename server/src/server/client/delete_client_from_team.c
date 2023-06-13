/*
** EPITECH PROJECT, 2023
** client
** File description:
** delete_client_from_team
*/

#include <string.h>
#include <zappy/server.h>
#include <zappy/server/client.h>

void delete_client_from_team(client_node_t *client, server_t *server)
{
    team_t *team = NULL;

    if (!client || !server ||
        !(team = find_team_by_uuid(client->uuid_team, server)))
        return;
    for (unsigned int i = 0; i < team->nb_clients; i++) {
        if (strcmp(client->uuid, team->uuid_clients[i]) == SUCCESS) {
            team->uuid_clients[i] = NULL;
            break;
        }
    }
    team->nb_clients--;
    add_egg_to_team(client, server);
}
