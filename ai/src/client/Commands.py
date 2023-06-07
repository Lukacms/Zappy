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
        self.action_to_do = "Forward"
        return self.action_to_do

    def turn_left(self) -> str:
        self.action_to_do = "Left"
        return self.action_to_do

    def turn_right(self) -> str:
        self.action_to_do = "Right"
        return self.action_to_do

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

    def look(self, socket: socket.socket, look_result: dict) -> str:
        action_to_do = "Look"
        socket.sendall((action_to_do + '\n').encode())
        response = socket.recv(BUFFER_SIZE).decode("utf-8").strip()
        print("look_response:", response)
        if response.startswith("[") and response.endswith("]"):
            response = response[1:-1]
            tiles = response.split(',')
            for contents in tiles:
                tile_contents = contents.strip()
                tile_index = tile_contents[0]
                if len(tile_contents) >= 1:
                    objects_on_tile = tile_contents
                    print("look_parsing:", objects_on_tile)
                    look_result[tile_index] = objects_on_tile
        return action_to_do

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
        self.action_to_do = "Fork"
        return self.action_to_do

    def eject(self) -> str:
        self.action_to_do = "Eject"
        return self.action_to_do

    def take_object(self) -> str:
        # fonction pour ajouter le nom de l'objet qui nous interesse
        # self.object_to_take = ...
        self.action_to_do = "Take " + self.object_to_take
        return self.action_to_do

    def set_object(self) -> str:
        # fonction pour ajouter les objects à drop pour évolution
        # self.object_to_take = ...
        self.action_to_do = "Set " + self.object_to_take
        return self.action_to_do