//
// Created by lgiuliani on 22/10/2020.
//

#ifndef IPASSAHARTE_SERIALDTO_H
#define IPASSAHARTE_SERIALDTO_H

#include <cstdint>

namespace SerialDTO {
    typedef struct {
        std::string port;
        uint32_t baudrate;
        uint8_t dataBits;
        uint8_t parity;
        uint8_t stopBits;
    } SerialConf;
}

#endif //IPASSAHARTE_SERIALDTO_H
