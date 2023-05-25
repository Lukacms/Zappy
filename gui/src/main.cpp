/*
** EPITECH PROJECT, 2023
** src
** File description:
** main
*/

#include <zappy/GUI/GUI.hh>
#include <zappy/gui.hh>

int main(int argc, const char *argv[])
{
    zappy::GUI gui{600, 400};
    gui.createMap(30, 30);
    gui.start();
    return SUCCESS;
}
