/*
** EPITECH PROJECT, 2023
** tests
** File description:
** launch
*/

#include <criterion/criterion.h>
#include <criterion/internal/redirect.h>
#include <zappy/config/config.h>
#include <zappy/server.h>

void redirect(void);

Test(create_server, null_arguments)
{
    cr_assert_eq(create_server(NULL, NULL), FAILURE);
}

Test(create_server, null_args)
{
    server_t server = {0};

    cr_assert_eq(create_server(&server, NULL), FAILURE);
}
