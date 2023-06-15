##
## EPITECH PROJECT, 2023
## zappy
## File description:
## broadcast
##

import json
from sys import exit, argv

def get_broadcast_by_team(team: int, message: str) -> str:
    file = open('ai/asset/broadcast.json')
    data = json.load(file)
    for i in data['Broadcast'][team - 1]:
        if (data['Broadcast'][team - 1][i] == message):
            return i
    file.close()
    return "not my team"

def set_broadcast_by_team(team: int, message: str) -> str:
    file = open('ai/asset/broadcast.json')
    data = json.load(file)
    result = "AAAAAAAHHHHHHHH"
    for i in data['Broadcast'][team - 1]:
        if (message == i):
            result = data['Broadcast'][team - 1][message]
    file.close()
    return result

def main():
    print(set_broadcast_by_team(int(argv[1]), argv[2]))

if __name__ == "__main__":
    exit(main())