/*
** EPITECH PROJECT, 2023
** gui
** File description:
** GUI
*/

#include "zappy/Map/Tile.hh"
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

// Constructor && Destructor

zappy::GUI::GUI(unsigned int width, unsigned int height)
    : m_window{{width, height}, GUI_TITLE.data()}
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
    this->m_music.play();
    while (m_window.isOpen()) {
        this->m_window.clear(sf::Color{74, 173, 74});
        eventManager();
        this->m_map.draw(this->m_window);
        this->m_hud.draw(this->m_window);
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
        this->m_camera.cameraOnKeyPressed(event);
        this->m_camera.cameraOnKeyReleased(event);
        this->m_camera.moveView(m_window);
        this->m_hud.eventManager(event, m_window);
        this->m_hud.turnHUD(this->m_map.selectTile(event, this->m_window));
    }
}

void zappy::GUI::createMap(unsigned int width, unsigned int height)
{
    sf::Vector2f center{};
    sf::View window_view = this->m_window.getView();

    this->m_map = zappy::Map{width, height};
    center.x = (width * TILE_SIZE * SCALING) / 2;
    center.y = (height * TILE_SIZE * SCALING) / 2;
    window_view.setCenter(center);
    m_window.setView(window_view);
}
