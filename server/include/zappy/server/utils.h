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
