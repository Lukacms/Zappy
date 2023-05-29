/*
** EPITECH PROJECT, 2023
** options
** File description:
** x_handler
*/

#include <stdlib.h>
#include <unistd.h>
#include <zappy/config/arguments.h>
#include <zappy/server.h>
#include <zappy/server/utils.h>

int x_handler(args_config_t *args, char __attribute__((unused)) *const argv[],
              int __attribute__((unused)) argc)
{
    if (!strisnum(optarg))
        return FAILURE;
    if ((args->world.x = atoi(optarg)) <= 0)
        return FAILURE;
    return SUCCESS;
}
