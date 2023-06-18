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
    1: {'player' : 1, 'food' : 9, 'linemate' : 1},
    2: {'player' : 2, 'food' : 9, 'linemate' : 1, 'deraumere' : 1, 'sibur' : 1},
    3: {'player' : 2, 'food' : 9, 'linemate' : 2, 'sibur' : 1, 'phiras' : 2},
    4: {'player' : 4, 'food' : 9, 'linemate' : 1, 'deraumere' : 1, 'sibur' : 2, 'phiras' : 1},
    5: {'player' : 4, 'food' : 9, 'linemate' : 1, 'deraumere' : 2, 'sibur' : 1, 'mendiane' : 3},
    6: {'player' : 6, 'food' : 9, 'linemate' : 1, 'deraumere' : 2, 'sibur' : 3, 'phiras' : 1},
    7: {'player' : 6, 'food' : 9, 'linemate' : 2, 'deraumere' : 2, 'sibur' : 2, 'mendiane' : 2, 'phiras' : 2, 'thystame' : 1},
    }
ITEM_VALUE = {'player' : -5, 'food' : 3, 'linemate' : 1, 'deraumere' : 2, 'sibur' : 3, 'mendiane' : 4, 'phiras' : 5, 'thystame' : 6}
BUFFER_SIZE = 1024

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
        self.prog_action = []
        self.go_levelup = False
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
        for item in ELEVATION_RITUAL[self.level].keys():
            if "player" not in item and \
            item in self.look[value] and \
                self.inventory[item] < ELEVATION_RITUAL[self.level][item]:
                #self.prog_action.append(self.commands.take_object(item))
                #self.inventory[item] += 1
                return True
        return False

    def get_object(self, value) -> bool:
        for item in self.look[value].split(' '):
            if (item != 'player'):
                self.prog_action.append(self.commands.take_object(item))
                #if (item == 'food'):
                #    self.inventory[item] += 125
                #self.inventory[item] += 1
        return True

    def decision_to_steal_object(self, socket) -> None:
        if self.object_needed(socket, 0) == True:
            return get_object(socket, 0)
        else:
            self.commands.eject()


# A VERIFIER APRES LE MERGE
# evolution / incatation

    def check_if_incantation(self, socket) -> bool:
        nb_player = self.look[0].count("player")
        nb_linemate = self.look[0].count("linemate")
        nb_sibur = self.look[0].count("sibur")
        if nb_player >= 2 and nb_linemate >= 2 and nb_sibur >= 2:
            self.decision_to_steal_object(socket)
            return True
        return False

    def turn_to_broadcast(self, socket, direction: int):
        self.prog_action = []
        self.look = {}
        self.go_levelup = True
        if (direction == 0):
            self.level_up(socket)
        if (direction == 1):
            self.prog_action.append(self.commands.move_forward())
            self.prog_action.append("Look")
            return
        if (direction == 2):
            self.prog_action.append(self.commands.move_forward())
            self.prog_action.append(self.commands.turn_left())
            self.prog_action.append(self.commands.move_forward())
            self.prog_action.append("Look")
            return
        if (direction == 3):
            self.prog_action.append(self.commands.turn_left())
            self.prog_action.append(self.commands.move_forward())
            self.prog_action.append("Look")
            return
        if (direction == 4):
            self.prog_action.append(self.commands.turn_left())
            self.prog_action.append(self.commands.move_forward())
            self.prog_action.append(self.commands.turn_left())
            self.prog_action.append(self.commands.move_forward())
            self.prog_action.append("Look")
            return
        if (direction == 5):
            self.prog_action.append(self.commands.turn_left())
            self.prog_action.append(self.commands.turn_left())
            self.prog_action.append(self.commands.move_forward())
            self.prog_action.append("Look")
            return
        if (direction == 6):
            self.prog_action.append(self.commands.turn_right())
            self.prog_action.append(self.commands.move_forward())
            self.prog_action.append(self.commands.turn_right())
            self.prog_action.append(self.commands.move_forward())
            self.prog_action.append("Look")
            return
        if (direction == 7):
            self.prog_action.append(self.commands.turn_right())
            self.prog_action.append(self.commands.move_forward())
            self.prog_action.append("Look")
            return
        if (direction == 8):
            self.prog_action.append(self.commands.move_forward())
            self.prog_action.append(self.commands.turn_right())
            self.prog_action.append(self.commands.move_forward())
            self.prog_action.append("Look")
            return

    def level_up(self, socket):
        self.look = {}
        res = socket.recv(BUFFER_SIZE).decode("utf-8")
        while "message" in res or "ok" in res:
            res = socket.recv(BUFFER_SIZE).decode("utf-8")
        print(res)
        if "ko" in res:
            return
        self.level = int(res.split(':')[1].strip())

    def check_if_evolution(self, socket) -> bool:
        if self.inventory['food'] < 8 or self.look == {}:
            self.look == {}
            return False
        for item in ELEVATION_RITUAL[self.level].keys():
            if "player" in item:
                continue
            if self.inventory[item] < ELEVATION_RITUAL[self.level][item]:
                return False
                #self.broadcast_text = "I need " + item
                #self.prog_action.append(self.commands.broadcast())
        if self.look[0].count("player") < ELEVATION_RITUAL[self.level]["player"]:
            self.prog_action.append(self.commands.broadcast(self.team_name ,"evolution" + str(self.level)))
            return True
        for item in ELEVATION_RITUAL[self.level].keys():
            if "food" not in item and \
                "player" not in item and \
                    self.inventory[item] >= ELEVATION_RITUAL[self.level][item]:
                for tmp in range(ELEVATION_RITUAL[self.level][item]):
                    self.prog_action.append(self.commands.set_object(item))
                    self.inventory[item] -= 1
        self.prog_action.append(self.commands.incantation())
        return True

