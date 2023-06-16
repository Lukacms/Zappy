##
## EPITECH PROJECT, 2023
## zappy
## File description:
## Ai
##

import socket
import random
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
        self.prog_action = dict(dict(str))
        self.object_to_take = ""
        self.commands = Commands()

    def check_if_alone(self, socket) -> bool:
        self.commands.look(socket, self.look)
        if "player" in self.look[0]:
            return False
        self.check_if_object(socket)
        return True

    def check_if_object(self, socket) -> None:
        self.commands.parse_inventory(socket, self.inventory)
        print(self.inventory)
        for item in RESOURCES:
            if item == "food" and self.inventory[item] < 450:
                self.prog_action.append(self.commands.take_object(item))
                self.inventory[item] += 126
                return
            if item in self.look[0]:
                if self.object_needed(socket, 0) == True:
                    return
        # self.requirements_analysis(socket)

    def object_needed(self, socket, value) -> bool:
        self.commands.parse_inventory(socket, self.inventory)
        for item in ELEVATION_RITUAL[self.level].keys():
            if item in self.look[value] and item != self.object_to_take and self.inventory[item] < ELEVATION_RITUAL[self.level][item]:
                self.prog_action.append(self.commands.take_object(item))
                self.inventory[item] += 1
                return True
        self.requirements_analysis(socket)
        return False

    def decision_to_steal_object(self, socket) -> None:
        if self.object_needed(socket, 0) == True:
            return
        else:
            self.commands.eject()

    def check_if_incantation(self, socket) -> bool:
        nb_player = self.look[0].count("player")
        nb_linemate = self.look[0].count("linemate")
        nb_sibur = self.look[0].count("sibur")
        if nb_player >= 2 and nb_linemate >= 2 and nb_sibur >= 2:
            self.decision_to_steal_object(socket)
            return True
        return False

    def check_if_evolution(self, socket) -> None:
        for item in ELEVATION_RITUAL[self.level].keys():
            if self.inventory[item] < ELEVATION_RITUAL[self.level][item] or self.inventory['food'] < 450:
                self.requirements_analysis(socket)
                return
        for item in ELEVATION_RITUAL[self.level].keys():
            self.prog_action.append(self.commands.set_object_down(item))
            self.inventory[item] -= 1
        self.prog_action.append(self.commands.incantation())

# A VERIFIER APRES LE MERGE
    def track_objcet(self, socket) -> bool:
        y = 0
        x = 0
        for tile in range(len(self.look)):
            if (self.object_needed(socket, tile) == True):
                for yidx in range(y):
                    self.prog_action.append(self.commands.move_forward())
                if (x < 0):
                    self.prog_action.append(self.commands.turn_left())
                    x = x * -1
                    for xidx in range(x):
                        self.prog_action.append(self.commands.move_forward())
                    return True
                if (x > 0):
                    self.prog_action.append(self.commands.turn_right())
                    for xidx in range(x):
                        self.prog_action.append(self.commands.move_forward())
                return True
            if (y == x):
                y += 1
                x = y * -1
            else:
                x += 1
        return False

    def requirements_analysis(self, socket) -> None:
        nb_player = self.commands.nb_player_in_team(socket)
        if nb_player < 4 and random.randint(1, 10) >= 5:
            self.prog_action.append(self.commands.fork())
            return
        if nb_player < 8 and random.randint(1, 10) >= 8:
            self.prog_action.append(self.commands.fork())
            return
        if self.track_objcet(socket) == True:
            self.prog_action.append(self.commands.turn_left())
            return

    def algo(self, socket: socket.socket):
        if (self.prog_action == empty):
            self.commands.look(socket, self.look)
            if (self.look[0] == "player"):
                requirements_analysis(self, socket)
            self.check_if_object(socket)
        self.action_to_do = self.prog_action.pop_front()
        # if self.check_if_alone(socket) == False:
        #     if self.check_if_incantation(socket) == True:
        #         self.decision_to_steal_object(socket)
        #     else:
        #         self.check_if_evolution(socket)
        return self.action_to_do
