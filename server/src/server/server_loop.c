/*
** EPITECH PROJECT, 2023
** server
** File description:
** server_loop
*/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <zappy/server.h>
#include <zappy/server/infos.h>

// TODO implement both methods
static void check_if_client_ready(server_t *server, size_t ind, fd_set *clients)
{
    if (FD_ISSET(ind, clients)) {
        if (ind == (size_t)server->server_fd)
            // connect_client(server);
            ind++;
        else
            ind++;
        // handle_client(server, ind);
    }
}

int server_loop(server_t *server)
{
    fd_set clients_ready = {0};
    struct timeval val = {0};

    if (!server)
        return FAILURE;
    signal(SIGINT, &handle_sigint);
    while (server->running) {
        server = get_server();
        clients_ready = server->clients_fd;
        if (select(FD_SETSIZE + 1, &clients_ready, NULL, NULL, &val) < 0) {
            perror("Couldn't select a client ready");
            continue;
        }
        for (size_t i = 0; i < FD_SETSIZE; i++)
            check_if_client_ready(server, i, &clients_ready);
        set_server(server);
    }
    return SUCCESS;
}
