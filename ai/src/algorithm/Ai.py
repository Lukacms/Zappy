##
## EPITECH PROJECT, 2023
## zappy
## File description:
## Ai
##

import socket
from ai.src.client.Commands import Commands

# RESOURCES = ['food', 'linemate', 'deraumere', 'sibur', 'mendiane', 'phiras', 'thystame']
# ELEVATION_RITUAL = {
#     1: {'linemate' : 1},
#     2: {'linerame' : 1, 'deraumere' : 1, 'sibur' : 1},
#     3: {'linemate' : 2, 'sibur' : 1, 'phiras' : 2},
#     4: {'linemate' : 1, 'deraumere' : 1, 'sibur' : 2, 'phiras' : 1},
#     5: {'linemate' : 1, 'deraumere' : 2, 'sibur' : 1, 'mendiane' : 3},
#     6: {'linemate' : 1, 'deraumere' : 2, 'sibur' : 3, 'phiras' : 1},
#     7: {'linemate' : 2, 'deraumere' : 2, 'sibur' : 2, 'mendiane' : 2, 'phiras' : 2, 'thystame' : 1},
#     }


class Artifical_intelligence():
    def __init__(self, team_name: str):
        self.inventory = {'food' : 0, 'linemate' : 0, 'deraumere' : 0, 'sibur' : 0, 'mendiane' : 0, 'phiras' : 0, 'thystame' : 0}
        self.broadcast_text = ""
        self.look = {}
        self.level = 1
        self.nb_player = 1
        self.life_units = 10
        self.connect_nbr = 0
        self.team_name = team_name
        self.previous_action = ""
        self.action_to_do = ""
        self.object_to_take = ""
        self.commands = Commands()

    def algo(self, socket: socket.socket):
        self.commands.parse_inventory(socket, self.inventory)
        self.action_to_do = self.commands.look(socket, self.look)
        return self.action_to_do