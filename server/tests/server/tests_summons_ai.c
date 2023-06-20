/*
** EPITECH PROJECT, 2023
** server
** File description:
** tests_summons_ai
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <unistd.h>
#include <zappy/server.h>
#include <zappy/server/client.h>
#include <zappy/server/destroy.h>
#include <zappy/server/summon/utils.h>

void redirect(void);
int create_default_server(server_t *server, int port);

Test(broadcast_func, broadcast_func)
{
    cr_assert_eq(broadcast_func(NULL, NULL, NULL), FAILURE);
}

Test(connect_nbr, connect_nbr, .init = redirect)
{
    server_t server = {0};
    client_node_t *client = malloc(sizeof(client_node_t));
    char *inv[] = {"", "", NULL};
    char *args[] = {"args", NULL};

    cr_assert_eq(create_default_server(&server, 4256), SUCCESS);
    client->cfd = STDERR_FILENO;
    add_client_node(client, &server);
    add_client_to_team(client, &server, "Team1");
    cr_assert_eq(connect_nbr_func(NULL, NULL, NULL), FAILURE);
    cr_assert_eq(connect_nbr_func(&server, NULL, NULL), FAILURE);
    cr_assert_eq(connect_nbr_func(&server, NULL, client), FAILURE);
    cr_assert_eq(connect_nbr_func(&server, inv, client), FAILURE);
    client->cfd = STDOUT_FILENO;
    cr_assert_eq(connect_nbr_func(&server, args, client), SUCCESS);
    cr_assert_stdout_eq_str("2\n");
    client->cfd = STDERR_FILENO;
    client->uuid_team = "";
    cr_assert_eq(connect_nbr_func(&server, args, client), FAILURE);
    destroy_server(&server);
}

Test(inventory_func, inventory_func, .init = redirect)
{
    server_t server = {0};
    client_node_t *client = malloc(sizeof(client_node_t));
    char *inv[] = {"", "", NULL};
    char *args[] = {"args", NULL};

    cr_assert_eq(create_default_server(&server, 4257), SUCCESS);
    client->cfd = STDERR_FILENO;
    client->stats.inventory[FOOD].units = 37;
    client->stats.inventory[LINEMATE].units = 36;
    client->stats.inventory[DERAUMERE].units = 35;
    client->stats.inventory[SIBUR].units = 34;
    client->stats.inventory[MENDIANE].units = 33;
    client->stats.inventory[PHIRAS].units = 32;
    client->stats.inventory[THYSTAME].units = 31;
    add_client_node(client, &server);
    add_client_to_team(client, &server, "Team1");
    cr_assert_eq(inventory_func(NULL, NULL, NULL), FAILURE);
    cr_assert_eq(inventory_func(&server, NULL, NULL), FAILURE);
    cr_assert_eq(inventory_func(&server, NULL, client), FAILURE);
    cr_assert_eq(inventory_func(&server, inv, client), FAILURE);
    client->cfd = STDOUT_FILENO;
    cr_assert_eq(inventory_func(&server, args, client), SUCCESS);
    cr_assert_stdout_eq_str("[food 37, linemate 36, deraumere 35, sibur "
                            "34, mendiane 33, phiras "
                            "32, thystame 31]\n");
    destroy_server(&server);
}