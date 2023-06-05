/*
** EPITECH PROJECT, 2023
** server
** File description:
** infos
*/

#pragma once

#include <netinet/in.h>
#include <stdbool.h>
#include <sys/types.h>
#include <zappy/config/arguments.h>
#include <zappy/server/clock/infos.h>
#include <zappy/server/summon/infos.h>

#define TCP 0
#define ERROR -1

#define MAX_PORT 65535
#define MAX_NAME_LENGTH 32
#define MAX_DESCRIPTION_LENGTH 255
#define MAX_BODY_LENGTH 512

#define INVENTORY_SLOTS 7

static const char __attribute__((unused)) *
    RESOURCES_INVENTORY[INVENTORY_SLOTS] = {
    "food", "linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame",
};

typedef enum resource_s {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME
} resource_t;

typedef enum action_s {
    NOTHING,
    ACTION,
} action_t;

typedef enum orientation_s {
    NORTH,
    SOUTH,
    EAST,
    WEST,
} orientation_t;

typedef enum player_s {
    NONE,
    GUI,
    AI,
} player_t;

typedef struct inventory_s {
    resource_t resource;
    size_t units;
} inventory_t;

typedef struct stats_s {
    struct {
        action_t type;
        int ticks;
    } action;

    size_t level;
    vector2i_t pos;
    size_t vision;
    orientation_t orientation;
    inventory_t inventory[INVENTORY_SLOTS];
} stats_t;

typedef struct client_node_s {
    int cfd;
    char *uuid;
    struct sockaddr_in socket_infos;
    player_t state;
    char *uuid_team;
    stats_t stats;
    summon_queue_t queue[MAX_WAITING_SUMMONS];
    // linked list
    struct client_node_s *prev;
    struct client_node_s *next;
} client_node_t;

typedef struct clients_s {
    client_node_t *head;
    size_t length;
} clients_t;

typedef struct egg_s {
    int nb;
    char *team_uuid;
} egg_t;

typedef struct team_s {
    char *uuid;
    char *team_name;
    char **uuid_clients;
    size_t nb_clients;
    size_t spots_free;
} team_t;

typedef struct tile_s {
    inventory_t slots[INVENTORY_SLOTS];
    char **players_uuid;
    int last_updated;
    egg_t **eggs;
    bool end;
} tile_t;

typedef struct map_s {
    vector2i_t size;
    tile_t **tiles;
    int last_egg_id;
} map_t;

typedef struct server_s {
    bool running;
    ssize_t server_fd;
    struct sockaddr_in socket_infos;
    socklen_t sock_size;
    team_t **teams;
    fd_set clients_fd;
    clients_t clients;
    map_t map;
    zappy_clock_t clock;
} server_t;

typedef int (*cmd_handler_t)(server_t *, char *[], client_node_t *);

typedef struct summons_funptr_s {
    char *summon;
    cmd_handler_t handler;
    player_t type;
} summons_funptr_t;