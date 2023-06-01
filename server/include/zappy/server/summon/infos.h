/*
** EPITECH PROJECT, 2023
** server
** File description:
** summons
*/

#pragma once

#define MAX_WAITING_SUMMONS 10
#define BUFFER_SIZE 4096

#define INVALID_ACTION "ko"
#define UNKNOWN_COMMAND "ko"

typedef struct summon_queue_s {
    char *summon;
    int size;
} summon_queue_t;
