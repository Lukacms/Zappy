/*
** EPITECH PROJECT, 2023
** src
** File description:
** main
*/

#include <cstdlib>
#include <zappy/GUI/GUI.hh>
#include <zappy/gui.hh>

int main(int argc, const char *argv[])
{
    if (argc != 3)
        return FAILURE;
    zappy::GUI gui{argv[1], static_cast<unsigned short>(std::atoi(argv[2]))};
    gui.start();
    return SUCCESS;
}
