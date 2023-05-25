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

#define TCP 0
#define ERROR -1

#define MAX_PORT 65535
#define MAX_NAME_LENGTH 32
#define MAX_DESCRIPTION_LENGTH 255
#define MAX_BODY_LENGTH 512

#define INVENTORY_SLOTS 7

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

typedef struct inventory_s {
    resource_t resource;
    size_t units;
} inventory_t;

typedef struct stats_s {
    action_t action;
    size_t level;
    vector2i_t pos;
    size_t vision;
    inventory_t inventory[INVENTORY_SLOTS];
} stats_t;

typedef struct client_node_s {
    int cfd;
    char *uuid;
    char *uuid_team;
    stats_t stats;
    // linked list
    struct client_s *prev;
    struct client_s *next;
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

typedef struct server_s {
    bool running;
    ssize_t server_fd;
    struct protoent *proto;
    struct sockaddr_in socket_infos;
    socklen_t sock_size;
    fd_set clients_fd;
    clients_t clients;
} server_t;
