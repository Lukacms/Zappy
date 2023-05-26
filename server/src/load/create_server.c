/*
** EPITECH PROJECT, 2023
** load
** File description:
** create_server
*/

#include <sys/select.h>
#include <sys/socket.h>
#include <zappy/config/arguments.h>
#include <zappy/server.h>
#include <zappy/server/infos.h>

static struct sockaddr_in create_server_infos(int const port)
{
    struct sockaddr_in dest = {0};

    dest.sin_family = AF_INET;
    dest.sin_port = htons(port);
    dest.sin_addr.s_addr = INADDR_ANY;
    return dest;
}

static int bind_listen_server(server_t *serv)
{
    if (bind(serv->server_fd, (const struct sockaddr *)(&serv->socket_infos),
            sizeof(struct sockaddr)) < 0)
        return FAILURE;
    if (listen(serv->server_fd, FD_SETSIZE) < 0)
        return FAILURE;
    return SUCCESS;
}

int create_server(server_t *server, args_config_t *args)
{
    if (!server || !args)
        return FAILURE;
    if ((server->server_fd = socket(AF_INET, SOCK_STREAM, TCP)) < 0)
        return FAILURE;
    server->socket_infos = create_server_infos(args->port);
    if (bind_listen_server(server) != SUCCESS)
        return FAILURE;
    FD_ZERO(&server->clients_fd);
    FD_SET(server->server_fd, &server->clients_fd);
    return SUCCESS;
}
