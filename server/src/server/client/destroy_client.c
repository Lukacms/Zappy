/*
** EPITECH PROJECT, 2023
** client
** File description:
** destroy_client
*/

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <zappy/server.h>

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

void destroy_client(server_t *server, client_node_t *client)
{
    if (!server || !client)
        return;
    rebase_nodes(server, client);
    free(client->uuid);
    FD_CLR(client->cfd, &server->clients_fd);
    close(client->cfd);
    free(client);
}
