/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** GuiClient
*/

#pragma once

#include <SFML/Network.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <zappy/GuiCommand/GuiCommand.hh>

namespace zappy
{
    class Client
    {
        public:
            Client(const std::string &name, unsigned short port);
            Client(Client const &to_copy) = delete;
            Client(Client &&to_move) = delete;
            ~Client() noexcept = default;
            Client &operator=(Client const &to_copy) = delete;
            Client &operator=(Client &&to_move) = delete;

            void sendCommand(const std::string &cmd);
            void receiveCommand();

        private:
            zappy::Packet packet{};
            sf::TcpSocket m_socket{};
    };

    template <typename... Ts> struct LambdaVisitor : Ts... {
            LambdaVisitor(Ts &&...lambda) : Ts{std::forward<Ts>(lambda)}... {};
            using Ts::operator()...;
    };

    template <typename... Ts> auto make_lambda_visitor(Ts &&...lambda)
    {
        return LambdaVisitor<std::remove_cvref_t<Ts>...>{std::forward<Ts>(lambda)...};
    }

} // namespace zappy
