//
// Created by lgiuliani on 17/10/2020.
//
#include "SystemServices.hpp"
#include <iostream>
#include "Serial.h"
#include <memory>
#include "serialReaderLib.h"
#include "ServerSocket.h"

bool initializeSystem(){
    std::shared_ptr<Serial> serial(new Serial());
    bool res1 = serial->open("COM1", 1200, 8, 1, 0);
    if(!res1){
        std::cout << "Error Opening Serial";
        return false;
    }
    std::shared_ptr<Serial> serial2(new Serial());
    bool res2 = serial2->open("COM3", 1200, 8, 1, 0);
    if(!res2){
        std::cout << "Error Opening Serial";
        return false;
    }

    //std::shared_ptr<SerialSubscriber> serialReaderLib(dynamic_cast<SerialSubscriber*>(new SerialReaderLib(serial2)));
    std::shared_ptr<SerialSubscriber> serialReaderLib = std::make_shared<SerialReaderLib>(serial2);

    std::shared_ptr<SerialSubscriber> serialReaderLib2 = std::make_shared<SerialReaderLib>(serial);
    serial->subscribe(serialReaderLib);
    serial2->subscribe(serialReaderLib2);

    //socketServer start
    std::shared_ptr<ServerSocket> serverSocket = std::make_shared<ServerSocket>();
    serialReaderLib->setServerSocket(serverSocket);
    serialReaderLib2->setServerSocket(serverSocket);

    serial->join();
    serial2->join();
    return true;
}

void initializeSocket(){

}