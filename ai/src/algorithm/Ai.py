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
BUFFER_SIZE = 4096

class Artifical_intelligence():
    def __init__(self, team_name: str):
        self.actif = False
        self.stay = False
        self.value_up_to_date = False
        self.mentor = False
        self.look = {}
        self.inventory = {'food' : 0, 'linemate' : 0, 'deraumere' : 0, 'sibur' : 0, 'mendiane' : 0, 'phiras' : 0, 'thystame' : 0}
        self.nb_player = 1
        self.broadcast_text = ""
        self.team_name = team_name
        self.level = 1
        self.previous_action = ""
        self.action_to_do = ""
        self.prog_action = []
        self.commands = Commands()

    def object_needed(self, value) -> bool:
        for item in ELEVATION_RITUAL[self.level].keys():
            if "player" not in item and \
            item in self.look[value] and \
                self.inventory[item] < ELEVATION_RITUAL[self.level][item]:
                return True
        return False

    def get_object(self, value) -> bool:
        for item in self.look[value].split(' '):
            if (item != 'player' and item != ''):
                self.prog_action.append(self.commands.take_object(item))
        return True

    def decision_to_steal_object(self, socket) -> None:
        if self.object_needed(0) == True:
            return self.get_object(0)
        else:
            self.commands.eject()

    def turn_to_broadcast(self, socket, direction: int):
        self.prog_action = []
        self.look = {}
        self.go_levelup = True
        self.value_up_to_date = False
        if (direction == 1):
            self.prog_action.append("Forward\n")
            self.prog_action.append("Look\n")
            return
        if (direction == 2):
            self.prog_action.append("Forward\n")
            self.prog_action.append("Left\n")
            self.prog_action.append("Forward\n")
            self.prog_action.append("Look\n")
            return
        if (direction == 3):
            self.prog_action.append("Left\n")
            self.prog_action.append("Forward\n")
            self.prog_action.append("Look\n")
            return
        if (direction == 4):
            self.prog_action.append("Left\n")
            self.prog_action.append("Forward\n")
            self.prog_action.append("Left\n")
            self.prog_action.append("Forward\n")
            self.prog_action.append("Look\n")
            return
        if (direction == 5):
            self.prog_action.append("Left\n")
            self.prog_action.append("Left\n")
            self.prog_action.append("Forward\n")
            self.prog_action.append("Look\n")
            return
        if (direction == 6):
            self.prog_action.append("Right\n")
            self.prog_action.append("Forward\n")
            self.prog_action.append("Right\n")
            self.prog_action.append("Forward\n")
            self.prog_action.append("Look\n")
            return
        if (direction == 7):
            self.prog_action.append("Right\n")
            self.prog_action.append("Forward\n")
            self.prog_action.append("Look\n")
            return
        if (direction == 8):
            self.prog_action.append("Forward\n")
            self.prog_action.append("Right\n")
            self.prog_action.append("Forward\n")
            self.prog_action.append("Look\n")
            return

    def level_up(self):
        self.look = {}
        self.stay = True
        self.actif = False

    def check_if_evolution(self) -> bool:
        if self.inventory['food'] < 6:
            return False
        for item in ELEVATION_RITUAL[self.level].keys():
            if "player" in item:
                continue
            if self.inventory[item] < ELEVATION_RITUAL[self.level][item]:
                return False
        if self.look[0].count("player") < ELEVATION_RITUAL[self.level]["player"]:
            self.value_up_to_date = False
            self.prog_action.append(self.commands.broadcast(self.team_name ,"evolution" + str(self.level)))
            return True
        for item in ELEVATION_RITUAL[self.level].keys():
            if "food" not in item and \
                "player" not in item and \
                    self.inventory[item] >= ELEVATION_RITUAL[self.level][item]:
                self.prog_action.append(self.commands.set_object(item))
                self.inventory[item] -= 1
        self.prog_action.append("Incantation")
        return True

    def go_track_obj(self, tile, x, y) -> bool:
        print("MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM")
        for _ in range(y):
            print("Forward")
            self.prog_action.append("Forward\n")
        if (x < 0):
            print("LEFT")
            self.prog_action.append("Left\n")
            x = x * -1
            for _ in range(x):
                print("Forward")
                self.prog_action.append("Forward\n")
            return self.get_object(tile)
        if (x > 0):
            print("RIGHT")
            self.prog_action.append("Right\n")
            for _ in range(x):
                print("Forward")
                self.prog_action.append("Forward\n")
        return self.get_object(tile)

    def track_obj_set(self) -> bool:
        y = 0
        x = 0
        max_y = 0
        max_x = 0
        max_tile = 0
        value = 0
        value_tmp = 0
        for tile in range(len(self.look)):
            if (self.object_needed(tile) == True):
                return self.go_track_obj(tile, x, y)
            value_tmp = 0
            for item in self.look[tile].split(' '):
                if item in ITEM_VALUE:
                    value_tmp += ITEM_VALUE.get(item, 0)
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

    def requirements_analysis(self) -> None:
        if (self.nb_player < 8 and random.randint(1, 10) >= 9):
            self.prog_action.append("Fork")
            self.fork = 1
            return
        if self.track_obj_set() == False:
            print("GO FORWARD")
            self.prog_action.append("Forward")

    def algo(self):
        self.is_processing = True
        print(f"========================= lvl:{self.level}")
        if self.stay == True:
            self.stay = False
            return
        if (self.prog_action == []):
            self.go_levelup = False
            if self.value_up_to_date == True:
                if (self.check_if_evolution() == False):
                    print("+++++++++++++++++++++++++")
                    self.requirements_analysis()
                    if (self.look != {} and self.level > 1 and self.look[0].count("player") == ELEVATION_RITUAL[self.level]["player"]):
                        print("@@@@@@@@@@@@@@@@@@@@@@@@@")
                        self.stay = True
                else:
                    print("~~~~~~~~~~~~~~~~~~~~~~~~~")
                self.value_up_to_date = False
            else:
                self.prog_action.append("Inventory")
                self.prog_action.append("Look")
                self.value_up_to_date = True
        print("-------------------------")
        self.action_to_do = self.prog_action[0]
        self.prog_action = self.prog_action[1:]
        self.previous_action = self.action_to_do
        print("action to do: ", self.action_to_do)