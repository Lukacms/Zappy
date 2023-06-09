/*
** EPITECH PROJECT, 2023
** inventory_func
** File description:
** zappy
*/

#include <stdio.h>
#include <zappy/server.h>
#include <zappy/server/clock/utils.h>
#include <zappy/server/summon/utils.h>
#include <zappy/server/utils.h>

int inventory_func(server_t *server, char *args[], client_node_t *c)
{
    if (!args || array_len(args) != 2 || !server || !c)
        return set_error(c->cfd, INVALID_ACTION, false);
    add_ticks_occupied(c, RESTRAINT_INVENTORY, server);
    dprintf(
        c->cfd, AI_INVENTORY, c->stats.inventory[FOOD].units,
        c->stats.inventory[LINEMATE].units, c->stats.inventory[DERAUMERE].units,
        c->stats.inventory[SIBUR].units, c->stats.inventory[MENDIANE].units,
        c->stats.inventory[PHIRAS].units, c->stats.inventory[THYSTAME].units);
    send_toall_guicli(
        server, DISPATCH_PIN, c->cfd, c->stats.pos.x, c->stats.pos.y,
        c->stats.inventory[FOOD].units, c->stats.inventory[LINEMATE].units,
        c->stats.inventory[DERAUMERE].units, c->stats.inventory[SIBUR].units,
        c->stats.inventory[MENDIANE].units, c->stats.inventory[PHIRAS].units,
        c->stats.inventory[THYSTAME].units);
    return SUCCESS;
}
