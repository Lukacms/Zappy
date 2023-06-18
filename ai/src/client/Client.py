##
## EPITECH PROJECT, 2023
## Zappy
## File description:
## Client
##

import socket
from socket import AF_INET, SOCK_STREAM
from ai.src.algorithm.Ai import Artifical_intelligence
from ai.src.client.Commands import Commands
from ai.src.broadcast.broadcast import get_broadcast_by_team

BUFFER_SIZE = 1024
EPITECH_SUCCESS = 0
EPITECH_ERROR = 84
MAX_CONSECUTIVE_REQUESTS = 10


class Client():
    def __init__(self, hostname: str, port: str, team_name: str):
        self.name = team_name
        self.machine = hostname
        self.port = port
        self.socket = None
        self.requests_buffer = []
        self.consecutive_requests = 0
        self.ai = Artifical_intelligence(self.name)
        if self.socket is None:
            self.socket = socket.socket(AF_INET, SOCK_STREAM)
        else:
            self.socket = socket

    def server_connexion(self):
        try:
            server_address = (self.machine, self.port)
            self.socket.connect(server_address)
            response: str = self.socket.recv(BUFFER_SIZE).decode("utf-8")
            if not response:
                raise ValueError("Server connexion error")
            print(f"{response}", end="")
            self.socket.sendall((self.name + '\n').encode())
            response: str = self.socket.recv(BUFFER_SIZE).decode("utf-8")
            print(f"{response}", end="")

        except ValueError as e:
            print("Server connexion error:", e)

    def send_request(self, request: str):
        if self.consecutive_requests < MAX_CONSECUTIVE_REQUESTS:
            self.socket.sendall((request + '\n').encode())
            self.consecutive_requests += 1
        elif self.consecutive_requests >= MAX_CONSECUTIVE_REQUESTS:
            print("Error: too many consecutive requests, waiting for server response to continue...")
            self.pause_request()
        else:
            self.requests_buffer.append(request)

    def handle_response(self):
        self.consecutive_requests -= 1
        if self.consecutive_requests == 0 and self.requests_buffer:
            next_request = self.requests_buffer.pop(0)
            self.socket.sendall(('next_request:' + next_request + '\n').encode())
            self.consecutive_requests += 1

    def pause_request(self):
        print("pause_request")
        pass

    def get_broadcast_in_my_team(self, socket: socket.socket, cord: int, message: str):
        next_response = self.socket.recv(BUFFER_SIZE).decode("utf-8")
        print(f"{next_response}", end="")
        self.ai.commands.parse_inventory(socket, self.ai.inventory)
        if "evolution" in message and \
            int(message[-1]) == self.ai.level and \
                self.ai.inventory['food'] >= 8 and \
                self.ai.go_levelup == False:
            self.ai.turn_to_broadcast(socket, cord)
            return
        else:
            if "message" in next_response:
                return
            self.parse_response(next_response)

    def parse_response(self, response: str):
        if "dead" in response:
            self.close()
        if "Elevation underway" in response:
            self.ai.level_up(self.socket)
            return
        if response[0] == '[':
            self.ai.commands.look(response, self.ai.look)
            return
        if "message" in response and "not my team" not in get_broadcast_by_team(int(self.ai.team_name.split('m')[1]), response.split(',')[1].strip()):
            self.get_broadcast_in_my_team(self.socket, int(response.split(' ')[1][0]), get_broadcast_by_team(int(self.ai.team_name.split('m')[1]), response.split(',')[1].strip()))
            return
        if "ok" in response or "ok" in response:
            return
        self.client_launcher()

    def client_launcher(self):
        request = ""
        response = ""
        try:
            while True:
                request = Artifical_intelligence.algo(self.ai, self.socket)
                self.send_request(request)
                self.handle_response()
                response = self.socket.recv(BUFFER_SIZE).decode("utf-8")
                print(f"{response}", end="")
                self.parse_response(response)

        except ValueError as e:
            self.close()
            print("Client launcher error:", str(e))

        except KeyboardInterrupt as e:
            self.close()

            print("KeyboardInterrupt:", str(e))
    def close(self):
        if self.socket:
            self.socket.close()