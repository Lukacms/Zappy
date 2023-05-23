/*
** EPITECH PROJECT, 2023
** gui
** File description:
** Map
*/

#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string_view>
#include <vector>
#include <zappy/Map/Tile.hh>

constexpr std::string_view MAP_TEXTURE{"./gui/assets/sprites/map_texture.png"};
constexpr unsigned int TEXTURE_WIDTH{80};
constexpr unsigned int TEXTURE_HEIGHT{16};
constexpr unsigned int TILESIDE{32};

namespace zappy
{
    class Map
    {
        public:
            Map() = default;
            Map(unsigned int width, unsigned int height);
            Map(Map const &to_copy) = default;
            Map(Map &&to_move) = default;
            ~Map() = default;

            Map &operator=(Map const &to_copy) = default;
            Map &operator=(Map &&to_move) = default;

            void draw(sf::RenderWindow &window);
            [[nodiscard]] std::vector<std::vector<Tile>> getMap() const;
            void selectTile(sf::Event &event, sf::RenderWindow &window);

        private:
            std::vector<std::vector<Tile>> m_map;
            sf::Texture m_map_texture;
            sf::Sprite m_map_sprite;
            Tile m_cursor;
            bool isCursorActive = false;
    };
} // namespace zappy

