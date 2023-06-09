/*
** EPITECH PROJECT, 2023
** gui
** File description:
** PlayerManager
*/

#include <Inventory.hh>
#include <SFML/Audio/Sound.hpp>
#include <algorithm>
#include <ios>
#include <iostream>
#include <zappy/GuiCommand/GuiCommand.hh>
#include <zappy/Player/Player.hh>
#include <zappy/Player/PlayerManager.hh>

// Constructor && Destructor

zappy::PlayerManager::PlayerManager()
{
    m_death.loadFromFile(DEATH_SOUND.data());
    m_sound.setBuffer(m_death);
    m_sound.setVolume(100.0F);
}

// Methods

void zappy::PlayerManager::animatePlayers()
{
    for (auto &player : m_players)
        player.animatePlayer(m_size);
    deletePlayers();
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

void zappy::PlayerManager::changePlayerStats(zappy::Ppo &position)
{
    for (auto &player : m_players) {
        if (player.getId() == position.player_nb) {
            player.movePlayer(position.x_tile_coord, position.y_tile_coord,
                              static_cast<Orientation>(position.orientation));
            break;
        }
    }
}

void zappy::PlayerManager::changePlayerStats(zappy::Plv &level)
{
    for (auto &player : m_players) {
        if (player.getId() == level.player_nb) {
            player.setPlayerLevel(level.incantation_level);
            break;
        }
    }
}

void zappy::PlayerManager::changePlayerStats(zappy::Pin &inventory)
{
    Inventory p_inventory = {0};

    p_inventory.food = static_cast<unsigned int>(inventory.ressources[0]);
    p_inventory.linemate = static_cast<unsigned int>(inventory.ressources[1]);
    p_inventory.deraumede = static_cast<unsigned int>(inventory.ressources[2]);
    p_inventory.sibur = static_cast<unsigned int>(inventory.ressources[3]);
    p_inventory.mendiane = static_cast<unsigned int>(inventory.ressources[4]);
    p_inventory.phiras = static_cast<unsigned int>(inventory.ressources[5]);
    p_inventory.thystame = static_cast<unsigned int>(inventory.ressources[6]);
    for (auto &player : m_players) {
        if (player.getId() == inventory.player_nb) {
            player.setPlayerInventory(p_inventory);
            break;
        }
    }
}

void zappy::PlayerManager::addPlayer(Pnw &new_player)
{
    PlayerInfo infos{new_player.player_nb,
                     new_player.incantation_level,
                     static_cast<float>(new_player.x_tile_coord),
                     static_cast<float>(new_player.y_tile_coord),
                     static_cast<Orientation>(new_player.orientation),
                     new_player.team_name};
    m_players.emplace_back(infos);
}

void zappy::PlayerManager::explusePlayer(Pex &expulsed_player)
{
    for (auto iterator = m_players.begin(); iterator != m_players.end(); iterator++) {
        if (iterator->getId() == expulsed_player.player_nb)
            m_players.erase(iterator);
    }
}

void zappy::PlayerManager::playerDeath(Pdi &dead_player)
{
    for (auto &player : m_players) {
        if (player.getId() == dead_player.player_nb) {
            m_sound.play();
            player.triggerDeath();
            break;
        }
    }
}

void zappy::PlayerManager::deletePlayers()
{
    for (auto iterator = m_players.cbegin(); iterator != m_players.cend(); iterator++) {
        if (iterator->canDeletePlayer()) {
            m_players.erase(iterator);
            break;
        }
    }
}

bool zappy::PlayerManager::selectPlayer(sf::Event &event, sf::RenderWindow &window)
{
    sf::Vector2i tmp{event.mouseButton.x, event.mouseButton.y};
    const sf::Vector2f point = window.mapPixelToCoords(tmp);
    bool is_touched = false;

    if (event.mouseButton.button == sf::Mouse::Left) {
        for (auto &player : m_players) {
            if (player.getColliderBox().contains(point)) {
                deselecPlayer(m_selected_player_id);
                m_player_is_selected = true;
                m_selected_player_id = player.getId();
                m_selected_player = player;
                player.triggerSelection(true);
                is_touched = true;
                break;
            }
        }
        if (!is_touched) {
            m_player_is_selected = false;
            deselecPlayer(m_selected_player_id);
        }
    }
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        m_player_is_selected = false;
        deselecPlayer(m_selected_player_id);
    }
    return m_player_is_selected;
}

void zappy::PlayerManager::deselecPlayer(int player_id)
{
    for (auto &player : m_players) {
        if (player.getId() == player_id)
            player.triggerSelection(false);
    }
}

zappy::Player &zappy::PlayerManager::getSelectedPlayer()
{
    return m_selected_player;
}
