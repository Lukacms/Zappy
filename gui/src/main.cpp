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
    zappy::GUI gui{1920, 1080};
    gui.createMap(20, 10);
    gui.start();
    return SUCCESS;
}
