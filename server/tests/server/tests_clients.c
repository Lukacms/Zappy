/*
** EPITECH PROJECT, 2023
** server
** File description:
** tests_clients
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <zappy/server.h>
#include <zappy/server/client.h>

void redirect(void);
int create_default_server(server_t *server);

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
