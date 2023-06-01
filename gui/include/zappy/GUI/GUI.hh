/*
** EPITECH PROJECT, 2023
** gui
** File description:
** GUI
*/

#pragma once

#include "zappy/Camera.hh"
#include "zappy/HUD/HUD.hh"
#include <SFML/Audio.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <cstddef>
#include <string_view>
#include <vector>
#include <zappy/Map/Map.hh>

constexpr std::string_view GUI_TITLE{"Zappy Gui"};
constexpr unsigned int FRAMELIMIT{60};
constexpr std::string_view MUSIC_FILENAME{"./gui/assets/music/darkworld.ogg"};

namespace zappy
{
    class GUI
    {
        public:
            GUI(unsigned int width, unsigned int height);
            GUI(GUI const &to_copy) = delete;
            GUI(GUI &&to_move) = delete;
            ~GUI() = default;

            GUI &operator=(GUI const &to_copy) = delete;
            GUI &operator=(GUI &&to_move) = delete;

            [[nodiscard("PRENDS CETTE WINDOW")]] sf::RenderWindow &getWindow();
            void createMap(unsigned int width, unsigned int height);
            void updateWindow();
            void clearWindow();
            void eventManager();
            void draw();
            int start();

        private:
            sf::RenderWindow m_window;
            sf::Music m_music;
            zappy::Map m_map;
            zappy::Camera m_camera;
            zappy::HUD m_hud;
    };

} // namespace zappy
