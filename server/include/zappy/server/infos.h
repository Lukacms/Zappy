/*
** EPITECH PROJECT, 2023
** server
** File description:
** infos
*/

#pragma once

#include <netinet/in.h>
#include <stdbool.h>
#include <sys/select.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <zappy/config/arguments.h>

#define TCP 0
#define ERROR -1

#define MAX_PORT 65535
#define MAX_NAME_LENGTH 32
#define MAX_DESCRIPTION_LENGTH 255
#define MAX_BODY_LENGTH 512

#define INVENTORY_SLOTS 7

#define GUI_INDIC "GRAPHIC\n"

#define ZAPPY_GUI_CONNECT "GRAPHIC"
#define ZAPPY_MSG "msz"
#define ZAPPY_BCT "bct"
#define ZAPPY_TNA "mct"
#define ZAPPY_PNW "tna"
#define ZAPPY_PPO "ppo"
#define ZAPPY_PLV "plv"
#define ZAPPY_PIN "pin"
#define ZAPPY_SGT "sgt"
#define ZAPPY_SST "sst"

#define ZAPPY_FORWARD "Forward"
#define ZAPPY_RIGHT "Right"
#define ZAPPY_LEFT "Left"
#define ZAPPY_LOOK "Look"
#define ZAPPY_INVENTORY "Inventory"
#define ZAPPY_CONNECT_NBR "Connect_nbr"

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
    RITUAL,
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
    action_t action;
    size_t level;
    vector2i_t pos;
    size_t vision;
    orientation_t orientation;
    inventory_t inventory[INVENTORY_SLOTS];
} stats_t;

typedef struct client_node_s {
    int cfd;
    char *uuid;
    player_t state;
    char *uuid_team;
    stats_t stats;
    // linked list
    struct client_node_s *prev;
    struct client_node_s *next;
} client_node_t;

typedef struct clients_s {
    client_node_t *head;
    size_t length;
} clients_t;

typedef struct team_s {
    char *uuid;
    char **uuid_clients;
    size_t nb_clients;
} team_t;

// TODO need to add other elements to the map to complete it
typedef struct map_s {
    vector2i_t size;
    inventory_t **inventory[INVENTORY_SLOTS];
    // tile_t **tiles;
    // NOTE implement this structure, and size is determined by size element
} map_t;

typedef struct server_s {
    bool running;
    ssize_t server_fd;
    struct protoent *proto;
    struct sockaddr_in socket_infos;
    socklen_t sock_size;
    fd_set clients_fd;
    clients_t clients;
    team_t **teams;
    map_t map;
    u_int64_t time;
} server_t;

typedef int (*cmd_handler_t)(server_t *server, char *args[], client_node_t *client);

typedef struct summons_funptr_s {
    char *summon;
    cmd_handler_t handler;
    player_t type;
} summons_funptr_t;
