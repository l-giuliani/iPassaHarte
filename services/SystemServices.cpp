//
// Created by lgiuliani on 17/10/2020.
//
#include "SystemServices.hpp"
#include <iostream>
#include "Serial.h"
#include <memory>
#include "serialReaderLib.h"
#include "ServerSocket.h"
#include "ConfigLib.h"
#include "SerialDTO.h"

void initFeatures(ConfigLib& configLib, int argc, char *argv[], std::shared_ptr<SerialSubscriber> serialReaderLib, std::shared_ptr<SerialSubscriber> serialReaderLib2);

bool SystemService::initializeSystem(int argc, char *argv[]){
    ConfigLib configLib;
    SerialDTO::SerialConf serialConf1 = configLib.readSerialConf("SERIAL1");
    SerialDTO::SerialConf serialConf2 = configLib.readSerialConf("SERIAL2");

    std::shared_ptr<Serial> serial1(new Serial());
    bool res1 = serial1->open(serialConf1.port, serialConf1.baudrate, serialConf1.dataBits,
                             serialConf1.stopBits, serialConf1.parity);
    if(!res1){
        std::cout << "Error Opening Serial";
        return false;
    }
    std::shared_ptr<Serial> serial2(new Serial());
    bool res2 = serial2->open(serialConf2.port, serialConf2.baudrate, serialConf2.dataBits,
                              serialConf2.stopBits, serialConf2.parity);
    if(!res2){
        std::cout << "Error Opening Serial";
        return false;
    }

    //std::shared_ptr<SerialSubscriber> serialReaderLib(dynamic_cast<SerialSubscriber*>(new SerialReaderLib(serial2)));
    std::shared_ptr<SerialSubscriber> serialReaderLib1 = std::make_shared<SerialReaderLib>(serial2);
    std::shared_ptr<SerialSubscriber> serialReaderLib2 = std::make_shared<SerialReaderLib>(serial1);

    serial1->subscribe(serialReaderLib1);
    serial2->subscribe(serialReaderLib2);

    initFeatures(configLib, argc, argv, serialReaderLib1, serialReaderLib2);

    serial1->join();
    serial2->join();
    return true;
}

void initFeatures(ConfigLib& configLib, int argc, char *argv[], std::shared_ptr<SerialSubscriber> serialReaderLib1, std::shared_ptr<SerialSubscriber> serialReaderLib2){
    for(int i=0;i<argc;i++){
        if(strcmp(argv[i], "-socket") == 0){
            //socketServer start
            std::shared_ptr<ServerSocket> serverSocket = std::make_shared<ServerSocket>(configLib.readSocketServerPort());
            serialReaderLib1->setServerSocket(serverSocket);
            serialReaderLib2->setServerSocket(serverSocket);
        } else if(strcmp(argv[i], "-file") == 0){
            //TODO
        }
    }
}