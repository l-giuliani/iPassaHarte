//
// Created by lgiuliani on 22/10/2020.
//

#ifndef IPASSAHARTE_CONFIGLIB_H
#define IPASSAHARTE_CONFIGLIB_H

#define CONFIG_FILE "iPassaHarte.ini"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include "SerialDTO.h"

class ConfigLib {
private:
    boost::property_tree::ptree pt;
public:
    ConfigLib(){
        boost::property_tree::ini_parser::read_ini(CONFIG_FILE, pt);
    }
    SerialDTO::SerialConf readSerialConf(std::string serialEntry);
    uint32_t readSocketServerPort();
};

#endif //IPASSAHARTE_CONFIGLIB_H
