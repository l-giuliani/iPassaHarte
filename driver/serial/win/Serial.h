//
// Created by lgiuliani on 16/10/2020.
//

#ifndef TEST_SERIAL_H
#define TEST_SERIAL_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <cstdint>
#include <string>
#include <vector>
#include <memory>
#include <thread>
#include "SerialSubscriber.h"

using namespace std;

class Serial {

private:
    uint16_t baudrate;
    uint8_t parity;
    uint8_t stopbits;
    uint8_t databits;
    std::string port;

    HANDLE hComm=NULL;

    bool initialized=false;
    std::thread task;

    vector<std::shared_ptr<SerialSubscriber>> subscribers;

public:
    Serial(){}
    bool open(std::string port, uint16_t baudrate, uint8_t databits,
              uint8_t stopbits, uint8_t parity);
    void write(char* message, int len);
    void read(char* SerialBuffer, int& len);
    void close();
    void subscribe(std::shared_ptr<SerialSubscriber> serialSubscriber);
    vector<std::shared_ptr<SerialSubscriber>> getSubscribers();
    ~Serial();
    void join(){
        this->task.join();
    }
    bool isInitialized(){
        return this->initialized;
    }
    std::string getPort(){
        return this->port;
    }

};


#endif //TEST_SERIAL_H
