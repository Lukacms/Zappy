/* ** EPITECH PROJECT, 2023
** GuiClient
** File description:
** GuiClient
*/

#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/Socket.hpp>
#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>
#include <zappy/GuiClient/GuiClient.hpp>
#include <zappy/GuiCommand/GuiCommand.hh>
#include <zappy/Scenes/Game.hh>

zappy::Client::Client(const std::string &name, unsigned short port)
{
    if (m_socket.connect(sf::IpAddress{name}, port) != sf::Socket::Status::Done)
        throw;
    m_socket.setBlocking(false);
}

void zappy::Client::sendCommand(const std::string &cmd)
{
    m_socket.send(cmd.c_str(), cmd.size());
}

void zappy::Client::sendGraphic()
{
    if (m_socket.send("GRAPHIC\n", 8) != sf::Socket::Done)
        throw;
}

bool zappy::Client::WelcomeSuppressor()
{
    char buff[4096] = {0}; // NOLINT
    std::size_t size;

    if (m_socket.receive(&buff, 4096, size) != sf::Socket::Done)
        return false;
    return std::string{buff} == "WELCOME\n";
}

static std::vector<std::string> parser(const std::string &buff)
{
    std::vector<std::string> parsed{};
    std::istringstream stringstream{buff};
    std::string token;

    while (std::getline(stringstream, token, ' '))
        parsed.emplace_back(token);
    return parsed;
}

static zappy::Packet get_variant(std::vector<std::string> &parsed)
{
    for (size_t i{0}; i < zappy::NB_MAX_CMD; i++) {
        if (parsed[0] == zappy::VARIANT_LIST[i].name)
            return zappy::VARIANT_LIST[i].packet;
    }
    return zappy::Packet{zappy::Ukn{}};
}

void zappy::Client::receiveCommand(zappy::Game &game)
{
    char buff[255] = {0}; // NOLINT
    std::size_t index{0};
    char tmp = -1;

    fillRingBuffer();
    std::memset(buff, '\0', 255);
    while ((tmp = m_ring_buffer.front()) != '\0') {
        if (m_ring_buffer.isWritable()) {
            if (!fillRingBuffer()) {
                m_ring_buffer.clear();
                return;
            }
            buff[index] = tmp;
            index += 1;
        } else if (tmp == '\n') {
            applyCommands(game, std::string{buff});
            index = 0;
            std::memset(buff, '\0', 255);
        } else {
            buff[index] = tmp;
            index += 1;
        }
    }
    m_ring_buffer.clear();
}

bool zappy::Client::fillRingBuffer()
{
    char buffer[1364]; // NOLINT
    std::size_t size{1364};
    std::size_t read_size{0};

    std::memset(buffer, '\0', 1364);
    m_socket.receive(buffer, size, read_size);
    if (size == 0)
        return false;
    for (auto chr : buffer)
        m_ring_buffer.push(chr);
    return true;
}

void zappy::Client::applyCommands(zappy::Game &game, const std::string &str)
{
    std::vector<std::string> parsed;

    parsed = parser(str);
    // std::cerr << "<---------------------------------------->" << std::endl;
    // std::cerr << str << std::endl;
    // for (auto yolo : parsed)
    //     std::cerr << yolo << std::endl;

    Packet variant = get_variant(parsed);
    auto visitor = make_lambda_visitor(
        [&](Msz &arg) {
            arg.x_map_size = std::atoi(parsed[1].c_str());
            arg.y_map_size = std::atoi(parsed[2].c_str());
            game.createMap(arg);
        },
        [&](Bct &arg) {
            arg.x_tile_coord = std::atoi(parsed[1].c_str());
            arg.y_tile_coord = std::atoi(parsed[2].c_str());
            arg.ressources[0] = std::atoi(parsed[3].c_str());
            arg.ressources[1] = std::atoi(parsed[4].c_str());
            arg.ressources[2] = std::atoi(parsed[5].c_str());
            arg.ressources[3] = std::atoi(parsed[6].c_str());
            arg.ressources[4] = std::atoi(parsed[7].c_str());
            arg.ressources[5] = std::atoi(parsed[8].c_str());
            arg.ressources[6] = std::atoi(parsed[9].c_str());
            game.changeTileInventory(arg);
        },
        [&](Tna &arg) { ; }, [&](Pnw &arg) { ; }, [&](Ppo &arg) { ; }, [&](Plv &arg) { ; },
        [&](Pin &arg) { ; }, [&](Pex &arg) { ; }, [&](Pbc &arg) { ; }, [&](Pic &arg) { ; },
        [&](Pie &arg) { ; }, [&](Pkf &arg) { ; }, [&](Pdr &arg) { ; }, [&](Pgt &arg) { ; },
        [&](Pdi &arg) { ; }, [&](Enw &arg) { ; }, [&](Ebo &arg) { ; }, [&](Edi &arg) { ; },
        [&](Ukn & /*arg*/) { return; }, [&](Sgt &arg) { ; }, [&](Sst &arg) { ; },
        [&](Seg &arg) { ; }, [&](Smg &arg) { ; });
    std::visit(visitor, variant);
}
