//
// Created by lgiuliani on 17/10/2020.
//

#include <iostream>
#include <string>
#include "SerialReader.h"

void waitForIncomingData(Serial* serial){
    char SerialBuffer[4000];

    while(serial->isInitialized()){
        //std::cout<<"test\n";
        memset(SerialBuffer, 0, sizeof(SerialBuffer));
        int len = 0;
        serial->read(SerialBuffer, len);
        std::string resp(SerialBuffer);

        if(strlen(SerialBuffer) > 0) {
            std::vector<std::shared_ptr<SerialSubscriber>> subscribers = serial->getSubscribers();
            for (std::vector<std::shared_ptr<SerialSubscriber>>::iterator it = subscribers.begin() ; it != subscribers.end(); ++it) {
                (*it)->onData(SerialBuffer, len, serial->getPort());
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
