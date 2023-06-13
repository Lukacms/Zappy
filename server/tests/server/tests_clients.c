/*
** EPITECH PROJECT, 2023
** server
** File description:
** tests_clients
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <fcntl.h>
#include <zappy/server.h>
#include <zappy/server/client.h>
#include <zappy/server/destroy.h>

void redirect(void);
int create_default_server(server_t *server, int port);

Test(add_client_node, add_client_node)
{
    server_t server = {0};
    client_node_t client = {0};
    client_node_t next_client = {0};

    client.next = &client;
    client.prev = &client;
    cr_assert_eq(add_client_node(NULL, NULL), FAILURE);
    cr_assert_eq(add_client_node(&client, &server), SUCCESS);
    cr_assert_eq(add_client_node(&next_client, &server), SUCCESS);
    cr_assert_eq(&client, server.clients.head);
}

Test(find_client_by_uuid, find_client_by_uuid)
{
    server_t server = {0};
    client_node_t client = {0};

    client.uuid = "ouep";
    cr_assert_null(find_client_by_uuid(NULL, NULL));
    cr_assert_null(find_client_by_uuid("gné", NULL));
    cr_assert_null(find_client_by_uuid("gné", &server));
    cr_assert_eq(add_client_node(&client, &server), SUCCESS);
    cr_assert_null(find_client_by_uuid("gné", &server));
    cr_assert_not_null(find_client_by_uuid("ouep", &server));
}

Test(find_client_by_fd, find_client_by_fd)
{
    server_t server = {0};
    client_node_t client = {0};

    client.cfd = 7;
    cr_assert_null(find_client_by_fd(-1, NULL));
    cr_assert_null(find_client_by_fd(-1, NULL));
    cr_assert_null(find_client_by_fd(-1, &server));
    cr_assert_eq(add_client_node(&client, &server), SUCCESS);
    cr_assert_null(find_client_by_fd(-1, &server));
    cr_assert_not_null(find_client_by_fd(7, &server));
}

Test(connect_new_client, connect_new_client)
{
    cr_assert_eq(connect_new_client(NULL), FAILURE);
}

Test(kill_player, kill_player)
{
    server_t server = {0};
    client_node_t *client = malloc(sizeof(client_node_t));

    cr_assert_eq(kill_player(NULL, NULL), FAILURE);
    cr_assert_eq(kill_player(&server, NULL), FAILURE);
    cr_assert_eq(create_default_server(&server, 4241), SUCCESS);
    client->cfd = open("./tmp", O_CREAT | O_TRUNC | O_RDWR);
    cr_assert_eq(add_client_node(client, &server), SUCCESS);
    cr_assert_eq(kill_player(&server, client), SUCCESS);
    cr_assert_null(server.clients.head);
    remove("./tmp");
    destroy_server(&server);
}

Test(starve_players, starve_players_invalid)
{
    server_t server = {0};

    cr_assert_eq(starve_players(NULL), FAILURE);
    cr_assert_eq(starve_players(&server), FAILURE);
}

Test(starve_players, starve_players)
{
    server_t server = {0};
    client_node_t *client = malloc(sizeof(client_node_t));

    cr_assert_eq(create_default_server(&server, 4243), SUCCESS);
    client->cfd = open("./tmp", O_CREAT | O_TRUNC | O_RDWR);
    cr_assert_eq(add_client_node(client, &server), SUCCESS);
    cr_assert_eq(starve_players(&server), SUCCESS);
    client->stats.inventory[FOOD].units = 1;
    client->state = AI;
    cr_assert_eq(starve_players(&server), SUCCESS);
    cr_assert_eq(client->stats.inventory[FOOD].units, 0);
    cr_assert_eq(starve_players(&server), SUCCESS);
    cr_assert_null(server.clients.head);
    remove("./tmp");
    destroy_server(&server);
}
