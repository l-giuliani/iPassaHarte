//
// Created by lgiuliani on 17/10/2020.
//

#ifndef IPASSAHARTE_SERIALREADERLIB_H
#define IPASSAHARTE_SERIALREADERLIB_H

#include <SerialSubscriber.h>
#include<string>
#include <iostream>
#include <memory>
#include "Serial.h"
#include "utils.h"
class SerialReaderLib : public SerialSubscriber{
private:
    std::shared_ptr<Serial> serialOutput = nullptr;
public:
    SerialReaderLib(std::shared_ptr<Serial> serialOutput){
        this->serialOutput = serialOutput;
    }
    virtual void onData(char* data, int len, std::string port){
        std::cout << port << "\n"<<std::flush;
        std::cout << getActualTimestamp() << " " << data << "\n"<<std::flush;
        std::cout << getActualTimestamp() << " ";
        printHexBinary(data, len);
        std::cout << "\n";
        if(this->serialOutput != nullptr){
            this->serialOutput->write(data, len);
        }
    }
    virtual ~SerialReaderLib(){}
};


#endif //IPASSAHARTE_SERIALREADERLIB_H
