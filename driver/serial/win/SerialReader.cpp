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
        //std::cout<<"\nserialdata: "<< resp << strlen(SerialBuffer)<<std::flush;
        if(strlen(SerialBuffer) > 0) {
            //std::cout << "cane\n"<<std::flush;
            std::vector<std::shared_ptr<SerialSubscriber>> subscribers = serial->getSubscribers();
            for (std::vector<std::shared_ptr<SerialSubscriber>>::iterator it = subscribers.begin() ; it != subscribers.end(); ++it) {
                (*it)->onData(SerialBuffer, len, serial->getPort());
            }
        }
        //FIXME should be platform indipendent
        Sleep(10);
    }
}
