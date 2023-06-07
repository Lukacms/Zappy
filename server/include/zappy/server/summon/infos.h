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

/* command to send to GUIs */
// map size
#define DISPATCH_MSZ "msz %d %d\n"
// content of a tile
#define DISPATCH_BCT "bct %d %d %d %d %d %d %d %d %d\n"
// name of all a team
#define DISPATCH_TNA "tna %d\n"
// connection of a new player
#define DISPATCH_PNW "pnw #%d %d %d %d %d %d\n"
// player’s position
#define DISPATCH_PPO "ppo %d %d %d %d\n"
// player’s level
#define DISPATCH_PLV "plv %d\n"
// player’s inventory
#define DISPATCH_PIN "pin %d %d %d %d %d %d %d %d %d %d\n"
// expulsion
#define DISPATCH_PEX "pex %d\n"
// broadcast
#define DISPATCH_PBC "pbc %d %s\n"
// start of an incantation (by first player)
#define DISPATCH_PIC "pic %d %d %d %d %d\n"
// end of an incantation
#define DISPATCH_PIE "pie %d %d %s\n"
// egg laying by the player
#define DISPATCH_PFK "pfk %d\n"
// resource dropping
#define DISPATCH_PDR "pdr %d %d\n"
// resource collecting
#define DISPATCH_PGT "pgt %d %d\n"
// death of a player
#define DISPATCH_PDI "pdi %d\n"
// an egg was laid by a player
#define DISPATCH_ENW "enw %d %d %d %d\n"
// player connection for an egg
#define DISPATCH_EBO "ebo %d\n"
// death of an egg
#define DISPATCH_EDI "edi %d\n"
// time unit request
#define DISPATCH_SGT "sgt %d\n"
// time unit modification
#define DISPATCH_SST "sst %d\n"
// end of game
#define DISPATCH_SEG "seg %d\n"
// message from the server
#define DISPATCH_SMG "smg %s\n"
// unknown command
#define DISPATCH_SUC "suc\n"
// command parameter
#define DISPATCH_SBP "sbp\n"

typedef struct summon_queue_s {
    char *summon;
    int size;
} summon_queue_t;
