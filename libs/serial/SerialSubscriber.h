//
// Created by lgiuliani on 17/10/2020.
//

#ifndef IPASSAHARTE_SERIALSUBSCRIBER_H
#define IPASSAHARTE_SERIALSUBSCRIBER_H

#include <string>

class SerialSubscriber {
public:
    virtual void onData(char* data, int len, std::string port) = 0;
    virtual ~SerialSubscriber(){}
};


#endif //IPASSAHARTE_SERIALSUBSCRIBER_H
