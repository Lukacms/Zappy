/*
** EPITECH PROJECT, 2023
** gui_connect_func
** File description:
** zappy
*/

#include <zappy/server/infos.h>
#include <zappy/server/utils.h>

int gui_connect_func(server_t *server, char *args[], client_node_t *client)
{
    client->state = GUI;
    msz_func(server, args, client);
    sgt_func(server, args, client);
    mct_func(server, args, client);
    tna_func(server, args, client);
    return 0;
}
