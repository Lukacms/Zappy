/*
** EPITECH PROJECT, 2023
** gui
** File description:
** Game
*/

#pragma once

#include "zappy/Weather/WeatherManager.hh"
#include <zappy/MusicManager/MusicManager.hh>
#include <zappy/ParticleEngine/ParticleEngine.hh>
#include <SFML/System/Clock.hpp>
#include <zappy/GuiCommand/GuiCommand.hh>
#include <zappy/Player/Player.hh>
#include <zappy/Player/PlayerManager.hh>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <string_view>
#include <zappy/Camera.hh>
#include <zappy/HUD/HUD.hh>
#include <zappy/Map/Map.hh>
#include <zappy/Scenes/AScene.hh>

constexpr std::string_view GAME_TEXTURE{"./gui/assets/sprites/Game_texture.png"};

namespace zappy
{
    class Game : public AScene
    {
        public:
            Game();
            Game(Game const &to_copy) = delete;
            Game(Game &&to_move) = delete;
            ~Game() override = default;

            Game &operator=(Game const &to_copy) = delete;
            Game &operator=(Game &&to_move) = delete;

            void draw(sf::RenderWindow &window) final;
            void manageEvent(sf::RenderWindow &window, sf::Event &event) final;

            void createMap(Msz &map, sf::RenderWindow &window);
            void changeTileInventory(Bct &tile);

            void addPlayer(Pnw &new_player);
            void movePlayer(Ppo &player);
            void changePlayerInventory(Pin &player);
            void changePlayerLevel(Plv &player);
            void explusePlayer(Pex &player);
            void broadcast(Pbc &broadcast);
            void startIncantation(Pic &player_incantation);
            void endIncantation(Pie &player_incantation);
            void eggGoingLayed(Pkf &player_layer);
            void ressourceDropping(Pdr &ressources);
            void ressourceCollecting(Pgt &ressources);
            void playerDeath(Pdi &player);

            void eggLayed(Enw &egg_infos);
            void playerEggConnect(Ebo &player_infos);
            void eggDeath(Edi &egg_infos);

            void getTimeUnit(Sgt &time_unit);
            void getTimeUnitModifier(Sst &time_unit_modifier);

            void winTeam(Seg &winner);

            void servorMsg(Smg &message);

        private:
            zappy::HUD m_hud;
            zappy::Map m_map;
            zappy::Camera m_camera;
            zappy::PlayerManager m_player_manager;
            zappy::MusicManager m_music_manager;
            zappy::WeatherManager m_weather;

            sf::Sound m_sound;
    };
} // namespace zappy
