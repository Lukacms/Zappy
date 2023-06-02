/*
** EPITECH PROJECT, 2023
** summons
** File description:
** handle_summon
*/

#include <zappy/server.h>
#include <zappy/server/client.h>
#include <zappy/server/summon/utils.h>

static int handle_client_summon(const char *cmd, client_node_t *client,
                                server_t *server)
{
    if (!cmd)
        return SUCCESS;
    return SUCCESS;
}

int handle_summon(server_t *server, int cfd)
{
    client_node_t *client = NULL;

    if (!server || cfd <= 0 || !(client = find_client_by_fd(cfd, server)))
        return FAILURE;
    if (get_summon(server, client) != SUCCESS)
        return SUCCESS;
    if (client->stats.action.type == NOTHING)
        return handle_client_summon(pop_summon(client), client, server);
    return SUCCESS;
}
