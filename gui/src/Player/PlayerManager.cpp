/*
** EPITECH PROJECT, 2023
** gui
** File description:
** PlayerManager
*/

#include <Inventory.hh>
#include <algorithm>
#include <zappy/GuiCommand/GuiCommand.hh>
#include <zappy/Player/Player.hh>
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
    for (auto iterator = m_players.begin(); iterator != m_players.end(); iterator ++) {
        if (iterator->getId() == expulsed_player.player_nb)
            m_players.erase(iterator);
    }
}
