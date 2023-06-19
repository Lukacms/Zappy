/*
** EPITECH PROJECT, 2023
** options
** File description:
** c_handler
*/

#include <stdlib.h>
#include <unistd.h>
#include <zappy/config/arguments.h>
#include <zappy/server.h>
#include <zappy/server/utils.h>

int c_handler(args_config_t *args, char *const argv[],
              int __attribute__((unused)) argc)
{
    if (!strisnum(argv[optind]))
        return set_error(STDERR_FILENO, ERROR_CLIENTS, false);
    if ((args->port = atoi(argv[optind])) <= 0)
        return set_error(STDERR_FILENO, ERROR_CLIENTS, false);
    optind++;
    return SUCCESS;
}
