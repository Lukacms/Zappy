/*
** EPITECH PROJECT, 2023
** gui
** File description:
** Player
*/

#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>

namespace zappy
{

    enum class Orientation {
        North = 0,
        East = 1,
        South = 2,
        West = 3,
    };

    struct PlayerInfo {
            int m_id;
            int m_level;
            float m_x;
            float m_y;
            Orientation m_orientation;
            std::string m_team;
    };

    class Player
    {
        public:
            Player() = default;
            Player(const PlayerInfo &infos);
            Player(Player const &to_copy) = default;
            Player(Player &&to_move) = default;
            ~Player() = default;

            Player &operator=(Player const &to_copy) = default;
            Player &operator=(Player &&to_move) = default;

            void movePlayer(int pos_x, int pos_y, Orientation orientation);
            void animatePlayer();
            void drawPlayer(sf::RenderWindow &window, sf::Sprite &sprite);
            void setPlayerLevel(int level);

            [[nodiscard]] int getId() const;
            [[nodiscard]] sf::Vector2f getPosition() const;
        private:

            void animateNorth();
            void animateEast();
            void animateSouth();
            void animateWest();
            int m_id;
            int m_level;
            Orientation m_orientation;
            std::string m_team;

            sf::Vector2f m_position;
            sf::Vector2f m_position_map;
            sf::Vector2f m_remain;
            sf::IntRect m_rect;
            sf::FloatRect m_box;
            sf::Clock m_clock;
    };
} // namespace zappy
