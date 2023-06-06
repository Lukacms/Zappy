/*
** EPITECH PROJECT, 2023
** gui
** File description:
** Player
*/

#include "Inventory.hh"
#include "zappy/Map/Tile.hh"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <utility>
#include <zappy/Player/Player.hh>

// Constructor && Destructor

zappy::Player::Player(const zappy::PlayerInfo &infos)
    : m_id{infos.m_id}, m_level{infos.m_level},
      m_orientation{infos.m_orientation}, m_team{infos.m_team}, m_position{static_cast<int>(infos.m_x), static_cast<int>(infos.m_y)}
{
    m_position_map.x = m_position.x * TILE_SIZE * SCALING + (TILE_SIZE * SCALING / 2);
    m_position_map.y = m_position.y * TILE_SIZE * SCALING + (TILE_SIZE * SCALING / 2);
}

// Methods

int zappy::Player::getId() const
{
    return m_id;
}

void zappy::Player::setPlayerLevel(int level)
{
    m_level = level;
}

void zappy::Player::drawPlayer(sf::RenderWindow &window, sf::Sprite &sprite, sf::Vector2i &size)
{
    animatePlayer(size);
    sprite.setOrigin({16, 26});
    sprite.setPosition(m_position_map);
    sprite.setTextureRect(m_rect);
    window.draw(sprite);
    sprite.setOrigin({0, 0});
}

void zappy::Player::movePlayer(int pos_x, int pos_y, Orientation orientation)
{
    m_orientation = orientation;
    if (m_orientation == Orientation::North) {
        m_remain.y = -TILE_SIZE * SCALING;
        if (pos_y == m_position.y)
            m_remain.y = 0;
    }
    if (m_orientation == Orientation::East) {
        m_remain.x = TILE_SIZE * SCALING;
        if (pos_x == m_position.x)
            m_remain.x = 0;
    }
    if (m_orientation == Orientation::South) {
        m_remain.y = TILE_SIZE * SCALING;
        if (pos_y == m_position.y)
            m_remain.y = 0;
    }
    if (m_orientation == Orientation::West) {
        m_remain.x = -TILE_SIZE * SCALING;
        if (pos_x == m_position.x)
            m_remain.x = 0;
    }
    m_position.x = pos_x;
    m_position.y = pos_y;
}

void zappy::Player::animatePlayer(sf::Vector2i &size)
{
    if (m_orientation == Orientation::North)
        animateNorth(size);
    if (m_orientation == Orientation::East)
        animateEast(size);
    if (m_orientation == Orientation::South)
        animateSouth(size);
    if (m_orientation == Orientation::West)
        animateWest(size);
}

void zappy::Player::animateNorth(sf::Vector2i &size)
{
    if (m_remain.y < 0) {
        m_position_map.y -= 1;
        m_remain.y += 1;
        if (m_position_map.y < 0)
            m_position_map.y = size.y * TILE_SIZE * SCALING;
        if (m_rect.top != 242)
            m_rect = {0, 242, 32, 32};
        if (m_clock.getElapsedTime().asSeconds() > 0.07F) {
            m_rect.left += m_rect.width;
            if (m_rect.left / 32 >= 10)
                m_rect.left = 0;
            m_clock.restart();
        }
    } else
        m_rect = {96, 274, 32, 32};
}

void zappy::Player::animateEast(sf::Vector2i &size)
{

    if (m_remain.x > 0) {
        m_position_map.x += 1;
        m_remain.x -= 1;
        if (m_position_map.x > size.x * TILE_SIZE * SCALING)
            m_position_map.x = 0;
        if (m_rect.top != 146)
            m_rect = {0, 146, 32, 32};
        if (m_clock.getElapsedTime().asSeconds() > 0.07F) {
            m_rect.left += m_rect.width;
            if (m_rect.left / 32 >= 10)
                m_rect.left = 0;
            m_clock.restart();
        }
    } else
        m_rect = {64, 274, 32, 32};
}

void zappy::Player::animateSouth(sf::Vector2i &size)
{
    if (m_remain.y > 0) {
        m_position_map.y += 1;
        m_remain.y -= 1;
        if (m_position_map.y > size.y * TILE_SIZE * SCALING)
            m_position_map.y = 0;
        if (m_rect.top != 178)
            m_rect = {0, 178, 32, 32};
        if (m_clock.getElapsedTime().asSeconds() > 0.07F) {
            m_rect.left += m_rect.width;
            if (m_rect.left / 32 >= 10)
                m_rect.left = 0;
            m_clock.restart();
        }
    } else
        m_rect = {0, 274, 32, 32};
}

void zappy::Player::animateWest(sf::Vector2i &size)
{
    if (m_remain.x < 0) {
        m_position_map.x -= 1;
        m_remain.x += 1;
        if (m_position_map.x < 0)
            m_position_map.x = size.x * TILE_SIZE * SCALING;
        if (m_rect.top != 210)
            m_rect = {0, 210, 32, 32};
        if (m_clock.getElapsedTime().asSeconds() > 0.07F) {
            m_rect.left += m_rect.width;
            if (m_rect.left / 32 >= 10)
                m_rect.left = 0;
            m_clock.restart();
        }
    } else
        m_rect = {32, 274, 32, 32};
}

sf::Vector2f zappy::Player::getPosition() const
{
    return this->m_position_map;
}

void zappy::Player::setPlayerInventory(Inventory &inventory)
{
    m_inventory = inventory;
}

zappy::Inventory zappy::Player::getInventory() const
{
    return m_inventory;
}
