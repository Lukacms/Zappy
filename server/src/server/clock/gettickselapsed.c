/*
** EPITECH PROJECT, 2023
** clock
** File description:
** gettickselapsed
*/

#include <stdio.h>
#include <time.h>
#include <zappy/server/clock.h>

int gettickselapsed(zappy_clock_t *clock)
{
    double ticks = 0;
    struct timespec new_val = {0};

    clock_gettime(CLOCK_MONOTONIC, (struct timespec *)&new_val);
    ticks = (new_val.tv_sec - clock->value.tv_sec) +
        (new_val.tv_nsec - clock->value.tv_nsec) * 1e-9;
    return ticks * clock->freq;
}
