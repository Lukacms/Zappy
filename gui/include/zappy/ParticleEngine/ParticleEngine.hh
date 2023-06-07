/*
** EPITECH PROJECT, 2023
** gui
** File description:
** ParticleEngine
*/

#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <zappy/ParticleEngine/Particle.hh>
#include <vector>

namespace zappy
{

    class ParticleEngine
    {
        public:
            ParticleEngine() = default;
            ParticleEngine(ParticleEngine const &to_copy) = default;
            ParticleEngine(ParticleEngine &&to_move) = default;
            ~ParticleEngine() = default;

            ParticleEngine &operator=(ParticleEngine const &to_copy) = default;
            ParticleEngine &operator=(ParticleEngine &&to_move) = default;

            void createRain();
            void drawParticles(sf::RenderWindow &window);
            void setDelete();
            void deleteParticles();
            void clear();

        private:
            void moveParticles();

            bool m_delete;
            std::vector<Particle> m_particles;
            sf::Clock m_clock;
    };

} // namespace zappy
