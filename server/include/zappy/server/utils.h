/*
** EPITECH PROJECT, 2023
** server
** File description:
** utils
*/

#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <sys/types.h>
#include <zappy/server/infos.h>

#define QUOTATION "\""

ssize_t array_len(void *to_size);
int char_in_str(const char *str, char to_find);
void free_array(void *to_del);
char *generate_uuid(void);
int print_help(int ret_value);
int set_error(int fileno, char *str, bool perr);
bool strisnum(const char *str);
char *strndup_quotes(char *src, size_t n);
char **str_to_array(char *src, char *delim);
char **realloc_array(char **ptr, u_int y, u_int x);


int send_toall_guicli(server_t *server, char *str, ...);
void dprint_tile(map_t map, size_t cord_x, size_t cord_y,
                        client_node_t *client);

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
int connect_nbr_func(server_t *server, char *args[], client_node_t *client);
