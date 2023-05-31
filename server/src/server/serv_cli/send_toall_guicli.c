/*
** EPITECH PROJECT, 2023
** teams
** File description:
** creat_new_client
*/

#include <stdio.h>
#include <zappy/server/infos.h>

int send_toall_guicli(server_t *server, char *str, ...)
{
    client_node_t *tmp = server->clients.head;
    va_list ap;

    va_start(ap, str);
    while (tmp) {
        if (tmp->state == GUI)
            dprintf(tmp->cfd, str, ap);
    }
    va_end(ap);
    return 0;
}
