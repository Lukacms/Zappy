/*
** EPITECH PROJECT, 2023
** gui
** File description:
** GUI
*/

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <cstddef>
#include <iostream>
#include <vector>
#include <zappy/GUI/GUI.hh>
#include <zappy/Map/Map.hh>
#include <zappy/Map/Tile.hh>
#include <zappy/Scenes/Game.hh>

// Constructor && Destructor

zappy::GUI::GUI(const std::string &address, unsigned short port)
    : m_window{{WIDTH, HEIGHT}, GUI_TITLE.data()}, game_scene{m_window, 20, 20}, m_client{address,
                                                                                          port}
{
    m_window.setFramerateLimit(FRAMELIMIT);
    m_music.openFromFile(MUSIC_FILENAME.data());
    m_music.setLoop(true);
}

// Methods

sf::RenderWindow &zappy::GUI::getWindow()
{
    return this->m_window;
}

int zappy::GUI::start()
{
    m_music.play();
    while (!m_client.WelcomeSuppressor())
        ;
    m_client.sendGraphic();
    while (m_window.isOpen()) {
        m_client.receiveCommand(game_scene);
        m_window.clear(sf::Color{74, 173, 74});
        eventManager();
        this->game_scene.draw(this->m_window);
        this->m_window.display();
    }
    this->m_music.stop();
    return 0;
}

void zappy::GUI::eventManager()
{
    sf::Event event;

    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            m_window.close();
        this->game_scene.manageEvent(this->m_window, event);
    }
}
