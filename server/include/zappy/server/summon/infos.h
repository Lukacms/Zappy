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
#define GUI_INDIC "GRAPHIC\n"

#define GO_LEVEL_2 "1100000"
#define GO_LEVEL_3 "2111000"
#define GO_LEVEL_4 "2201020"
#define GO_LEVEL_5 "4112010"
#define GO_LEVEL_6 "4121300"
#define GO_LEVEL_7 "6123010"
#define GO_LEVEL_8 "6222221"

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

typedef struct summon_queue_s {
    char *summon;
    int size;
} summon_queue_t;
