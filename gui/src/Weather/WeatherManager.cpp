/*
** EPITECH PROJECT, 2023
** gui
** File description:
** WeatherManager
*/

#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <zappy/MusicManager/MusicManager.hh>
#include <zappy/Weather/WeatherManager.hh>

// Constructor && Destructor

zappy::WeatherManager::WeatherManager()
{
    std::srand(time(nullptr)); // NOLINT
    m_weathers[0] = Weather::DAY;
    m_weathers[1] = Weather::RAINY;
    m_filter.setSize({1920, 1080});
    m_filter.setFillColor({0, 0, 0, 0});
}

// Methods

void zappy::WeatherManager::checkWeather(zappy::MusicManager &music_manager)
{
    int random;
    Weather new_weather;

    if (m_clock.getElapsedTime().asSeconds() < 15.F)
        return;
    m_cycles += 1;
    if (m_cycles == 10)
        m_cycles = 0;
    if (m_cycles % 5 == 0)
        changeDayNight();
    m_clock.restart();
    random = std::rand() % 2;
    new_weather = m_weathers[static_cast<size_t>(random)];
    if (new_weather == m_state)
        return;
    changeWeather(new_weather, music_manager);
    m_state = new_weather;
}

void zappy::WeatherManager::draw(sf::RenderWindow &window)
{
    sf::View window_view = window.getView();

    window.setView(m_view);
    animateFilter();
    m_engine.drawParticles(window);
    window.draw(m_filter);
    window.setView(window_view);
};

void zappy::WeatherManager::setFilter(bool status)
{
    m_filter_status = status;
}

void zappy::WeatherManager::animateFilter()
{
    sf::Color current_color = m_filter.getFillColor();

    if (m_filter_status && current_color.a < 130 && m_animation_clock.getElapsedTime().asSeconds() >= 0.02F) {
        current_color.a += 1;
        m_filter.setFillColor(current_color);
        m_animation_clock.restart();
    }
    if (!m_filter_status && current_color.a > 0 && m_animation_clock.getElapsedTime().asSeconds() >= 0.02F) {
        current_color.a -= 1;
        m_filter.setFillColor(current_color);
        m_animation_clock.restart();
    }
}

void zappy::WeatherManager::changeWeather(zappy::Weather new_weather, zappy::MusicManager &music_manager)
{
        if (new_weather == Weather::RAINY) {
        m_engine.createRain();
        setFilter(true);
        music_manager.loadNewMusic(MUSIC_RAINY_1.data());
    }
    if (new_weather == Weather::DAY) {
        setFilter(false);
        m_engine.setDelete();
        music_manager.loadNewMusic(MUSIC_DAY_2.data());
    }
    if (new_weather == Weather::NIGHT) {
        setFilter(true);
        m_engine.setDelete();
        music_manager.loadNewMusic(MUSIC_NIGHT_2.data());
    }
}

void zappy::WeatherManager::changeDayNight()
{
    if (m_cycles == 5) {
        for (size_t iterator = 0; iterator < m_weathers.size(); iterator += 1) {
            if (m_weathers[iterator] == Weather::DAY)
                m_weathers[iterator] = Weather::NIGHT;
        }
    }
    if (m_cycles == 0) {
        for (size_t iterator = 0; iterator < m_weathers.size(); iterator += 1) {
            if (m_weathers[iterator] == Weather::NIGHT)
                m_weathers[iterator] = Weather::DAY;
        }
    }
}
