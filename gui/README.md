# Zappy - Gui

A tribute to Zaphod Beeblebrox

## Project
Our goal was to create a graphical client in order to show how IA move in the world of Trantor.

We had the following objectives:
* Represent what is happening on the server
* Create connection with sockets

### Dependencies
The GUI part is done in [C++](https://en.wikipedia.org/wiki/C%2B%2B), and build using [CMake](https://cmake.org/). Moreover, it uses [SFML](https://www.sfml-dev.org/), a multimedia library.

### Documentation

To have more information, look at the [docs](../docs) folder.

### Launch GUI
After building project, here is the output of the help:
```bash
$ > ./zappy_gui -h
USAGE: ./zappy_gui <SERVER_IP> <SERVER_PORT>
    SERVER_IP: IP Adress of the zappy server
    SERVER_PORT: Port of the zappy server
```

#### Interface
The Gui is divided in two parts, the first one is the world map which shows players and tiles.
"Image of link on the map"
The second one is the inventory of tiles or players.
"Image of the inventory"
To see the inventory of players or tiles, you have to click on them.
