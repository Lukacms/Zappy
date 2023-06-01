/*
** EPITECH PROJECT, 2023
** gui
** File description:
** Game
*/

#include "zappy/Player/Player.hh"
#include <SFML/Graphics/RenderWindow.hpp>
#include <zappy/Scenes/Game.hh>

// Constructor && Destructor

zappy::Game::Game(sf::RenderWindow &window, unsigned int width, unsigned int height)
{
    sf::Vector2f center{};
    sf::View window_view = window.getView();
    PlayerInfo infos = {1, 1, 0, 0, Orientation::South, "TESTING"};

    this->m_map = zappy::Map{width, height};
    center.x = (width * TILE_SIZE * SCALING) / 2;
    center.y = (height * TILE_SIZE * SCALING) / 2;
    window_view.setCenter(center);
    window.setView(window_view);
    m_test = Player{infos};
    m_texture.loadFromFile(GAME_TEXTURE.data());
};

// Methods

void zappy::Game::draw(sf::RenderWindow &window)
{
    m_sprite.setTexture(m_texture);
    this->m_hud.setFocusedTile(this->m_map.getSelectedTile());
    this->m_map.draw(window, m_sprite);
    m_test.drawPlayer(window, m_sprite);
    if (m_test_clock.getElapsedTime().asSeconds() > 2 && m_test_flag == 0) {
        m_test_clock.restart();
        m_test.movePlayer(1, 0, Orientation::East);
        m_test_flag += 1;
    }
    if (m_test_clock.getElapsedTime().asSeconds() > 2 && m_test_flag == 1) {
        m_test_clock.restart();
        m_test.movePlayer(1, 1, Orientation::South);
        m_test_flag += 1;
    }
    if (m_test_clock.getElapsedTime().asSeconds() > 2 && m_test_flag == 2) {
        m_test_clock.restart();
        m_test.movePlayer(0, 1, Orientation::West);
        m_test_flag += 1;
    }
    if (m_test_clock.getElapsedTime().asSeconds() > 2 && m_test_flag == 3) {
        m_test_clock.restart();
        m_test.movePlayer(0, 0, Orientation::North);
        m_test_flag = 0;
    }
    this->m_hud.draw(window, m_sprite);
}

void zappy::Game::manageEvent(sf::RenderWindow &window, sf::Event &event)
{
    this->m_camera.cameraOnKeyPressed(event);
    this->m_camera.cameraOnKeyReleased(event);
    this->m_camera.moveView(window);
    this->m_hud.eventManager(event, window);
    this->m_hud.turnHUD(this->m_map.selectTile(event, window));
}
