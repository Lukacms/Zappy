/*
** EPITECH PROJECT, 2023
** gui
** File description:
** ParticleEngine
*/

#include <SFML/System/Vector2.hpp>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <zappy/ParticleEngine/ParticleEngine.hh>

// Constructor && Destructor

// Methods

void zappy::ParticleEngine::drawParticles(sf::RenderWindow &window)
{
    moveParticles();
    if (m_delete)
        deleteParticles();
    for (auto &particle : m_particles)
        particle.draw(window);
}

void zappy::ParticleEngine::moveParticles()
{
    if (m_clock.getElapsedTime().asSeconds() < 0.01F)
        return;
    for (auto &particle : m_particles)
        particle.moveShape();
    m_clock.restart();
}

void zappy::ParticleEngine::clear()
{
    m_particles.clear();
}

void zappy::ParticleEngine::createRain()
{
    for (size_t iterator = 0; iterator < 1000; iterator += 1) {
        m_particles.emplace_back();
        m_particles[iterator].setSize(sf::Vector2f{2, 30});
        m_particles[iterator].setColor(sf::Color{196, 211, 223});
        m_particles[iterator].setVelocity(
            sf::Vector2f{0.F, static_cast<float>(std::rand() % 20 + 10)});
        m_particles[iterator].setPosition(sf::Vector2f{static_cast<float>(std::rand() % 1920),
                                                       static_cast<float>(-(std::rand() % 1080))});
    }
}

void zappy::ParticleEngine::setDelete()
{
    m_delete = true;
};

void zappy::ParticleEngine::deleteParticles()
{
    auto iterator = m_particles.begin();

    if (m_particles.empty()) {
        m_delete = false;
        return;
    }
    for (; iterator != m_particles.end();) {
        if (iterator->getPosition().y >= 1100) {
            iterator = m_particles.erase(iterator);
        } else
            ++iterator;
    }
}
