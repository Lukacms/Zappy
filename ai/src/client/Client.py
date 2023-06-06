##
## EPITECH PROJECT, 2023
## Zappy
## File description:
## Client
##

import socket
from socket import AF_INET, SOCK_STREAM
from ai.src.algorithm.Ai import Artifical_intelligence

BUFFER_SIZE = 1024
EPITECH_SUCCESS = 0
EPITECH_ERROR = 84

class Client():
    def __init__(self, hostname: str, port: str, team_name: str):
        self.name = team_name
        self.machine = hostname
        self.port = port
        self.socket = None
        if self.socket is None:
            self.socket = socket.socket(AF_INET, SOCK_STREAM)
        else:
            self.socket = socket
        self.ia = Artifical_intelligence

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
            print(f"{response}")

        except ValueError as e:
            print("Server connexion error:", e)

    def client_launcher(self):
        try:
            while True:
                # request va contenir la commande à envoyer au serveur, une fois que l'IA aura décidé de ce qu'elle veut faire
                core = Artifical_intelligence(self.name)
                request: str = Artifical_intelligence.algo(core, self.socket)
                self.socket.sendall((request + '\n').encode())
                response: str = self.socket.recv(BUFFER_SIZE).decode("utf-8")
                print(f"{response}", end="")
                if "dead" in response:
                    exit(EPITECH_SUCCESS)

        except KeyboardInterrupt as e:
            self.socket.close()
            print("KeyboardInterrupt:", e)

    def close(self):
        self.socket.close()