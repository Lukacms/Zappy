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

zappy::Camera::Camera(const sf::View &view) : m_view{view}, m_directions{false, false, false, false}
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
        m_view.zoom(static_cast<float>(ZOOM_ADD));
    if (event.key.code == sf::Keyboard::Subtract)
        m_view.zoom(static_cast<float>(ZOOM_MINUS));
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
}

void zappy::Camera::moveView(sf::RenderWindow &window)
{
    if (m_directions[0])
        m_view.move(sf::Vector2f{0, -5});
    if (m_directions[1])
        m_view.move(sf::Vector2f{0, 5});
    if (m_directions[2])
        m_view.move(sf::Vector2f{5, 0});
    if (m_directions[3])
        m_view.move(sf::Vector2f{-5, 0});
    window.setView(this->m_view);
}
