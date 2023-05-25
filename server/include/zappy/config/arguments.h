/*
** EPITECH PROJECT, 2023
** parse
** File description:
** arguments
*/

#pragma once

typedef struct vector2i_s {
    int x;
    int y;
} vector2i_t;

/* store arguments information */
typedef struct args_config_s {
    int port;
    vector2i_t world;
    int nb_clients_og;
    int freq;
    char **team_names;
} args_config_t;

int parse_args(args_config_t *args, int argc, char *const argv[]);
