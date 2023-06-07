/*
** EPITECH PROJECT, 2023
** gui
** File description:
** Game
*/

#include <zappy/MusicManager/MusicManager.hh>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <zappy/GuiCommand/GuiCommand.hh>
#include <zappy/Map/Map.hh>
#include <zappy/Player/Player.hh>
#include <zappy/Scenes/Game.hh>

// Constructor && Destructor

zappy::Game::Game()
{
    m_texture.loadFromFile(GAME_TEXTURE.data());
}

// Methods

void zappy::Game::draw(sf::RenderWindow &window)
{
    m_music_manager.fade();
    m_weather.checkWeather(m_music_manager);
    m_sprite.setTexture(m_texture);
    m_hud.setFocusedTile(m_map.getSelectedTile());
    m_map.draw(window, m_sprite);
    m_player_manager.animatePlayers();
    m_player_manager.drawPlayers(window, m_sprite);
    m_weather.draw(window);
    m_hud.draw(window, m_sprite);
}

void zappy::Game::manageEvent(sf::RenderWindow &window, sf::Event &event)
{
    m_camera.cameraOnKeyPressed(event);
    m_camera.cameraOnKeyReleased(event);
    m_camera.moveView(window);
    m_hud.eventManager(event, window);
    m_hud.turnHUD(m_map.selectTile(event, window));
}

void zappy::Game::createMap(zappy::Msz &map, sf::RenderWindow &window)
{
    sf::Vector2i size = {map.x_map_size, map.y_map_size};
    sf::Vector2f center{};
    sf::View window_view = window.getView();

    m_map = zappy::Map{map.x_map_size, map.y_map_size};
    center.x = (map.x_map_size * TILE_SIZE * SCALING) / 2;
    center.y = (map.y_map_size * TILE_SIZE * SCALING) / 2;
    window_view.setCenter(center);
    window.setView(window_view);
    m_player_manager.setMapSize(size);
}

void zappy::Game::changeTileInventory(Bct &tile)
{
    m_map.modifyTile(tile);
}

void zappy::Game::addPlayer(Pnw &new_player)
{
    m_player_manager.addPlayer(new_player);
}

void zappy::Game::changePlayerInventory(Pin &player)
{
    m_player_manager.changePlayerStats(player);
}

void zappy::Game::movePlayer(Ppo &player)
{
    m_player_manager.changePlayerStats(player);
}

void zappy::Game::changePlayerLevel(Plv &player)
{
    m_player_manager.changePlayerStats(player);
}

void zappy::Game::explusePlayer(Pex &player)
{
    m_player_manager.explusePlayer(player);
}

void zappy::Game::playerDeath(Pdi &player)
{
    m_player_manager.playerDeath(player);
}
