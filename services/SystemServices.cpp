//
// Created by lgiuliani on 17/10/2020.
//
#include "SystemServices.hpp"
#include <iostream>
#include "Serial.h"
#include <memory>
#include "serialReaderLib.h"

bool initializeSystem(){
    std::shared_ptr<Serial> serial(new Serial());
    boolean res1 = serial->open("COM1", 1200, 8, 1, 0);
    if(!res1){
        std::cout << "Error Opening Serial";
        return false;
    }
    std::shared_ptr<Serial> serial2(new Serial());
    boolean res2 = serial2->open("COM3", 1200, 8, 1, 0);
    if(!res1){
        std::cout << "Error Opening Serial";
        return false;
    }

    //std::shared_ptr<SerialSubscriber> serialReaderLib(dynamic_cast<SerialSubscriber*>(new SerialReaderLib(serial2)));
    std::shared_ptr<SerialSubscriber> serialReaderLib = std::make_shared<SerialReaderLib>(serial2);

    std::shared_ptr<SerialSubscriber> serialReaderLib2 = std::make_shared<SerialReaderLib>(serial);
    serial->subscribe(serialReaderLib);
    serial2->subscribe(serialReaderLib2);
    serial->join();
    serial2->join();
    return true;
}

void initializeSocket(){

}