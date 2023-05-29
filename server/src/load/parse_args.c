/*
** EPITECH PROJECT, 2023
** load
** File description:
** parse_args
*/

#include <unistd.h>
#include <zappy/config/arguments.h>
#include <zappy/server.h>

static const flag_handler_binder_t OPTIONS[] = {
    {.cases = 'p', .handler = &p_handler},
    {.cases = 'x', .handler = &x_handler},
    {.cases = 'y', .handler = &y_handler},
    {.cases = 'n', .handler = &n_handler},
    {.cases = 'c', .handler = &c_handler},
    {.cases = 'h', .handler = &h_handler},
    {.cases = 'f', .handler = &f_handler},
    {0},
};

static int fill_args(args_config_t *args, char *const argv[], int opt, int argc)
{
    for (unsigned int i = 0; OPTIONS[i].cases; i++) {
        if (OPTIONS[i].cases == opt) {
            return OPTIONS[i].handler(args, argv, argc);
        }
    }
    return FAILURE;
}

int parse_args(args_config_t *args, int argc, char *const argv[])
{
    int opt = 0;

    if (!args || !argv)
        return FAILURE;
    while ((opt = getopt(argc, argv, SHORT_ARGS)) != -1) {
        if (opt == '?')
            return FAILURE;
        if (fill_args(args, argv, opt, argc) != SUCCESS)
            return FAILURE;
    }
    if (optind != argc)
        return FAILURE;
    return SUCCESS;
}
