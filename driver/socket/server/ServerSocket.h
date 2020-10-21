//
// Created by lgiuliani on 21/10/2020.
//

#ifndef IPASSAHARTE_SERVERSOCKET_H
#define IPASSAHARTE_SERVERSOCKET_H

#define WIN32_LEAN_AND_MEAN
#include "boost/asio.hpp"
#include <thread>
#include <memory>

#define MAXCONNECTION 10

using boost::asio::ip::tcp;

class ServerSocket {
private:
    uint8_t connectionNum = 0;
    boost::asio::io_service io_service;
    std::shared_ptr<std::thread> taskAcceptConnetions;
    std::vector<std::shared_ptr<tcp::socket>> clientConnected;
public:
    ServerSocket();
    void acceptConnections(std::shared_ptr<tcp::acceptor> acceptor);
    void sendToClients(std::string message);
};


#endif //IPASSAHARTE_SERVERSOCKET_H
