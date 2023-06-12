/*
** EPITECH PROJECT, 2023
** client
** File description:
** kill_player
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <zappy/server.h>
#include <zappy/server/summon/utils.h>

int kill_player(server_t *server, client_node_t *client)
{
    if (!server || !client)
        return FAILURE;
    server->clients.length -= 1;
    if (server->clients.head == client)
        server->clients.head = server->clients.head->next;
    else {
        client->prev->next = client->next;
        client->next->prev = client->prev;
    }
    if (server->clients.length == 0)
        server->clients.head = NULL;
    send_toall_guicli(server, DISPATCH_PDI, client->cfd);
    dprintf(client->cfd, AI_DEATH);
    free(client->uuid);
    FD_CLR(client->cfd, &server->clients_fd);
    close(client->cfd);
    free(client);
    return SUCCESS;
}
