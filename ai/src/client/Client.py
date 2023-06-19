##
## EPITECH PROJECT, 2023
## Zappy
## File description:
## Client
##

from sys import exit
import socket
import selectors
from socket import AF_INET, SOCK_STREAM
from ai.src.algorithm.Ai import Artifical_intelligence
from ai.src.client.Commands import Commands
from ai.src.broadcast.broadcast import get_broadcast_by_team

BUFFER_SIZE: int = 4096
EPITECH_SUCCESS: int = 0
EPITECH_ERROR: int = 84
MAX_CONSECUTIVE_REQUESTS: int = 10
UNICODE: str = "utf-8"


class Client():
    def __init__(self, hostname: str, port: str, team_name: str):
        self.name = team_name
        self.machine = hostname
        self.port = port
        self.socket = None
        if self.socket is None:
            self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        else:
            self.socket = socket
        self.ai = Artifical_intelligence(self.name)
        self.selectors = selectors.DefaultSelector()
        self.client_num = 0
        self.connected_player = 0
        self.pending_player = 0
        self.init_condition = False

    def start_connection(self):
        try:
            server_address = (self.machine, self.port)
            self.socket.setblocking(False)
            self.socket.connect_ex(server_address)
            self.events = selectors.EVENT_READ | selectors.EVENT_WRITE
            self.selectors.register(self.socket, self.events)
        except socket.error as socketErr:
            print("Error while connecting to server: ", socketErr)
            exit(EPITECH_ERROR)
        except ValueError as e:
            print("Server connexion error:", e)

#     def anaylse_data(self, data: str, nb: int):
#         if nb == 1:
#             self.ai.nb_team_unused_slots = int(data)
#             self.ai.action_to_do = ""
#             self.pending_player = 2
#         else:
#             print("analyse data before split: ", data)
#             data = data.split()
#             print("analyse data after split: ", data)
#             self.ai.action_to_do = ""
#             self.pending_player = 3
#             self.connected_player = 1
#             self.ai.is_processing = True

    def get_broadcast_in_my_team(self, socket: socket.socket, cord: int, message: str):
        if "evolution" in message and \
            int(message[-1]) == self.ai.level and \
                self.ai.inventory['food'] >= 6 and \
                self.ai.go_levelup == False:
            self.ai.turn_to_broadcast(socket, cord)
            return

    def parse_response(self, response: str):
        if "WELCOME" in response:
            self.ai.action_to_do = (self.name + '\n')
            self.ai.actif = True
            return
        if "dead" in response:
            print("Death of player number: ", self.client_num)
            exit(EPITECH_SUCCESS)
        if "Current level:" in response:
            self.ai.actif = True
            self.ai.level = int(response.split(':')[1].strip())
        if "Elevation underway" in response:
            self.ai.level_up(self.socket)
            return
        if response.isdigit() == True:
            self.ai.commands.nb_player_in_team(response, self.ai.nb_player, self.ai.value_up_to_date)
            self.ai.actif = True
            return
        if response.startswith("["):
            if (response[7].isdigit() == True):
                self.ai.commands.parse_inventory(response, self.ai.inventory)
            else:
                self.ai.commands.parse_look(response, self.ai.look)
            self.ai.actif = True
            return
        if "message" in response and "not my team" not in get_broadcast_by_team(int(self.ai.team_name.split('m')[1]), response.split(',')[1].strip()):
            self.get_broadcast_in_my_team(self.socket, int(response.split(' ')[1][0]), get_broadcast_by_team(int(self.ai.team_name.split('m')[1]), response.split(',')[1].strip()))
            return
        if "message" in response:
            print("not my team")
            return
        if "ok" in response or "ko" in response:
            self.ai.actif = True
        if self.init_condition == False:
            self.init_condition = True
            self.ai.actif = True
            print(f"init_condition: {self.init_condition}")
            print(f"ai.actif: {self.ai.actif}")
            return
            # elif self.pending_player < 3:
            #     if "message" in line:
            #         continue
            #     self.anaylse_data(line, self.pending_player)
            # elif self.just_log >= 3 and "message" in line:
            #     if self.ia.clear_read == 1:
            #         self.ia.clear_read = 0
            #         data = data.split("\n")[-1]
            #         continue
            #    BROADCAST ?
            # elif "Current level:" in line:
            #     print("Current level step")
            #     print("line: ", line)
            # if self.ai.action_to_do == "Inventory\n" or self.ai.inventory == {'food' : 0, 'linemate' : 0, 'deraumere' : 0, 'sibur' : 0, 'mendiane' : 0, 'phiras' : 0, 'thystame' : 0}:
            #     self.ai.commands.parse_inventory(self.socket, self.ai.inventory)
            # elif self.ai.action_to_do == "Connect_nbr\n":
            #     self.ai.nb_team_unused_slots = int(line)
            #     print("Nb team unused slots:", self.ai.nb_team_unused_slots)
            # if line[0].startswith('['):
            #     self.ai.commands.look(data, self.ai.look)
        # data = data.split("\n")[-1]

    def launcher(self):
        try:
            while True:
                event = self.selectors.select(timeout=None)
                for _, mask in event:
                    if mask & selectors.EVENT_READ:
                        print("\nEVENT READ")
                        recieve_data = self.socket.recv(BUFFER_SIZE).decode(UNICODE)
                        print(f"recieve_data: {recieve_data}")
                        self.parse_response(recieve_data.strip())

                    if mask & selectors.EVENT_WRITE:
                        if (self.init_condition == True and self.ai.actif == True):
                            self.ai.algo()
                        if (self.ai.action_to_do != "" and self.ai.actif == True):
                            print("\nEVENT_WRITE")
                            if self.name in self.ai.action_to_do:
                                self.init_condition == True;
                            self.socket.sendall((self.ai.action_to_do + "\n").encode())
                            print(f"action envoyé: {self.ai.action_to_do}")
                            self.ai.action_to_do = ""
                            self.ai.actif = False
                        # if self.connected_player and self.ai.is_processing == True:
                        #     self.ai.algo(self.socket)
                        # if self.ai.action_to_do == (self.name + '\n') and self.connected_player == 0:
                        #     self.pending_player = 1
                        # print("before sendall(), action to do is: " + self.ai.action_to_do)
                        # self.socket.sendall((self.ai.action_to_do).encode())
                        # print("after sendall()")
                        # self.ai.is_processing = False
# FIN PARTIE CLIENT LEO A IMPLEMENTER / ADAPTER AVEC LE RESTE

        except ValueError as valueErr:
            print("Inappropriate argument value:", str(valueErr))
            self.socket.close()
        except KeyboardInterrupt as keybInterr:
            print("KeyboardInterrupt:", str(keybInterr))
            self.socket.close()

    def close(self):
        self.selectors.unregister()
        self.socket.close()
