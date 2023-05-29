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

int f_handler(args_config_t *args, char __attribute__((unused)) *const argv[],
              int __attribute__((unused)) argc)
{
    if (!strisnum(optarg))
        return FAILURE;
    if ((args->freq = atoi(optarg)) <= 0)
        return FAILURE;
    return SUCCESS;
}
