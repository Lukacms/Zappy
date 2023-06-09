/*
** EPITECH PROJECT, 2023
** gui
** File description:
** PlayerManager
*/

#pragma once

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <string_view>
#include <vector>
#include <zappy/GuiCommand/GuiCommand.hh>
#include <zappy/Player/Player.hh>

constexpr std::string_view DEATH_SOUND{"./gui/assets/sound/death.ogg"};

namespace zappy
{
    class PlayerManager
    {
        public:
            PlayerManager();
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
            void playerDeath(Pdi &dead_player);
            bool selectPlayer(sf::Event &event, sf::RenderWindow &window);
            void deletePlayers();
            [[nodiscard]] Player &getSelectedPlayer();

        private:
            void depthManager();
            void deselecPlayer(int player_id);

            bool m_player_is_selected = false;
            Player m_selected_player;
            int m_selected_player_id;
            std::vector<Player> m_players;
            sf::Vector2i m_size;
            sf::SoundBuffer m_death;
            sf::Sound m_sound;
    };
} // namespace zappy
