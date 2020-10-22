//
// Created by lgiuliani on 22/10/2020.
//

#include "Serial.h"

#include <thread>
#include <cstring>
#include <iostream>

bool Serial::open(std::string port, uint16_t baudrate, uint8_t databits,
          uint8_t stopbits, uint8_t parity){

    try {
        this->port = port;

        this->serialPort->open(port);
        this->serialPort->set_option(boost::asio::serial_port_base::parity());    // default none
        this->serialPort->set_option(boost::asio::serial_port_base::character_size(databits));
        this->serialPort->set_option(boost::asio::serial_port_base::stop_bits());    // default one
        this->serialPort->set_option(boost::asio::serial_port_base::baud_rate(baudrate));

        this->initialized = true;

        this->task = std::make_shared<std::thread>(&Serial::waitForIncomingData, this, this);
        return true;
    }catch(boost::system::system_error e){
        std::cout << e.what() << "\n";
        return false;
    }
}

void Serial::waitForIncomingData(Serial* serial){
    char buff[SERIAL_BUFFER_SIZE];
    int len = SERIAL_BUFFER_SIZE;
    while(serial->isInitialized()) {
        memset(buff,0,sizeof(buff));
        serial->read(buff, len);

        std::string resp(buff);
        if(strlen(buff) > 0) {
            std::vector<std::shared_ptr<SerialSubscriber>> subscribers = serial->getSubscribers();
            for (std::vector<std::shared_ptr<SerialSubscriber>>::iterator it = subscribers.begin() ; it != subscribers.end(); ++it) {
                (*it)->onData(buff, strlen(buff), serial->getPort());
            }
        }
        //FIXME should be platform indipendent
        Sleep(10);
    }

}

void Serial::write(char* message, int len){
    if(!this->initialized){
        return;
    }
    this->serialPort->write_some(boost::asio::buffer(message, len));
}

void Serial::read(char* buff, int& len){
    this->serialPort->read_some(boost::asio::buffer(buff, len));
}

void Serial::close(){
    this->initialized = false;
    this->task->join();
    this->serialPort->close();
}

void Serial::subscribe(std::shared_ptr<SerialSubscriber> serialSubscriber){
    this->subscribers.push_back(serialSubscriber);
}

std::vector<std::shared_ptr<SerialSubscriber>> Serial::getSubscribers(){
    return this->subscribers;
}

Serial::~Serial(){
    this->close();
}