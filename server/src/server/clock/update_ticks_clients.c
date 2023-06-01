/*
** EPITECH PROJECT, 2023
** clock
** File description:
** update_ticks_clients
*/

#include <zappy/server.h>
#include <zappy/server/clock/utils.h>

void update_ticks_clients(server_t *server)
{
    int ticks_elapsed = -1;
    client_node_t *client = 0;

    if (!server || (ticks_elapsed = gettickselapsed(&server->clock)) <= 0)
        return;
    client = server->clients.head;
    for (unsigned int i = 0; i < server->clients.length; i++) {
        if (client->state != AI)
            continue;
        if (client->stats.action.type == ACTION &&
            ticks_elapsed >= client->stats.action.ticks) {
            client->stats.action.type = NOTHING;
            client->stats.action.ticks = -1;
        }
        client = client->next;
    }
}
