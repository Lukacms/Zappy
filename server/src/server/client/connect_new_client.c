/*
** EPITECH PROJECT, 2023
** client
** File description:
** connect_new_client
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>
#include <zappy/server.h>
#include <zappy/server/client.h>
#include <zappy/server/utils.h>

int connect_new_client(server_t *server)
{
    client_node_t *new_client = malloc(sizeof(client_node_t));
    int size_addr = sizeof(struct sockaddr_in);

    if (!server || !new_client)
        return FAILURE;
    if ((new_client->cfd = accept(server->server_fd,
                                  (struct sockaddr *)&new_client->socket_infos,
                                  (socklen_t *)&size_addr)) < 0)
        return set_error(STDERR_FILENO, "Accepting client", true);
    FD_SET(new_client->cfd, &server->clients_fd);
    if (!(new_client->uuid = generate_uuid()))
        return set_error(new_client->cfd, "Creating unique uuid", true);
    add_client_node(new_client, server);
    return SUCCESS;
}
