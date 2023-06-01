/*
** EPITECH PROJECT, 2023
** gui
** File description:
** Game
*/

#include "zappy/GuiCommand/GuiCommand.hh"
#include "zappy/Map/Map.hh"
#include "zappy/Player/Player.hh"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <zappy/Scenes/Game.hh>

// Constructor && Destructor

zappy::Game::Game(sf::RenderWindow &window, unsigned int width, unsigned int height)
{
    sf::Vector2f center{};
    sf::View window_view = window.getView();
    PlayerInfo infos = {1, 1, 0, 0, Orientation::South, "TESTING"};

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
    sf::Vector2i test{20, 20};
    m_sprite.setTexture(m_texture);
    this->m_hud.setFocusedTile(this->m_map.getSelectedTile());
    this->m_map.draw(window, m_sprite);
    m_test.drawPlayer(window, m_sprite, test);
    if (m_test_clock.getElapsedTime().asSeconds() > 2 && m_test_flag == 0) {
        m_test_clock.restart();
        m_test.movePlayer(20, 0, Orientation::West);
        m_test_flag += 1;
    }
    if (m_test_clock.getElapsedTime().asSeconds() > 2 && m_test_flag == 1) {
        m_test_clock.restart();
        m_test.movePlayer(19, 0, Orientation::West);
        m_test_flag += 1;
    }
    if (m_test_clock.getElapsedTime().asSeconds() > 2 && m_test_flag == 2) {
        m_test_clock.restart();
        m_test.movePlayer(19, 20, Orientation::North);
        m_test_flag += 1;
    }
    if (m_test_clock.getElapsedTime().asSeconds() > 2 && m_test_flag == 3) {
        m_test_clock.restart();
        m_test.movePlayer(19, 19, Orientation::North);
        m_test_flag += 1;
    }
    if (m_test_clock.getElapsedTime().asSeconds() > 2 && m_test_flag == 4) {
        m_test_clock.restart();
        m_test.movePlayer(19, 20, Orientation::South);
        m_test_flag += 1;
    }
    if (m_test_clock.getElapsedTime().asSeconds() > 2 && m_test_flag == 5) {
        m_test_clock.restart();
        m_test.movePlayer(19, 0, Orientation::South);
        m_test_flag += 1;
    }
    if (m_test_clock.getElapsedTime().asSeconds() > 2 && m_test_flag == 6) {
        m_test_clock.restart();
        m_test.movePlayer(20, 0, Orientation::East);
        m_test_flag += 1;
    }
    if (m_test_clock.getElapsedTime().asSeconds() > 2 && m_test_flag == 7) {
        m_test_clock.restart();
        m_test.movePlayer(0, 0, Orientation::East);
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

void zappy::Game::createMap(zappy::Msz &map)
{
    sf::Vector2i size = {map.x_map_size, map.y_map_size};

    m_map = zappy::Map{map.x_map_size, map.y_map_size};
    m_player_manager.setMapSize(size);
}
