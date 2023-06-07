/*
** EPITECH PROJECT, 2023
** server
** File description:
** summons
*/

#pragma once

#define MAX_WAITING_SUMMONS 10
#define BUFFER_SIZE 4096
#define SEPARATOR_CMD " \t\r\n"

#define CLIENT_CONNECT "WELCOME\n"

#define INVALID_ACTION "ko\n"
#define UNKNOWN_COMMAND "ko\n"

#define GUI_INDIC "GRAPHIC\n"
#define GUI_UNKNOWN "suc\n"

#define GO_LEVEL_2 "1100000"
#define GO_LEVEL_3 "2111000"
#define GO_LEVEL_4 "2201020"
#define GO_LEVEL_5 "4112010"
#define GO_LEVEL_6 "4121300"
#define GO_LEVEL_7 "6123010"
#define GO_LEVEL_8 "6222221"

/* summons of GUIs */
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

/* summons of AIs */
#define ZAPPY_FORWARD "Forward"
#define ZAPPY_RIGHT "Right"
#define ZAPPY_LEFT "Left"
#define ZAPPY_LOOK "Look"
#define ZAPPY_INVENTORY "Inventory"
#define ZAPPY_CONNECT_NBR "Connect_nbr"

/* delay for summons of AIs */
#define RESTRAINT_FORWARD 7
#define RESTRAINT_RIGHT 7
#define RESTRAINT_LEFT 7
#define RESTRAINT_LOOK 7
#define RESTRAINT_INVENTORY 1
#define RESTRAINT_BROADCAST 7
#define RESTRAINT_FORK 42
#define RESTRAINT_EJECT 7
#define RESTRAINT_TAKE 7
#define RESTRAINT_SET 7
#define RESTRAINT_INCANTATION 300

typedef struct summon_queue_s {
    char *summon;
    int size;
} summon_queue_t;
