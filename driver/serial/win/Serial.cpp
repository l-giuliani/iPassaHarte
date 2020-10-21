//
// Created by lgiuliani on 16/10/2020.
//

#include "Serial.h"
#include <iostream>
#include <string>
#include <thread>
#include "SerialReader.h"

bool Serial::open(std::string port, uint16_t baudrate, uint8_t databits,
                  uint8_t stopbits, uint8_t parity){
    this->hComm = CreateFile(("\\\\.\\"+port).c_str(),                //port name
    GENERIC_READ | GENERIC_WRITE, //Read/Write
            0,                            // No Sharing
            NULL,                         // No Security
            OPEN_EXISTING,// Open existing port only
            0,            // Non Overlapped I/O
            NULL);        // Null for Comm Devices

    if (hComm == INVALID_HANDLE_VALUE){
        return false;
    }
    DCB dcbSerialParams = { 0 };
    dcbSerialParams.BaudRate = baudrate;  // Setting BaudRate = 9600
    dcbSerialParams.ByteSize = databits;         // Setting ByteSize = 8
    dcbSerialParams.StopBits = stopbits;// Setting StopBits = 1
    dcbSerialParams.Parity   = parity;  // Setting Parity = None
    SetCommState(hComm, &dcbSerialParams);

    COMMTIMEOUTS timeout = { 0 };
    timeout.ReadIntervalTimeout = 50;
    timeout.ReadTotalTimeoutConstant = 50;
    timeout.ReadTotalTimeoutMultiplier = 50;
    timeout.WriteTotalTimeoutConstant = 50;
    timeout.WriteTotalTimeoutMultiplier = 10;

    SetCommTimeouts(hComm, &timeout);

    this->initialized = true;

    //wait for incoming data
    this->task = std::thread(waitForIncomingData, this);

    this->port = port;
    return true;
}
void Serial::write(char* message, int len){
    if(!this->initialized){
        return;
    }
    char* lpBuffer = message;
    DWORD dNoOFBytestoWrite;         // No of bytes to write into the port
    DWORD dNoOfBytesWritten = 0;     // No of bytes written to the port
    dNoOFBytestoWrite = len;

    WINBOOL Status = WriteFile(hComm,        // Handle to the Serial port
                       lpBuffer,     // Data to be written to the port
                       dNoOFBytestoWrite,  //No of bytes to write
                       &dNoOfBytesWritten, //Bytes written
                       NULL);
}



void Serial::read(char* SerialBuffer, int& len){
    DWORD dwEventMask;

    char TempChar; //Temporary character used for reading
    DWORD NoBytesRead;
    int i = 0;
    //WaitCommEvent(hComm, &dwEventMask, NULL);
    int timeout = 100;
    do {
        ReadFile(hComm,           //Handle of the Serial port
                 &TempChar,       //Temporary character
                 sizeof(TempChar),//Size of TempChar
                 &NoBytesRead,    //Number of bytes read
                 NULL);

        if (NoBytesRead > 0) {
            SerialBuffer[i] = TempChar;// Store Tempchar into buffer
            i++;
        }
        //std::string resp(SerialBuffer);
        //std::cout << resp << "\n";
    } while (NoBytesRead > 0);
    len = i;
    //std::cout << "fff\n";
    //std::string resp(SerialBuffer);
    //std::cout << resp << "\n";
}
void Serial::close(){
    if(this->hComm != NULL) {
        CloseHandle(this->hComm);
    }
    this->initialized = false;
    this->task.join();
}

void Serial::subscribe(std::shared_ptr<SerialSubscriber> serialSubscriber){
    this->subscribers.push_back(serialSubscriber);
}

Serial::~Serial(){
    if(this->hComm != NULL) {
        CloseHandle(this->hComm);
    }
    this->initialized = false;
    this->task.join();
}

vector <std::shared_ptr<SerialSubscriber>> Serial::getSubscribers() {
    return this->subscribers;
}
