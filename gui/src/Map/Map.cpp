/*
** EPITECH PROJECT, 2023
** gui
** File description:
** Map
*/

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <ostream>
#include <vector>
#include <zappy/Map/Map.hh>
#include <zappy/Map/Tile.hh>

// Constructor && Destructor

zappy::Map::Map(unsigned int width, unsigned int height)
{
    int random = 0;
    zappy::Tile tile = {};

    std::srand(static_cast<unsigned int>(time(nullptr)));
    for (size_t y = 0; y < height; y += 1) {
        this->m_map.emplace_back();
        for (size_t x = 0; x < width; x += 1) {
            random = std::rand() % TILE_NUMBER;
            tile.m_position = {static_cast<float>(x) * (TILE_SIZE * SCALING),
                               static_cast<float>(y) * (TILE_SIZE * SCALING)};
            tile.m_rect = {random * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE};
            this->m_map[y].emplace_back(tile);
        }
    }
    this->m_map_texture.loadFromFile(MAP_TEXTURE.data());
    this->m_cursor.m_rect = {0, TILE_SIZE, TILE_SIZE, TILE_SIZE};
}

// Methods

void zappy::Map::draw(sf::RenderWindow &window)
{
    this->m_map_sprite.setTexture(this->m_map_texture);
    for (auto &columns : this->m_map) {
        for (auto &tile : columns) {
            this->m_map_sprite.setTextureRect(tile.m_rect);
            this->m_map_sprite.setPosition(tile.m_position);
            tile.m_box = this->m_map_sprite.getGlobalBounds();
            m_map_sprite.setScale(sf::Vector2f{SCALING, SCALING});
            window.draw(this->m_map_sprite);
        }
    }
    if (this->isCursorActive) {
        this->m_map_sprite.setTextureRect(this->m_cursor.m_rect);
        this->m_map_sprite.setPosition(this->m_cursor.m_position);
        window.draw(this->m_map_sprite);
    }
}

void zappy::Map::selectTile(sf::Event &event, sf::RenderWindow &window)
{
    sf::Vector2i tmp{event.mouseButton.x, event.mouseButton.y};
    const sf::Vector2f point = window.mapPixelToCoords(tmp);

    if (event.mouseButton.button == sf::Mouse::Left) {
        for (auto height : this->m_map) {
            for (auto width : height) {
                if (width.m_box.contains(point)) {
                    this->isCursorActive = true;
                    this->m_cursor.m_position = width.m_position;
                }
            }
        }
    }
}

std::vector<std::vector<zappy::Tile>> zappy::Map::getMap() const
{
    return m_map;
}
