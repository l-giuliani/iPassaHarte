//
// Created by lgiuliani on 22/10/2020.
//

#include "ConfigLib.h"

SerialDTO::SerialConf ConfigLib::readSerialConf(std::string serialEntry){
    SerialDTO::SerialConf serialConf;
    serialConf.port = pt.get<std::string>(serialEntry + ".port");
    serialConf.baudrate = pt.get<uint32_t>(serialEntry + ".baudrate");
    serialConf.dataBits = pt.get<uint8_t>(serialEntry + ".databits");
    serialConf.parity = pt.get<uint8_t>(serialEntry + ".parity");
    serialConf.stopBits = pt.get<uint8_t>(serialEntry + ".stopbits");
    return serialConf;
}