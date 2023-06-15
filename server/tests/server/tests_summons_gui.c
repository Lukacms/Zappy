/*
** EPITECH PROJECT, 2023
** server
** File description:
** tests_summons_gui
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <unistd.h>
#include <zappy/server.h>
#include <zappy/server/client.h>
#include <zappy/server/destroy.h>
#include <zappy/server/summon/utils.h>
#include <zappy/server/utils.h>

void redirect(void);
int create_default_server(server_t *server, int port);

Test(bct_func, bct_func, .init = redirect)
{
    char *args[] = {"bct", "1", "5"};
    char *inv1[] = {NULL};
    char *inv2[] = {"bct", "-1", "5"};
    char *inv3[] = {"bct", "1", "-5"};
    server_t server = {0};
    client_node_t *client = malloc(sizeof(client_node_t));
    char output[4096] = {0};

    cr_assert_eq(create_default_server(&server, 4246), SUCCESS);
    client->uuid = generate_uuid();
    client->cfd = STDOUT_FILENO;
    cr_assert_eq(bct_func(&server, NULL, client), FAILURE);
    cr_assert_eq(bct_func(&server, inv1, client), FAILURE);
    cr_assert_eq(bct_func(NULL, args, client), FAILURE);
    cr_assert_eq(bct_func(&server, args, NULL), FAILURE);
    cr_assert_eq(bct_func(&server, inv2, client), FAILURE);
    cr_assert_eq(bct_func(&server, inv3, client), FAILURE);
    cr_assert_eq(bct_func(&server, args, client), SUCCESS);
    sprintf(output, DISPATCH_BCT, 1, 5,
            server.map.tiles[1][5].slots[FOOD].units,
            server.map.tiles[1][5].slots[LINEMATE].units,
            server.map.tiles[1][5].slots[DERAUMERE].units,
            server.map.tiles[1][5].slots[SIBUR].units,
            server.map.tiles[1][5].slots[MENDIANE].units,
            server.map.tiles[1][5].slots[PHIRAS].units,
            server.map.tiles[1][5].slots[THYSTAME].units);
    cr_assert_stdout_eq_str(output);
    destroy_server(&server);
}

Test(msz_func, msz_func, .init = redirect)
{
    server_t server = {0};
    client_node_t *client = malloc(sizeof(client_node_t));
    char output[4096] = {0};

    cr_assert_eq(create_default_server(&server, 4246), SUCCESS);
    client->uuid = generate_uuid();
    client->cfd = STDOUT_FILENO;
    sprintf(output, DISPATCH_MSZ, server.map.size.x, server.map.size.y);
    cr_assert_eq(msz_func(NULL, NULL, NULL), FAILURE);
    cr_assert_eq(msz_func(&server, NULL, NULL), FAILURE);
    cr_assert_eq(msz_func(&server, NULL, client), SUCCESS);
    cr_assert_stdout_eq_str(output);
}
