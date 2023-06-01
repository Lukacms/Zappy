/*
** EPITECH PROJECT, 2023
** gui
** File description:
** PlayerManager
*/

#include <algorithm>
#include <zappy/Player/PlayerManager.hh>

// Constructor && Destructor

// Methods

void zappy::PlayerManager::animatePlayers()
{
    for (auto &player : m_players)
        player.animatePlayer(m_size);
}

void zappy::PlayerManager::depthManager()
{
    auto compare = [](Player &player_a, Player &player_b) {
        return player_a.getPosition().y > player_b.getPosition().y;
    };
    std::sort(m_players.begin(), m_players.end(), compare);
}

void zappy::PlayerManager::drawPlayers(sf::RenderWindow &window, sf::Sprite &sprite)
{
    for (auto &player : m_players)
        player.drawPlayer(window, sprite, m_size);
}

void zappy::PlayerManager::setMapSize(sf::Vector2i &size)
{
    m_size = size;
}
