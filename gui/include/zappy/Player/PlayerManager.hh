/*
** EPITECH PROJECT, 2023
** gui
** File description:
** PlayerManager
*/

#pragma once

#include "zappy/GuiCommand/GuiCommand.hh"
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
            void addPlayer(Pnw &new_player);
            void changePlayerStats(Ppo &position);
            void changePlayerStats(Plv &level);
            void changePlayerStats(Pin &inventory);
            void drawPlayers(sf::RenderWindow &window, sf::Sprite &sprite);
            void eventManager(sf::RenderWindow &window, sf::Event &event);
            void setMapSize(sf::Vector2i &size);
            void explusePlayer(Pex &expulsed_player);

        private:
            void depthManager();

            std::vector<Player> m_players;
            sf::Vector2i m_size;
    };
} // namespace zappy
