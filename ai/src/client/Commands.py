##
## EPITECH PROJECT, 2023
## Zappy
## File description:
## Commands
##

import socket
BUFFER_SIZE = 1024

class Commands():
    def move_forward(self) -> str:
        return "Forward"

    def turn_left(self) -> str:
        return "Left"

    def turn_right(self) -> str:
        return "Right"

    def parse_inventory(self, socket: socket.socket , inventory) -> None:
        self.action_to_do = "Inventory"
        socket.sendall((self.action_to_do + '\n').encode())
        str_response = socket.recv(BUFFER_SIZE).decode("utf-8").split(',')
        for item in str_response:
            parts = item.strip().strip('[ ').strip(' ]').split(' ')
            key = parts[0]
            value = int(parts[1])
            if key in inventory:
                inventory[key] = value

    def look(self, response, look: dict) -> str:
        response = response.split(',')
        for i,item in enumerate(response):
            parts = item.strip().strip('[ ').strip(' ]')
            look[i] = parts

    def nb_player_in_team(self, socket: socket.socket) -> int:
        self.action_to_do = "Connect_nbr"
        socket.send((self.action_to_do + '\n').encode())
        str_response = socket.recv(BUFFER_SIZE).decode("utf-8")
        self.nb_player = int(str_response)
        return self.nb_player

    def broadcast(self) -> str:
        # fonction pour ajouter le message à broadcast
        # self.broadcast_text = ...
        self.action_to_do = "Broadcast " + self.broadcast_text
        return self.action_to_do

    def fork(self) -> str:
        action_to_do = "Fork"
        return action_to_do

    def eject(self) -> str:
        self.action_to_do = "Eject"
        return self.action_to_do

    def take_object(self, object_to_take: str) -> str:
        action_to_do = "Take " + object_to_take
        return action_to_do

    def set_object(self) -> str:
        # fonction pour ajouter les objects à drop pour évolution
        # self.object_to_take = ...
        action_to_do = "Set " + object
        return action_to_do

    def incantation(self) -> str:
        action_to_do = "Incantation"
        return action_to_do