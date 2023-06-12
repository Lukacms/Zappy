/*
** EPITECH PROJECT, 2023
** eggs
** File description:
** delete_egg_from_team
*/

#include <stdlib.h>
#include <zappy/server.h>
#include <zappy/server/summon/utils.h>
#include <zappy/server/utils.h>

static egg_t **delete_from_egg_array(egg_t **src, u_int ind)
{
    ssize_t size = 0;
    egg_t **dest = NULL;
    int flag = 0;

    if (!src || (size = array_len(src)) < ind) {
        free(src);
        return NULL;
    }
    if (!(dest = malloc(sizeof(egg_t *) * (size))))
        return NULL;
    dest[size] = NULL;
    for (u_int i = 0; i < size - 1; i++) {
        if (i == ind)
            flag = 1;
        dest[i] = src[i + flag];
    }
    free(src);
    return dest;
}

static int check_team_eggs(server_t *server, int id, u_int ind)
{
    int flag = 0;
    team_t **teams = server->teams;

    if (!teams[ind]->eggs)
        return FAILURE;
    for (u_int i = 0; teams[ind]->eggs[i]; i++) {
        if (teams[ind]->eggs[i]->nb == id) {
            send_toall_guicli(server, DISPATCH_EDI, teams[ind]->eggs[i]->nb);
            teams[ind]->eggs = delete_from_egg_array(teams[ind]->eggs, i);
            flag = 1;
            break;
        }
    }
    if (flag && teams[ind]->eggs)
        return SUCCESS;
    return FAILURE;
}

int delete_egg_from_team(server_t *server, int id)
{
    if (!server || id < 0)
        return FAILURE;
    for (u_int i = 0; server->teams[i]; i++)
        if (check_team_eggs(server, id, i) == SUCCESS)
            return SUCCESS;
    return FAILURE;
}
