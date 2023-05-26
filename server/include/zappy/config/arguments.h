/*
** EPITECH PROJECT, 2023
** parse
** File description:
** arguments
*/

#pragma once

#define DEFAULT_FREQ 100
#define DEFAULT_HEIGHT 10
#define DEFAULT_WIDTH 10
#define DEFAULT_TEAMS \
    { \
        "Team1", "Team2", "Team3", "Team3", NULL \
    }
#define DEFAULT_CLIENTS 3

typedef struct vector2i_s {
    int x;
    int y;
} vector2i_t;

/* store arguments information */
/*
    @param port - int
    @param nb clients og - int
    @param world - vector2i
    @param freq - int
    @param team names - char **
*/
typedef struct args_config_s {
    int port;
    vector2i_t world;
    int nb_clients_og;
    int freq;
    char **team_names;
} args_config_t;

int parse_args(args_config_t *args, int argc, char *const argv[]);
