##
## EPITECH PROJECT, 2023
## zappy
## File description:
## Ai
##

RESOURCES = ['food', 'linemate', 'deraumere', 'sibur', 'mendiane', 'phiras', 'thystame']
ELEVATION_RITUAL = {
    1: {'linemate' : 1},
    2: {'linerame' : 1, 'deraumere' : 1, 'sibur' : 1},
    3: {'linemate' : 2, 'sibur' : 1, 'phiras' : 2},
    4: {'linemate' : 1, 'deraumere' : 1, 'sibur' : 2, 'phiras' : 1},
    5: {'linemate' : 1, 'deraumere' : 2, 'sibur' : 1, 'mendiane' : 3},
    6: {'linemate' : 1, 'deraumere' : 2, 'sibur' : 3, 'phiras' : 1},
    7: {'linemate' : 2, 'deraumere' : 2, 'sibur' : 2, 'mendiane' : 2, 'phiras' : 2, 'thystame' : 1},
    }


class Artifical_intelligence():
    def __init__(self, team_name):
        self.inventory = {'food' : 0, 'linemate' : 0, 'deraumere' : 0, 'sibur' : 0, 'mendiane' : 0, 'phiras' : 0, 'thystame' : 0}
        self.broadcast_text = ""
        self.look = ""
        self.level = 1
        self.nb_player = 1
        self.life_units = 10
        self.connect_nbr = 0
        self.team_name = team_name
        self.previous_action = ""
        self.action_to_do = ""
        self.object_to_take = ""

    def check_tile_info():
        print("check_tile_info")


    def move_forward(self):
        self.action_to_do = "Forward"


    def turn_left(self):
        self.action_to_do = "Left"


    def turn_right(self):
        self.action_to_do = "Right"


    def parse_inv(self, socket):
        self.action_to_do = "Inventory"
        socket.send((self.action_to_do + '\n').encode())
        str_response = socket.recv(1024).decode("utf-8").split(',')
        for item in str_response:
            parts = item.strip().strip('[ ').strip(' ]').split(' ')
            key = parts[0]
            value = int(parts[1])
            if key in self.inventory:
                self.inventory[key] = value


    def nb_player_in_team(self, socket):
        self.action_to_do = "Connect_nbr"
        socket.send((self.action_to_do + '\n').encode())
        str_response = socket.recv(1024).decode("utf-8")
        self.nb_player = int(str_response)


    def broadcast(self):
        # fonction pour ajouter le message à broadcast
        # self.broadcast_text = ...
        self.action_to_do = "Broadcast " + self.broadcast_text


    def fork(self):
        self.action_to_do = "Fork"


    def eject(self):
        self.action_to_do = "Eject"


    def take_object(self):
        # fonction pour ajouter le nom de l'objet qui nous interesse
        # self.object_to_take = ...
        self.action_to_do = "Take " + self.object_to_take


    def set_object(self):
        # fonction pour ajouter les objects à drop pour évolution
        # self.object_to_take = ...
        self.action_to_do = "Set " + self.object_to_take

    def algo(self, socket):
        # Exemple de fonction pour lancer une action
        # self.parse_inv(socket)
        # self.action_to_do = turn_left()

        # self.look(socket)
        return self.action_to_do
