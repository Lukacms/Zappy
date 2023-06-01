/*
** EPITECH PROJECT, 2023
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
#include <vector>
#include <zappy/GuiClient/GuiClient.hpp>
#include <zappy/GuiCommand/GuiCommand.hh>
#include <zappy/Scenes/Game.hh>

zappy::Client::Client(const std::string &name, unsigned short port)
{
    char buff[4096]; // NOLINT
    std::size_t size{0};

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
    m_socket.send("GRAPHIC\n", 8);
}

bool zappy::Client::WelcomeSuppressor()
{
    char buff[4096]; // NOLINT
    std::size_t size;

    if (m_socket.receive(&buff, 4096, size) != sf::Socket::Done)
        return false;
    if (std::string{buff} == "WELCOME\n")
        return true;
    return false;
}

static std::vector<std::string> parser(const std::string &buff, char delim)
{
    std::vector<std::string> parsed{};
    std::string sub_str{};

    for (size_t i{0}; i < buff.size() || buff[i] == '\0'; i++) {
        if (buff[i] == delim) {
            parsed.push_back(sub_str);
            sub_str.clear();
            i += 1;
        }
        sub_str.push_back(buff[i]);
    }
    parsed.push_back(sub_str);
    for (auto str : parsed) {
        std::cout << str << '\n';
    }
    return parsed;
}

static zappy::Packet get_variant(const std::vector<std::string> &parsed)
{
    for (size_t i{0}; i < zappy::NB_MAX_CMD; i++) {
        if (parsed[0] == zappy::VARIANT_LIST[0].name)
            return zappy::VARIANT_LIST[0].packet;
    }
    return zappy::Packet{};
}

void zappy::Client::receiveCommand(zappy::Game &game)
{
    std::vector<std::string> parsed{};
    char buff[4096]; // NOLINT
    std::memset(&buff, '\0', 4096);
    std::size_t size{0};
    std::vector<std::string> parsed2{};

    std::cout << "HERE\n";
    if (m_socket.receive(&buff, 4096, size) != sf::Socket::Done)
        return;
    parsed = parser(buff, '\n');

    for (auto str : parsed) {
        std::cout << str << std::endl;
        parsed2 = parser(str, ' ');
        Packet variant = get_variant(parsed2);
        auto visitor = make_lambda_visitor(
            [&](Msz &arg) {
                arg.x_map_size = std::atoi(parsed2[1].c_str());
                arg.y_map_size = std::atoi(parsed2[2].c_str());
                game.createMap(arg);
            },
            [&](Bct &arg) { ; }, [&](Tna &arg) { ; }, [&](Pnw &arg) { ; }, [&](Ppo &arg) { ; },
            [&](Plv &arg) { ; }, [&](Pin &arg) { ; }, [&](Pex &arg) { ; }, [&](Pbc &arg) { ; },
            [&](Pic &arg) { ; }, [&](Pie &arg) { ; }, [&](Pkf &arg) { ; }, [&](Pdr &arg) { ; },
            [&](Pgt &arg) { ; }, [&](Pdi &arg) { ; }, [&](Enw &arg) { ; }, [&](Ebo &arg) { ; },
            [&](Edi &arg) { ; }, [&](Sgt &arg) { ; }, [&](Sst &arg) { ; }, [&](Seg &arg) { ; },
            [&](Smg &arg) { ; });
        std::visit(visitor, variant);
        break;
    }
}
