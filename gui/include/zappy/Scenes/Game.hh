/*
** EPITECH PROJECT, 2023
** gui
** File description:
** Game
*/

#pragma once

#include "zappy/GuiCommand/GuiCommand.hh"
#include "zappy/Player/Player.hh"
#include "zappy/Player/PlayerManager.hh"
#include <string_view>
#include <zappy/Camera.hh>
#include <zappy/Map/Map.hh>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <zappy/HUD/HUD.hh>
#include <zappy/Scenes/AScene.hh>

constexpr std::string_view GAME_TEXTURE{"./gui/assets/sprites/Game_texture.png"};

namespace zappy
{
    class Game : public AScene
    {
        public:
            Game(sf::RenderWindow &window, unsigned int width, unsigned int height);
            Game(Game const &to_copy) = default;
            Game(Game &&to_move) = default;
            ~Game() override = default;

            Game &operator=(Game const &to_copy) = default;
            Game &operator=(Game &&to_move) = default;

            void draw(sf::RenderWindow &window) final;
            void manageEvent(sf::RenderWindow &window, sf::Event &event) final;

            void createMap(Msz &map);
            void changeTileInventory(Bct &tile);

            void addPlayer(Pnw &new_player);
            void movePlayer(Ppo &player);
            void changePlayerInventory(Pin &player);
            void changePlayerLevel(Plv &player);

        private:
            zappy::HUD m_hud;
            zappy::Map m_map;
            zappy::Camera m_camera;
            zappy::PlayerManager m_player_manager;
            zappy::Player m_test;
            sf::Clock m_test_clock;
            int m_test_flag = 0;
    };
} // namespace zappy
