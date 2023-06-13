/*
** EPITECH PROJECT, 2023
** server
** File description:
** tests_eggs
*/

#include "zappy/server/destroy.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <zappy/server.h>
#include <zappy/server/client.h>
#include <zappy/server/map_utils.h>

void redirect(void);
int create_default_server(server_t *server);

Test(add_egg_to_tile, null_tests_egg)
{
    server_t server = {0};
    vector2i_t invalid_pos = {6666666, 896757};

    cr_assert_eq(add_egg_to_tile(NULL, invalid_pos, 0), FAILURE);
    cr_assert_eq(add_egg_to_tile(&server, invalid_pos, 0), FAILURE);
}

Test(create_egg, create_eggs)
{
    server_t server = {0};

    server.teams = NULL;
    cr_assert_eq(create_eggs(NULL), FAILURE);
    cr_assert_eq(create_eggs(&server), FAILURE);
}

Test(add_egg_to_team, add_egg_to_team_null)
{
    client_node_t client = {0};
    server_t server = {0};

    cr_assert_eq(add_egg_to_team(NULL, NULL), FAILURE);
    cr_assert_eq(add_egg_to_team(&client, NULL), FAILURE);
    cr_assert_eq(add_egg_to_team(&client, &server), FAILURE);
}

Test(add_egg_to_team, add_egg_to_team_basic)
{
    client_node_t client = {0};
    server_t server = {0};
    size_t old_nb = 0;

    cr_assert_eq(create_default_server(&server), SUCCESS);
    client.uuid_team = server.teams[0]->uuid;
    old_nb = server.teams[0]->nb_clients;
    cr_assert_eq(add_egg_to_team(&client, &server), SUCCESS);
    cr_assert_eq(server.teams[0]->nb_clients, old_nb + 1);
    destroy_server(&server);
}

Test(delete_egg_from_team, delete_egg_from_team_invalid)
{
    server_t server = {0};

    cr_assert_eq(delete_egg_from_team(NULL, 0), FAILURE);
    cr_assert_eq(delete_egg_from_team(&server, -1), FAILURE);
}

Test(delete_egg_from_team, delete_egg_from_team_valid)
{
    server_t server = {0};

    cr_assert_eq(create_default_server(&server), SUCCESS);
    cr_assert_eq(delete_egg_from_team(&server, 1), SUCCESS);
}

Test(delete_egg_from_team, delete_egg_from_team_invalid_2)
{
    server_t server = {0};

    cr_assert_eq(create_default_server(&server), SUCCESS);
    free(server.teams[0]->eggs);
    server.teams[0]->eggs = NULL;
    cr_assert_eq(delete_egg_from_team(&server, 1), SUCCESS);
}