# Récuperation d'obj necessaire + Fork si pas de player

    def go_track_obj(self, tile, x, y) -> bool:
        for yidx in range(y):
            self.prog_action.append(self.commands.move_forward())
        if (x < 0):
            self.prog_action.append(self.commands.turn_left())
            x = x * -1
            for xidx in range(x):
                self.prog_action.append(self.commands.move_forward())
            return self.get_object(tile)
        if (x > 0):
            self.prog_action.append(self.commands.turn_right())
            for xidx in range(x):
                self.prog_action.append(self.commands.move_forward())
        return self.get_object(tile)

    def track_obj_set(self, socket) -> bool:
        y = 0
        x = 0
        max_y = 0
        max_x = 0
        max_tile = 0
        value = 0
        value_tmp = 0
        for tile in range(len(self.look)):
            if (self.object_needed(socket, tile) == True):
                return self.go_track_obj(tile, x, y)
            value_tmp = 0
            for item in self.look[tile].split(' '):
                if item != '':
                    value_tmp += ITEM_VALUE[item]
            if value_tmp > value:
                value = value_tmp
                max_y = y
                max_x = x
                max_tile = tile
            if (y == x):
                y += 1
                x = y * -1
            else:
                x += 1
        if max_tile == 0:
            return False
        return self.go_track_obj(max_tile, max_x, max_y)

    def requirements_analysis(self, socket) -> None:
        nb_player = self.commands.nb_player_in_team(socket)
        if (nb_player < 8 and random.randint(1, 10) >= 8):
            self.prog_action.append(self.commands.fork())
            return
        if self.track_obj_set(socket) == False:
            print("N/A")
            self.prog_action.append(self.commands.move_forward())

    def track_object(self, socket) -> None:
        print("Analysis")
        self.requirements_analysis(socket)
        self.action_to_do = self.prog_action[0]
        self.prog_action = self.prog_action[1:]
        self.look = {}

#gestion principale

    def algo(self, socket: socket.socket):
        print("=========================")
        if (self.prog_action == []):
            self.go_levelup = False
            self.commands.parse_inventory(socket, self.inventory)
            if (self.check_if_evolution(socket) == True):
                print("~~~~~~~~~~~~~~~~~~~~~~~~~")
                self.action_to_do = self.prog_action[0]
                self.prog_action = self.prog_action[1:]
                self.previous_action = self.action_to_do
                print(self.action_to_do)
                return self.action_to_do
            print("+++++++++++++++++++++++++")
            if (self.look == {}):
                self.action_to_do = "Look"
            else:
                self.track_object(socket)
        else:
            print("-------------------------")
            self.action_to_do = self.prog_action[0]
            self.prog_action = self.prog_action[1:]

        # if self.check_if_alone(socket) == False:
        #     if self.check_if_incantation(socket) == True:
        #         self.decision_to_steal_object(socket)
        #     else:
        #         self.check_if_evolution(socket)
        self.previous_action = self.action_to_do
        print(self.action_to_do)
        return self.action_to_do
