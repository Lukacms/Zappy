/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Camera
*/

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <zappy/Camera.hh>

// Constructor && Destructor

zappy::Camera::Camera() : m_directions{false, false, false, false, false}
{
}

// Methods

void zappy::Camera::cameraOnKeyPressed(sf::Event &event)
{
    if (event.type != sf::Event::KeyPressed)
        return;
    if (event.key.code == sf::Keyboard::Up)
        m_directions[0] = true;
    if (event.key.code == sf::Keyboard::Down)
        m_directions[1] = true;
    if (event.key.code == sf::Keyboard::Right)
        m_directions[2] = true;
    if (event.key.code == sf::Keyboard::Left)
        m_directions[3] = true;
    if (event.key.code == sf::Keyboard::Add)
        m_directions[4] = true;
    if (event.key.code == sf::Keyboard::Subtract)
        m_directions[5] = true;
}

void zappy::Camera::cameraOnKeyReleased(sf::Event &event)
{
    if (event.type != sf::Event::KeyReleased)
        return;
    if (event.key.code == sf::Keyboard::Up)
        m_directions[0] = false;
    if (event.key.code == sf::Keyboard::Down)
        m_directions[1] = false;
    if (event.key.code == sf::Keyboard::Right)
        m_directions[2] = false;
    if (event.key.code == sf::Keyboard::Left)
        m_directions[3] = false;
    if (event.key.code == sf::Keyboard::Add)
        m_directions[4] = false;
    if (event.key.code == sf::Keyboard::Subtract)
        m_directions[5] = false;
}

void zappy::Camera::moveView(sf::RenderWindow &window)
{
    sf::View tmp = window.getView();

    if (m_directions[0])
        tmp.move(sf::Vector2f{0, -5});
    if (m_directions[1])
        tmp.move(sf::Vector2f{0, 5});
    if (m_directions[2])
        tmp.move(sf::Vector2f{5, 0});
    if (m_directions[3])
        tmp.move(sf::Vector2f{-5, 0});
    if (m_directions[4])
        tmp.zoom(static_cast<float>(ZOOM_ADD));
    if (m_directions[5])
        tmp.zoom(static_cast<float>(ZOOM_MINUS));
    window.setView(tmp);
}
