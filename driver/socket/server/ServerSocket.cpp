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
    std::cout << "waiting for clients\n";
    while(true){
        std::shared_ptr<tcp::socket> socket = std::make_shared<tcp::socket>(this->io_service);
        acceptor->accept(*socket);
        //std::thread t(&ServerSocket::handleConnections, this, socket);
        if(++this->connections <= MAXCONNECTION) {
            this->clientConnected.push_back(socket);
        }
    }
}

void ServerSocket::sendToClients(std::string message){
    const std::lock_guard<std::mutex> lock(this->mutex);

    boost::system::error_code ignored_error;
    std::vector<int> elementsToErase;
    int index = 0;
    for (std::vector<std::shared_ptr<tcp::socket>>::iterator it = this->clientConnected.begin() ; it != this->clientConnected.end(); ++it) {
        int bytesWritten = boost::asio::write((**it), boost::asio::buffer(message), ignored_error);
        if(bytesWritten == 0){
            //sign to remove connection
            elementsToErase.push_back(index);
        }
        std::cout << "written bytes: " << bytesWritten << "\n";
        index++;
    }
    for (int i=0; i<elementsToErase.size(); ++i){
        this->clientConnected.erase(this->clientConnected.begin() + elementsToErase[i]);
        this->connections--;
    }
}