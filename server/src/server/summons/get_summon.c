/*
** EPITECH PROJECT, 2023
** summons
** File description:
** get_summon
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <zappy/server.h>
#include <zappy/server/summon/utils.h>
#include <zappy/server/utils.h>

int get_summon(server_t *server, client_node_t *client)
{
    char *summon = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    int size = 0;

    if (!server || !client)
        return FAILURE;
    memset(summon, '\0', BUFFER_SIZE);
    if ((size = read(client->cfd, summon, BUFFER_SIZE)) < 0)
        return set_error(client->cfd, "ko", false);
    summon[size - 1] = '\0';
    if (add_summon(summon, client) != SUCCESS)
        free(summon);
    return SUCCESS;
}
