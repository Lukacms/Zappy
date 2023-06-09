/*
** EPITECH PROJECT, 2023
** eggs
** File description:
** delete_egg_from_team
*/

#include <zappy/server.h>

int delete_egg_from_team(server_t *server, int id)
{
    if (!server || id < 0)
        return FAILURE;
    return SUCCESS;
}
