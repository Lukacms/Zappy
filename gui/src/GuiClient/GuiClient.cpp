/*
** EPITECH PROJECT, 2023
** GuiClient
** File description:
** GuiClient
*/

#include <SFML/Network/IpAddress.hpp>
#include <algorithm>
#include <cstring>
#include <vector>
#include <zappy/GuiClient/GuiClient.hpp>
#include <zappy/GuiCommand/GuiCommand.hh>

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

static std::vector<std::string> &&parser(const std::string &buff)
{
    std::vector<std::string> parsed{};
    std::string sub_str{};

    for (size_t i{0}; i < 4096 || buff[i] == '\0'; i++) {
        if (buff[i] == ' ') {
            parsed.push_back(sub_str);
            sub_str.clear();
        }
        sub_str.push_back(buff[i]);
    }
    return std::move(parsed);
}

static zappy::Packet get_variant(const std::vector<std::string> &parsed)
{
    for (size_t i{0}; i < zappy::NB_MAX_CMD; i++) {
        if (parsed[0] == zappy::VARIANT_LIST[0].name)
            return zappy::VARIANT_LIST[0].packet;
    }
    return zappy::Packet{};
}

void zappy::Client::receiveCommand()
{
    std::vector<std::string> parsed{};
    char buff[4096];
    std::memset(&buff, '\0', 4096);
    std::size_t size{0};

    m_socket.receive(&buff, 4096, size);
    parsed = parser(buff);

    Packet variant;
    auto visitor = make_lambda_visitor(
        [&](Msz &arg) { ; }, [&](Bct &arg) { ; }, [&](Tna &arg) { ; }, [&](Pnw &arg) { ; },
        [&](Ppo &arg) { ; }, [&](Plv &arg) { ; }, [&](Pin &arg) { ; }, [&](Pex &arg) { ; },
        [&](Pbc &arg) { ; }, [&](Pic &arg) { ; }, [&](Pie &arg) { ; }, [&](Pkf &arg) { ; },
        [&](Pdr &arg) { ; }, [&](Pgt &arg) { ; }, [&](Pdi &arg) { ; }, [&](Enw &arg) { ; },
        [&](Ebo &arg) { ; }, [&](Edi &arg) { ; }, [&](Sgt &arg) { ; }, [&](Sst &arg) { ; },
        [&](Seg &arg) { ; }, [&](Smg &arg) { ; });
    std::visit(visitor, variant);
}
