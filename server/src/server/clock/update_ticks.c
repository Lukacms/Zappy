/*
** EPITECH PROJECT, 2023
** clock
** File description:
** update_ticks
*/

#include <stdio.h>
#include <zappy/server.h>
#include <zappy/server/client.h>
#include <zappy/server/clock/utils.h>
#include <zappy/server/map_utils.h>

// TODO by doudou
static void check_incantation(server_t *server, client_node_t *client)
{
    client->stats.action.type = NOTHING;
    client->stats.action.ticks = -1;
}

static void update_ticks_clients(server_t *server, int ticks_elapsed)
{
    client_node_t *client = 0;

    if (!(client = server->clients.head))
        return;
    for (unsigned int i = 0; i < server->clients.length; i++) {
        if (client->state != AI) {
            client = client->next;
            continue;
        }
        if (client->stats.action.type == ACTION &&
            ticks_elapsed >= client->stats.action.ticks) {
            client->stats.action.type = NOTHING;
            client->stats.action.ticks = -1;
        }
        if (client->stats.action.type == INCANTATION &&
            ticks_elapsed >= client->stats.action.ticks) {
            check_incantation(server, client);
        }
        client = client->next;
    }
}

static void update_map_ticks(server_t *server, int ticks_elapsed)
{
    if (ticks_elapsed >= server->map.last_updated) {
        server->map.last_updated += UPDATE_TICKS;
        update_map(server);
    }
}

void update_ticks(server_t *server)
{
    int ticks_elapsed = -1;

    if (!server || (ticks_elapsed = gettickselapsed(&server->clock)) <= 0)
        return;
    update_ticks_clients(server, ticks_elapsed);
    update_map_ticks(server, ticks_elapsed);
    if (ticks_elapsed >= server->clients.last_meal) {
        server->clients.last_meal += MEAL_TIME;
        starve_players(server);
    }
}
