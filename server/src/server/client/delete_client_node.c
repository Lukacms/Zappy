/*
** EPITECH PROJECT, 2023
** client
** File description:
** delete_client_node
*/

#include <stdlib.h>
#include <zappy/server/client.h>

static void del_client_from_server(client_node_t *to_del, server_t *server)
{
    if (--server->clients.length == 0) {
        server->clients.head = NULL;
        free(to_del);
        return;
    }
    if (server->clients.head == to_del)
        server->clients.head = server->clients.head->next;
    to_del->prev->next = to_del->next;
    to_del->next->prev = to_del->prev;
    free(to_del->uuid);
    if (to_del->state == AI)
        delete_client_from_team(to_del, server);
    free(to_del);
}

void delete_client_by_uuid(const char *const uuid, server_t *server)
{
    client_node_t *to_del = NULL;

    if (!server || !uuid || !(to_del = find_client_by_uuid(uuid, server)))
        return;
    del_client_from_server(to_del, server);
}

void delete_client_by_fd(const int fd, server_t *server)
{
    client_node_t *to_del = NULL;

    if (!server || !(to_del = find_client_by_fd(fd, server)))
        return;
    del_client_from_server(to_del, server);
}
