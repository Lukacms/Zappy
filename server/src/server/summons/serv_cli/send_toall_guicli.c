/*
** EPITECH PROJECT, 2023
** teams
** File description:
** creat_new_client
*/

#include <stdarg.h>
#include <stdio.h>
#include <zappy/server.h>
#include <zappy/server/infos.h>

int send_toall_guicli(server_t *server, char *str, ...)
{
    client_node_t *tmp = NULL;
    va_list ap;

    if (!server || !(tmp = server->clients.head))
        return FAILURE;
    va_start(ap, str);
    for (unsigned int ind = 0; ind < server->clients.length; tmp = tmp->next) {
        if (tmp->state == GUI)
            dprintf(tmp->cfd, str, ap);
    }

    va_end(ap);
    return SUCCESS;
}
