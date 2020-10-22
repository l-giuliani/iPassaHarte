//
// Created by lgiuliani on 22/10/2020.
//

#ifndef IPASSAHARTE_SERIAL_H
#define IPASSAHARTE_SERIAL_H

#include <vector>
#include <cstdint>
#include <string>
#include <memory>
#include "boost/asio/serial_port.hpp"
#include "boost/asio.hpp"
#include "SerialSubscriber.h"

#define SERIAL_BUFFER_SIZE 4000

class Serial {
private:
    uint16_t baudrate;
    uint8_t parity;
    uint8_t stopbits;
    uint8_t databits;
    std::string port;

    boost::asio::io_service io_service;
    std::shared_ptr<boost::asio::serial_port> serialPort;

    bool initialized=false;
    std::shared_ptr<std::thread> task;

    std::vector<std::shared_ptr<SerialSubscriber>> subscribers;

public:
    Serial(){
        std::shared_ptr<boost::asio::serial_port> serialPort = std::make_shared<boost::asio::serial_port>(io_service);
        this->serialPort = serialPort;
    }
    bool open(std::string port, uint16_t baudrate, uint8_t databits,
              uint8_t stopbits, uint8_t parity);
    void write(char* message, int len);
    void read(char* SerialBuffer, int& len);
    void close();
    void subscribe(std::shared_ptr<SerialSubscriber> serialSubscriber);
    std::vector<std::shared_ptr<SerialSubscriber>> getSubscribers();
    ~Serial();
    void join(){
        this->task->join();
    }
    bool isInitialized(){
        return this->initialized;
    }
    std::string getPort(){
        return this->port;
    }

    void waitForIncomingData(Serial* serial);
};


#endif //IPASSAHARTE_SERIAL_H
