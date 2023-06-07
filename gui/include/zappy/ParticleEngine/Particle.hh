/*
** EPITECH PROJECT, 2023
** gui
** File description:
** Particle
*/

#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

namespace zappy
{

    class Particle
    {
        public:
            Particle() = default;
            Particle(Particle const &to_copy) = default;
            Particle(Particle &&to_move) = default;
            ~Particle() = default;

            Particle &operator=(Particle const &to_copy) = default;
            Particle &operator=(Particle &&to_move) = default;

            void draw(sf::RenderWindow &window);
            void setSize(sf::Vector2f size);
            void setVelocity(sf::Vector2f velocity);
            void setPosition(sf::Vector2f position);
            void setColor(sf::Color color);
            void moveShape();

            [[nodiscard]] sf::Vector2f getPosition() const;

        private:
            void resetPosition();

            sf::RectangleShape m_shape;
            sf::Vector2f m_velocity;
            bool m_delete;
    };

} // namespace zappy
