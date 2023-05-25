/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** HUD
*/

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <cstddef>
#include <ios>
#include <iostream>
#include <iterator>
#include <ostream>
#include <vector>
#include <zappy/HUD/HUD.hh>
#include <zappy/Map/Tile.hh>

// Constructor && Destructor

zappy::HUD::HUD()
{
    this->m_font.loadFromFile(MAIN_FONT.data());
    this->m_texture.loadFromFile(HUD_TEXTURE.data());
    this->m_color = this->m_sprite.getColor();
    this->initializeParchment();
    this->initializeRupees();
    this->initializeTexts();
}

// Methods

void zappy::HUD::draw(sf::RenderWindow &window)
{
    const sf::View world_view = window.getView();

    this->m_sprite.setTexture(this->m_texture);
    this->m_text.setFont(this->m_font);
    this->m_text.setFillColor(this->m_color_text);
    this->m_text.setCharacterSize(30);
    window.setView(this->m_hud_view);
    this->animateHUD();
    this->m_sprite.setColor(this->m_color);
    this->m_sprite.setTextureRect(this->m_parchment.m_rect);
    this->m_sprite.setPosition(this->m_parchment.m_position);
    this->m_sprite.setScale(this->m_hud_scale);
    this->m_parchment.m_box = this->m_sprite.getGlobalBounds();
    window.draw(m_sprite);
    for (size_t i = 0; i < RUPEE_TYPES; i += 1) {
        this->m_sprite.setTextureRect(m_rupees[i].m_rect);
        this->m_sprite.setPosition(m_rupees[i].m_position);
        this->m_text.setString(this->m_texts[i].m_str);
        this->m_text.setPosition(this->m_texts[i].m_position);
        auto tmp = this->m_text.getGlobalBounds();
        this->m_text.setPosition(this->m_text.getPosition().x -
                                     this->m_hud_view.getSize().x / 10 * 1.25,
                                 this->m_text.getPosition().y);
        window.draw(m_sprite);
        window.draw(m_text);
    }
    window.setView(world_view);
}

void zappy::HUD::animateHUD()
{
    if (this->m_is_active &&
        this->m_parchment.m_position.y > (this->m_hud_view.getSize().y / 3) * 2) {
        this->m_parchment.m_position.y -= HUD_SPEED;
        for (size_t i = 0; i < RUPEE_TYPES; i += 1) {
            this->m_rupees[i].m_position.y -= HUD_SPEED;
            this->m_texts[i].m_position.y -= HUD_SPEED;
        }
    }
    if (!this->m_is_active && this->m_parchment.m_position.y < this->m_hud_view.getSize().y) {
        this->m_parchment.m_position.y += HUD_SPEED;
        for (size_t i = 0; i < RUPEE_TYPES; i += 1) {
            this->m_rupees[i].m_position.y += HUD_SPEED;
            this->m_texts[i].m_position.y += HUD_SPEED;
        }
    }
    if (this->m_is_faded && this->m_color.a > MIN_ALPHA) {
        this->m_color.a -= ALPHA_SPEED;
        this->m_color_text.a -= ALPHA_SPEED;
    }
    if (!this->m_is_faded && this->m_color.a < MAX_ALPHA) {
        this->m_color.a += ALPHA_SPEED;
        this->m_color_text.a += ALPHA_SPEED;
    }
    if (!this->m_is_active)
        return;
    this->animateRupees();
}

void zappy::HUD::animateRupees()
{
    if (this->m_rupees_clock.getElapsedTime().asMilliseconds() >
            static_cast<float>(RUPEE_COUNTDOWN_1) &&
        this->m_rupees_phases != 0) {
        this->m_rupees_phases += 1;
        if (this->m_rupees_phases >= RUPEE_PHASES) {
            this->m_rupees_phases = 0;
            for (auto &rupee : m_rupees)
                rupee.m_rect.left = 0;
        } else {
            for (auto &rupee : m_rupees)
                rupee.m_rect.left += RUPEE_WIDTH;
        }
        this->m_rupees_clock.restart();
    }
    if (this->m_rupees_clock.getElapsedTime().asSeconds() > static_cast<float>(2) &&
        this->m_rupees_phases == 0) {
        this->m_rupees_phases += 1;
        for (auto &rupee : m_rupees)
            rupee.m_rect.left = RUPEE_WIDTH;
        this->m_rupees_clock.restart();
    }
}

void zappy::HUD::turnHUD(bool status)
{
    this->m_is_active = status;
}

void zappy::HUD::eventManager(sf::Event &event, sf::RenderWindow &window)
{
    sf::Vector2i tmp{event.mouseMove.x, event.mouseMove.y};
    sf::Vector2f point = window.mapPixelToCoords(tmp, this->m_hud_view);

    if (event.type == sf::Event::MouseMoved)
        m_is_faded = this->m_parchment.m_box.contains(point);
}

void zappy::HUD::initializeParchment()
{
    this->m_parchment.m_rect = {0, 0, HUD_WIDTH, HUD_HEIGHT};
    this->m_parchment.m_position = {0, static_cast<float>(this->m_hud_view.getSize().y)};
    this->m_hud_scale = {this->m_hud_view.getSize().x / HUD_WIDTH,
                         (this->m_hud_view.getSize().y / 3) / HUD_HEIGHT};
}

void zappy::HUD::initializeRupees()
{
    float pos_x;
    float pos_y;

    for (size_t i = 0; i < RUPEE_TYPES; i++) {
        this->m_rupees[i].m_rect = {0, HUD_HEIGHT + (static_cast<int>(i) * RUPEE_HEIGHT),
                                    RUPEE_WIDTH, RUPEE_HEIGHT};
        if (i < 3) {
            pos_x = static_cast<float>(this->m_hud_view.getSize().x / 10) * (4 + (2 * i));
            pos_y =
                this->m_parchment.m_position.y + this->m_parchment.m_rect.height / 10 * 4 * SCALING;
        } else {
            pos_x = static_cast<float>(this->m_hud_view.getSize().x / 10) * (4 + (2 * (i % 3)));
            pos_y =
                this->m_parchment.m_position.y + this->m_parchment.m_rect.height / 10 * 8 * SCALING;
        }
        this->m_rupees[i].m_position = {pos_x, pos_y};
    }
}

void zappy::HUD::initializeTexts()
{
    std::vector<std::string> strings{LINEMATE.data(), DERAUMEDE.data(), SIBUR.data(),
                                     MENDIANE.data(), PHIRAS.data(),    THYSTAME.data()};

    for (size_t i = 0; i < RUPEE_TYPES; i += 1) {
        this->m_texts[i].m_str = strings[i];
        this->m_texts[i].m_position = {this->m_rupees[i].m_position.x,
                                       this->m_rupees[i].m_position.y +
                                           this->m_rupees[i].m_rect.height * 2};
    };
}
