/*
** EPITECH PROJECT, 2023
** server
** File description:
** clock
*/

#pragma once

#include <time.h>

typedef struct zappy_clock_s {
    struct timespec value;
    int freq;
} zappy_clock_t;

int gettickselapsed(zappy_clock_t *clock);
