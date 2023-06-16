##
## EPITECH PROJECT, 2023
## zappy
## File description:
## Ai
##

import socket
from ai.src.client.Commands import Commands

RESOURCES = ['food', 'linemate', 'deraumere', 'sibur', 'mendiane', 'phiras', 'thystame']
ELEVATION_RITUAL = {
    1: {'linemate' : 1},
    2: {'linemate' : 1, 'deraumere' : 1, 'sibur' : 1},
    3: {'linemate' : 2, 'sibur' : 1, 'phiras' : 2},
    4: {'linemate' : 1, 'deraumere' : 1, 'sibur' : 2, 'phiras' : 1},
    5: {'linemate' : 1, 'deraumere' : 2, 'sibur' : 1, 'mendiane' : 3},
    6: {'linemate' : 1, 'deraumere' : 2, 'sibur' : 3, 'phiras' : 1},
    7: {'linemate' : 2, 'deraumere' : 2, 'sibur' : 2, 'mendiane' : 2, 'phiras' : 2, 'thystame' : 1},
    }


class Artifical_intelligence():
    def __init__(self, team_name: str):
        self.inventory = {'food' : 0, 'linemate' : 0, 'deraumere' : 0, 'sibur' : 0, 'mendiane' : 0, 'phiras' : 0, 'thystame' : 0}
        self.broadcast_text = ""
        self.look = {}
        self.level = 2
        self.nb_player = 1
        self.life_units = 10
        self.connect_nbr = 0
        self.team_name = team_name
        self.previous_action = ""
        self.action_to_do = ""
        self.object_to_take = ""
        self.commands = Commands()
        self.alone_on_tile = False
        self.direction = []

    def check_if_alone(self, socket) -> bool:
        self.commands.look(socket, self.look)
        if "player" in self.look[0]:
            # self.check_if_object(socket)
            self.alone_on_tile = True
        else:
            self.alone_on_tile = False
        return self.alone_on_tile

    def check_if_object(self, socket) -> bool:
        for item in RESOURCES:
            if item in self.look[0]:
                # self.object_needed(socket)
                return True
        return False

    def object_wanted(self, socket) -> bool:
        if self.object_to_take in self.look[0]:
            self.action_to_do = self.commands.take_object(self.object_to_take)
            self.inventory[self.object_to_take] += 1
            return True
        else:
            # self.object_needed(socket)
            return False

    def object_needed(self, socket) -> bool:
        self.commands.parse_inventory(socket, self.inventory)
        for item in ELEVATION_RITUAL[self.level].keys():
            if item in self.look[0] and item != self.object_to_take and self.inventory[item] < ELEVATION_RITUAL[self.level][item]:
                self.action_to_do = self.commands.take_object(item)
                self.inventory[item] += 1
                return True
        # self.programmed_action(socket)
        return False

##############################################
    def programmed_action(self, socket) -> bool:
        if len(self.direction) == 0:
            self.commands.parse_inventory(socket, self.inventory)
            self.requirements_analysis()
            return False
        else:
            if self.direction[0] == "forward":
                self.commands.move_forward()
            elif self.direction[0] == "left":
                self.commands.turn_left()
            else:
                self.commands.turn_right()
            self.direction.pop(0)
            return True
##############################################

    def requirements_analysis(self):
        print("+++++")

    def decision_to_steal_object(self, socket) -> bool:
        if self.object_needed(socket) == True:
            return True
        else:
            self.commands.eject()
            return False

    def check_if_incantation(self, socket) -> bool:
        nb_player = self.look[0].count("player")
        nb_linemate = self.look[0].count("linemate")
        nb_sibur = self.look[0].count("sibur")
        if nb_player >= 2 and nb_linemate >= 2 and nb_sibur >= 2:
            self.decision_to_steal_object(socket)
            return True
        return False

    def check_if_evolution(self, socket) -> bool:
        self.commands.parse_inventory(socket, self.inventory)
        for item in ELEVATION_RITUAL[self.level].keys():
            if self.inventory[item] != ELEVATION_RITUAL[self.level][item] or self.inventory['food'] < 400:
                return False
        return True

    def algo(self, socket: socket.socket):
        if self.alone_on_tile() == True:
            print("alone")
        return self.action_to_do