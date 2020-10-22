//
// Created by lgiuliani on 17/10/2020.
//

#ifndef IPASSAHARTE_SERIALREADERLIB_H
#define IPASSAHARTE_SERIALREADERLIB_H

#include <SerialSubscriber.h>
#include<string>
#include <iostream>
#include <sstream>
#include <memory>
#include "Serial.h"
#include "utils.h"
#include "ServerSocket.h"
class SerialReaderLib : public SerialSubscriber{
private:
    std::shared_ptr<Serial> serialOutput = nullptr;
    std::shared_ptr<ServerSocket> serverSocket = nullptr;
public:
    SerialReaderLib(std::shared_ptr<Serial> serialOutput){
        this->serialOutput = serialOutput;
    }
    void setServerSocket(std::shared_ptr<ServerSocket> serverSocket){
        this->serverSocket = serverSocket;
    }
    virtual void onData(char* data, int len, std::string port){
        std::stringstream ss;


        ss << port << "\n"<<std::flush;
        ss << getActualTimestamp() << " " << data << "\n"<<std::flush;
        ss << getActualTimestamp() << " ";
        ss << printHexBinary(data, len);
        ss << "\n";

        std::string s = ss.str();

        std::cout << s;

        if(this->serverSocket != nullptr) {
            serverSocket->sendToClients(s);
        }
        if(this->serialOutput != nullptr){
            this->serialOutput->write(data, len);
        }
    }
    virtual ~SerialReaderLib(){}
};


#endif //IPASSAHARTE_SERIALREADERLIB_H
