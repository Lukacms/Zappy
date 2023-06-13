/*
** EPITECH PROJECT, 2023
** client
** File description:
** kill_player
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <zappy/server.h>
#include <zappy/server/client.h>
#include <zappy/server/summon/utils.h>

static void rebase_nodes(server_t *server, client_node_t *client)
{
    server->clients.length -= 1;
    if (server->clients.head == client) {
        server->clients.head = server->clients.head->next;
    }
    client->prev->next = client->next;
    client->next->prev = client->prev;
    if (server->clients.length == 0)
        server->clients.head = NULL;
}

int kill_player(server_t *server, client_node_t *client)
{
    if (!server || !client)
        return FAILURE;
    rebase_nodes(server, client);
    delete_client_from_team(client, server);
    send_toall_guicli(server, DISPATCH_PDI, client->cfd);
    if (fcntl(client->cfd, F_GETFD) != 0)
        dprintf(client->cfd, AI_DEATH);
    free(client->uuid);
    FD_CLR(client->cfd, &server->clients_fd);
    close(client->cfd);
    free(client);
    return SUCCESS;
}
