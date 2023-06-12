/*
** EPITECH PROJECT, 2023
** destroy
** File description:
** destroy_server
*/

#include <stdlib.h>
#include <zappy/server/destroy.h>

void destroy_server(server_t *server)
{
    if (!server)
        return;
    destroy_clients(&server->clients);
    destroy_teams(server->teams);
    for (u_int i = 0; server->map.tiles[i]; i++) {
        free(server->map.tiles[i]->eggs);
        free(server->map.tiles[i]->players_uuid);
        free(server->map.tiles[i]);
    }
    free(server->map.tiles);
}
