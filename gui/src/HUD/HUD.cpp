/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** HUD
*/

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <cstddef>
#include <ios>
#include <iostream>
#include <iterator>
#include <ostream>
#include <string>
#include <vector>
#include <zappy/HUD/HUD.hh>
#include <zappy/Map/Tile.hh>

// Constructor && Destructor

zappy::HUD::HUD()
{
    m_font.loadFromFile(MAIN_FONT.data());
    m_color = sf::Color{255, 255, 255, 255};
    initializeParchment();
    initializeRupees();
    initializeTexts();
    initializeFood();
}

// Methods

void zappy::HUD::draw(sf::RenderWindow &window, sf::Sprite &sprite)
{
    const sf::View world_view = window.getView();

    m_text.setFont(m_font);
    m_text.setFillColor(m_color_text);
    window.setView(m_hud_view);
    animateHUD();
    sprite.setColor(m_color);
    sprite.setTextureRect(m_parchment.m_rect);
    sprite.setPosition(m_parchment.m_position);
    sprite.setScale(m_hud_scale);
    m_parchment.m_box = sprite.getGlobalBounds();
    window.draw(sprite);
    for (size_t i = 0; i < RUPEE_TYPES; i += 1) {
        sprite.setTextureRect(m_rupees[i].m_rect);
        sprite.setPosition(m_rupees[i].m_position);
        m_text.setString(m_texts[i].m_str);
        m_text.setCharacterSize(32);
        m_text.setPosition(m_texts[i].m_position);
        m_text.setPosition(m_text.getPosition().x - m_hud_view.getSize().x / 10 * 1.25F,
                           m_text.getPosition().y);
        window.draw(m_text);
        m_text.setString(m_ressources[i].m_str);
        m_text.setPosition(m_ressources[i].m_position);
        m_text.setCharacterSize(24);
        window.draw(m_text);
        window.draw(sprite);
    }
    sprite.setTextureRect(m_food.m_rect);
    sprite.setPosition(m_food.m_position);
    window.draw(sprite);
    m_text.setCharacterSize(32);
    m_text.setPosition(m_food_text.m_position);
    m_text.setString(m_food_text.m_str);
    window.draw(m_text);
    m_text.setCharacterSize(24);
    m_text.setPosition(m_food_count.m_position);
    m_text.setString(m_food_count.m_str);
    window.draw(m_text);
    sprite.setColor({255, 255, 255, 255});
    window.setView(world_view);
}

void zappy::HUD::animateHUD()
{
    if (m_is_active && m_parchment.m_position.y > (m_hud_view.getSize().y / 3) * 2) {
        m_parchment.m_position.y -= HUD_SPEED;
        m_food.m_position.y -= HUD_SPEED;
        m_food_count.m_position.y -= HUD_SPEED;
        m_food_text.m_position.y -= HUD_SPEED;
        for (size_t i = 0; i < RUPEE_TYPES; i += 1) {
            m_rupees[i].m_position.y -= HUD_SPEED;
            m_texts[i].m_position.y -= HUD_SPEED;
            m_ressources[i].m_position.y -= HUD_SPEED;
        }
    }
    if (!m_is_active && m_parchment.m_position.y < m_hud_view.getSize().y) {
        m_parchment.m_position.y += HUD_SPEED;
        m_food.m_position.y += HUD_SPEED;
        m_food_count.m_position.y += HUD_SPEED;
        m_food_text.m_position.y += HUD_SPEED;
        for (size_t i = 0; i < RUPEE_TYPES; i += 1) {
            m_rupees[i].m_position.y += HUD_SPEED;
            m_texts[i].m_position.y += HUD_SPEED;
            m_ressources[i].m_position.y += HUD_SPEED;
        }
    }
    if (m_is_faded && m_color.a > MIN_ALPHA) {
        m_color.a -= ALPHA_SPEED;
        m_color_text.a -= ALPHA_SPEED;
    }
    if (!m_is_faded && m_color.a < MAX_ALPHA) {
        m_color.a += ALPHA_SPEED;
        m_color_text.a += ALPHA_SPEED;
    }
    if (!m_is_active)
        return;
    animateRupees();
    animateFood();
}

void zappy::HUD::animateRupees()
{
    if (m_rupees_clock.getElapsedTime().asMilliseconds() > static_cast<float>(RUPEE_COUNTDOWN_1) &&
        m_rupees_phases != 0) {
        m_rupees_phases += 1;
        if (m_rupees_phases >= RUPEE_PHASES) {
            m_rupees_phases = 0;
            for (auto &rupee : m_rupees)
                rupee.m_rect.left = 0;
        } else {
            for (auto &rupee : m_rupees)
                rupee.m_rect.left += RUPEE_WIDTH;
        }
        m_rupees_clock.restart();
    }
    if (m_rupees_clock.getElapsedTime().asSeconds() > static_cast<float>(2) &&
        m_rupees_phases == 0) {
        m_rupees_phases += 1;
        for (auto &rupee : m_rupees)
            rupee.m_rect.left = RUPEE_WIDTH;
        m_rupees_clock.restart();
    }
}

