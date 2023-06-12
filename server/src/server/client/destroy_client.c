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

void destroy_client(server_t *server, client_node_t *client)
{
    if (!server || !client)
        return;
    server->clients.length -= 1;
    if (server->clients.head == client)
        server->clients.head = server->clients.head->next;
    else {
        client->prev->next = client->next;
        client->next->prev = client->prev;
    }
    if (server->clients.length == 0)
        server->clients.head = NULL;
    free(client->uuid);
    FD_CLR(client->cfd, &server->clients_fd);
    if (fcntl(client->cfd, F_GETFD) > 0)
        close(client->cfd);
    free(client);
}
