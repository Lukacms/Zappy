/*
** EPITECH PROJECT, 2023
** broadcast_func
** File description:
** zappy
*/

#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <zappy/server/summon/utils.h>

static const double DIRECTIONNAL_VECTOR[4] = {{0}, {180}, {90}, {270}};

static const double ANGLES[7][3] = {
    {67.5, 112.5, 7},  {112.5, 157.5, 6}, {157.5, 202.5, 5}, {202.5, 247.5, 4},
    {247.5, 292.2, 3}, {292.2, 337.5, 2}, {22.5, 67.5, 8},
};

static int get_angle(vector2i_t small_vector, client_node_t *client)
{
    double my_angle = ((atan2(small_vector.y, small_vector.x) * 180 / M_PI) +
                       DIRECTIONNAL_VECTOR[client->stats.orientation]) % 360;

    for (int i = 0; i < 8; i += 1) {
        if (my_angle > ANGLES[i][0] && my_angle < ANGLES[i][1])
            return ANGLES[i][2];
    }
    return 1;
}

static int get_oritation(vector2i_t receptor, vector2i_t emittor,
                         vector2i_t map_size, client_node_t *client)
{
    vector2i_t vectors[DIRECTIONNAL] = {
        {.x = emittor.x - receptor.x, .y = emittor.y - receptor.y},
        {.x = emittor.x - (receptor.x + map_size.x),
         .y = emittor.y - receptor.y},
        {.x = emittor.x - receptor.x,
         .y = emittor.y - (receptor.y + map_size.y)},
        {.x = emittor.x - ((-1 * map_size.x) - receptor.x),
         .y = emittor.y - receptor.y},
        {.x = emittor.x - receptor.x,
         .y = emittor.y - ((-1 * map_size.y) + receptor.y)}};
    vector2i_t small_vector = vectors[0];

    for (int i = 1; i < DIRECTIONNAL; i += 1) {
        if (sqrt(pow(vectors[i].x, 2) + pow(vectors[i].y, 2)) <
            sqrt(pow(small_vector.y, 2) + pow(small_vector.y, 2)))
            small_vector = vectors[i];
    }
    return get_angle(small_vector, client);
}

static int get_len(char *args[])
{
    int result = 0;

    for (int i = 1; args[i] != NULL; i += 1) {
        result += strlen(args[i]);
    }
    return result;
}

static void broadcast_message(char *message, client_node_t *list_clients,
                              client_node_t *client, vector2i_t map_size)
{
    client_node_t *tmp_clients = list_clients;

    while (tmp_clients) {
        if (tmp_clients->state == AI && tmp_clients != client) {
            dprintf(tmp_clients->cfd, "%s %i\n", message,
                    get_oritation(tmp_clients->stats.pos, client->stats.pos,
                                  map_size, client));
        }
        if (tmp_clients->state == GUI) {
            dprintf(tmp_clients->cfd, "pbc %s %s\n", client->uuid, message);
        }
        tmp_clients = tmp_clients->next;
    }
}

int broadcast_func(server_t *server, char *args[], client_node_t *client)
{
    int len_message = get_len(args);
    char *message = malloc(sizeof(char) * (len_message + 1));

    message[len_message] = '\0';
    for (int i = 1; args[i] != NULL; i += 1) {
        message = strcat(message, args[i]);
    }
    broadcast_message(message, server->clients.head, client, server->map.size);
    dprintf(client->cfd, "ok");
    return 0;
}
