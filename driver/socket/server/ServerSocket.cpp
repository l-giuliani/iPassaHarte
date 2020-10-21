//
// Created by lgiuliani on 21/10/2020.
//

#include "ServerSocket.h"
#include <iostream>
ServerSocket::ServerSocket(){
    std::shared_ptr<tcp::acceptor> acceptor = std::make_shared<tcp::acceptor>(this->io_service, tcp::endpoint(tcp::v4(), 23));
    this->taskAcceptConnetions = std::make_shared<std::thread>(&ServerSocket::acceptConnections, this, acceptor);
}

void ServerSocket::acceptConnections(std::shared_ptr<tcp::acceptor> acceptor) {
    int numClients = 0;
    std::cout << "waiting for clients\n";
    while(true){
        std::shared_ptr<tcp::socket> socket = std::make_shared<tcp::socket>(this->io_service);
        acceptor->accept(*socket);
        //std::thread t(&ServerSocket::handleConnections, this, socket);
        if(++numClients <= MAXCONNECTION) {
            this->clientConnected.push_back(socket);
        }
    }
}

void ServerSocket::sendToClients(std::string message){
    boost::system::error_code ignored_error;
    for (std::vector<std::shared_ptr<tcp::socket>>::iterator it = this->clientConnected.begin() ; it != this->clientConnected.end(); ++it) {
        boost::asio::write((**it), boost::asio::buffer(message), ignored_error);
    }
}