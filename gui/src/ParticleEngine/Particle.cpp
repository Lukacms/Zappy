/*
** EPITECH PROJECT, 2023
** gui
** File description:
** Particle
*/

#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <iterator>
#include <zappy/ParticleEngine/Particle.hh>

// Constructor && Destructor

// Methods

void zappy::Particle::draw(sf::RenderWindow &window)
{
    resetPosition();
    window.draw(m_shape);
}

void zappy::Particle::moveShape()
{
    m_shape.move(m_velocity);
}

void zappy::Particle::setVelocity(sf::Vector2f velocity)
{
    m_velocity = velocity;
}

void zappy::Particle::setSize(sf::Vector2f size)
{
    m_shape.setSize(size);
}

void zappy::Particle::setPosition(sf::Vector2f position)
{
    m_shape.setPosition(position);
}

void zappy::Particle::setColor(sf::Color color)
{
    m_shape.setFillColor(color);
}

void zappy::Particle::resetPosition()
{
    sf::Vector2f position = m_shape.getPosition();

    if (position.y >= 1100) {
        position.y = -100.F;
        m_shape.setPosition(position);
    }
}

sf::Vector2f zappy::Particle::getPosition() const
{
    return m_shape.getPosition();
}
