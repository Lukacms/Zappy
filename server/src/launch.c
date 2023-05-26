/*
** EPITECH PROJECT, 2023
** src
** File description:
** launch
*/

#include <zappy/config/config.h>
#include <zappy/server.h>

int launch(args_config_t *args)
{
    server_t server = {0};

    if (create_server(&server, args) != SUCCESS)
        return FAILURE;
    return server_loop(&server);
}
