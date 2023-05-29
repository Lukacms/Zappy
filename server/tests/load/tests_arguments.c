/*
** EPITECH PROJECT, 2023
** load
** File description:
** tests_arguments
*/

#include <criterion/criterion.h>
#include <criterion/internal/test.h>
#include <zappy/config/arguments.h>
#include <zappy/server.h>

Test(parse_args, basic_test)
{
    args_config_t args = {0};
    char *const argv[] = {"i"};

    cr_assert_eq(parse_args(&args, 1, argv), SUCCESS);
    cr_assert_eq(args.port, 4242);
    cr_assert_eq(args.nb_clients_og, DEFAULT_CLIENTS);
}
