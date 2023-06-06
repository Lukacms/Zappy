/*
** EPITECH PROJECT, 2023
** client
** File description:
** find_team
*/

#include <string.h>
#include <zappy/server.h>

team_t *find_team_by_uuid(const char *uuid, server_t *server)
{
    if (!uuid || !server || !server->teams)
        return NULL;
    for (unsigned int i = 0; server->teams[i]; i++) {
        if (strcmp(uuid, server->teams[i]->uuid) == SUCCESS)
            return server->teams[i];
    }
    return NULL;
}

team_t *find_team_by_name(const char *name, server_t *server)
{
    if (!name || !server || !server->teams)
        return NULL;
    for (unsigned int i = 0; server->teams[i]; i++) {
        if (strcmp(name, server->teams[i]->team_name) == SUCCESS)
            return server->teams[i];
    }
    return NULL;
}
