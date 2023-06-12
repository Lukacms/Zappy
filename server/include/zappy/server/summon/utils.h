/*
** EPITECH PROJECT, 2023
** server
** File description:
** summons
*/

#pragma once

#include <zappy/server/infos.h>

int add_summon(char *summon, client_node_t *client);
char *pop_summon(client_node_t *client);
int get_summon(server_t *server, client_node_t *client);
int handle_summon(server_t *server, int cfd);

int send_toall_guicli(server_t *server, char *str, ...);
void dprint_tile(map_t, size_t, size_t, client_node_t *);

int parse_event_client(server_t *, const char *, client_node_t *);

/* IA funptr */
int forward_north(server_t *server, client_node_t *client);
int forward_south(server_t *server, client_node_t *client);
int forward_east(server_t *server, client_node_t *client);
int forward_west(server_t *server, client_node_t *client);

/* GUI funptr */
int gui_connect_func(server_t *server, char *args[], client_node_t *client);
int msz_func(server_t *server, char *args[], client_node_t *client);
int bct_func(server_t *server, char *args[], client_node_t *client);
int mct_func(server_t *server, char *args[], client_node_t *client);
int tna_func(server_t *server, char *args[], client_node_t *client);
int ppo_func(server_t *server, char *args[], client_node_t *client);
int plv_func(server_t *server, char *args[], client_node_t *client);
int pin_func(server_t *server, char *args[], client_node_t *client);
int sgt_func(server_t *server, char *args[], client_node_t *client);
int sst_func(server_t *server, char *args[], client_node_t *client);

int forward_func(server_t *server, char *args[], client_node_t *client);
int right_func(server_t *server, char *args[], client_node_t *client);
int left_func(server_t *server, char *args[], client_node_t *client);
int look_func(server_t *server, char *args[], client_node_t *client);
int inventory_func(server_t *server, char *args[], client_node_t *client);
int broadcast_func(server_t *server, char *args[], client_node_t *client);
int connect_nbr_func(server_t *server, char *args[], client_node_t *client);
int eject_func(server_t *server, char *args[], client_node_t *client);
int take_func(server_t *server, char *args[], client_node_t *client);
int set_func(server_t *server, char *args[], client_node_t *client);
int incantation_func(server_t *server, char *args[], client_node_t *client);
int fork_func(server_t *server, char *args[], client_node_t *client);
