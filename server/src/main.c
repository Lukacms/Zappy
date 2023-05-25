/*
** EPITECH PROJECT, 2023
** src
** File description:
** main
*/

#include <zappy/config/arguments.h>
#include <zappy/server.h>

int main(int argc, char *const argv[])
{
    args_config_t args = {0};

    if (parse_args(&args, argc, argv) != SUCCESS)
        return FAILURE;
    return launch(&args);
}