void zappy::HUD::turnHUD(bool status)
{
    m_is_active = status;
}

void zappy::HUD::eventManager(sf::Event &event, sf::RenderWindow &window)
{
    sf::Vector2i tmp{event.mouseMove.x, event.mouseMove.y};
    sf::Vector2f point = window.mapPixelToCoords(tmp, m_hud_view);

    if (event.type == sf::Event::MouseMoved)
        m_is_faded = m_parchment.m_box.contains(point);
}

void zappy::HUD::initializeParchment()
{
    m_parchment.m_rect = {0, 0, HUD_WIDTH, HUD_HEIGHT};
    m_parchment.m_position = {0, static_cast<float>(m_hud_view.getSize().y)};
    m_hud_scale = {m_hud_view.getSize().x / HUD_WIDTH, (m_hud_view.getSize().y / 3) / HUD_HEIGHT};
}

void zappy::HUD::initializeRupees()
{
    float pos_x;
    float pos_y;

    for (size_t i = 0; i < RUPEE_TYPES; i++) {
        m_rupees[i].m_rect = {0, HUD_HEIGHT + (static_cast<int>(i) * RUPEE_HEIGHT), RUPEE_WIDTH,
                              RUPEE_HEIGHT};
        if (i < 3) {
            pos_x = static_cast<float>(m_hud_view.getSize().x / 10) * (4 + (2 * i));
            pos_y = m_parchment.m_position.y + m_parchment.m_rect.height / 10 * 4 * SCALING;
        } else {
            pos_x = static_cast<float>(m_hud_view.getSize().x / 10) * (4 + (2 * (i % 3)));
            pos_y = m_parchment.m_position.y + m_parchment.m_rect.height / 10 * 8 * SCALING;
        }
        m_rupees[i].m_position = {pos_x, pos_y};
    }
}

void zappy::HUD::initializeTexts()
{
    std::vector<std::string> strings{LINEMATE.data(), DERAUMEDE.data(), SIBUR.data(),
                                     MENDIANE.data(), PHIRAS.data(),    THYSTAME.data()};

    for (size_t i = 0; i < RUPEE_TYPES; i += 1) {
        m_texts[i].m_str = strings[i];
        m_texts[i].m_position = {m_rupees[i].m_position.x,
                                 m_rupees[i].m_position.y + m_rupees[i].m_rect.height * 2};
    }
    for (size_t i = 0; i < RUPEE_TYPES; i += 1) {
        m_ressources[i].m_str = "x0";
        m_ressources[i].m_position = {
            m_rupees[i].m_position.x + m_rupees[i].m_rect.width * SCALING / 2,
            m_rupees[i].m_position.y + m_rupees[i].m_rect.height * SCALING};
    }
}

void zappy::HUD::initializeFood()
{
    m_food.m_rect.top = 88;
    m_food.m_rect.left = 61;
    m_food.m_rect.width = 16;
    m_food.m_rect.height = 16;
    m_food.m_position.x = static_cast<float>(m_hud_view.getSize().x / 10) * 2;
    m_food.m_position.y = m_parchment.m_position.y + m_parchment.m_rect.height / 10 * 8 * SCALING;
    m_food_text.m_str = "Food";
    m_food_text.m_position = {m_food.m_position.x - m_food.m_rect.width * SCALING,
                              m_food.m_position.y + m_food.m_rect.height * 2};
    m_food_count.m_str = "x0";
    m_food_count.m_position = {m_food.m_position.x + m_food.m_rect.width * SCALING / 2,
                               m_food.m_position.y + m_food.m_rect.height * SCALING};
}

void zappy::HUD::setFocusedTile(zappy::Tile &tile)
{
    m_ressources[0].m_str = "x" + std::to_string(tile.m_inventory.linemate);
    m_ressources[1].m_str = "x" + std::to_string(tile.m_inventory.deraumede);
    m_ressources[2].m_str = "x" + std::to_string(tile.m_inventory.sibur);
    m_ressources[3].m_str = "x" + std::to_string(tile.m_inventory.mendiane);
    m_ressources[4].m_str = "x" + std::to_string(tile.m_inventory.phiras);
    m_ressources[5].m_str = "x" + std::to_string(tile.m_inventory.thystame);
    m_food_count.m_str = "x" + std::to_string(tile.m_inventory.food);
}

void zappy::HUD::animateFood()
{
    if (m_food_clock.getElapsedTime().asMilliseconds() > 75.0F &&
        m_food_phases != 0) {
        m_food_phases += 1;
        if (m_food_phases >= 7) {
            m_food_phases = 0;
            m_food.m_rect.left = 61;
        } else
            m_food.m_rect.left += m_food.m_rect.width;
        m_food_clock.restart();
    } else if (m_food_clock.getElapsedTime().asSeconds() > 2.0F &&
        m_food_phases == 0) {
        m_food_phases += 1;
        m_food.m_rect.left += m_food.m_rect.width;
        m_food_clock.restart();
    }
}
