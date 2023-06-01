/*
** EPITECH PROJECT, 2023
** gui
** File description:
** PlayerManager
*/

#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <zappy/Player/Player.hh>

namespace zappy
{

    class PlayerManager
    {
        public:
            PlayerManager() = default;
            PlayerManager(PlayerManager const &to_copy) = default;
            PlayerManager(PlayerManager &&to_move) = default;
            ~PlayerManager() = default;

            PlayerManager &operator=(PlayerManager const &to_copy) = default;
            PlayerManager &operator=(PlayerManager &&to_move) = default;

            void animatePlayers();
            void addPlayer(PlayerInfo &infos);
            void drawPlayers(sf::RenderWindow &window, sf::Sprite &sprite);
            void eventManager(sf::RenderWindow &window, sf::Event &event);
            void setMapSize(sf::Vector2i &size);

        private:
            void depthManager();

            std::vector<Player> m_players;
            sf::Vector2i m_size;
    };
} // namespace zappy
