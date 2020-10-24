# iPassaHarte  
### What is iPassaHarte  
iPassaHarte is a software that open two configurable serial connections, it waits for incoming data from this connections and redirect data readed to the other serial port. Before redirect data from one serial port to the other it dispays data on the screen in both ASCII and HEX form.  
It is also possible to display data incoming from serial ports sending them through socket starting the application with -socket param, you can develop your own sniffer socket client or use the already existing [iPassaHarteGui](https://github.com/l-giuliani/iPassaHarteGui).
Actually you can:  
- open a maximum of ten clients to sniff data
- use clients from several pc or devices in the network
### How can I use it ?  
- as a debug tool to sniff data sended by software and devices. It can be used with some virtual serial port software like socat on Linux or VSPE on Windows if you need to sniff data from your pc to some device, or you can put yourself in the midle of two blackbox devices to see what happens.
- in order to connect blackbox devices with different serial port params
- if you have problems with some high level language serial port library and you need to use a lower level library
- code is multiplatform, so maybe you can recompile it for some sort of linux embedded device with display, using [iPassaHarteGui](https://github.com/l-giuliani/iPassaHarteGui) as gui, or without display, sniffing data by socket connections
### Configuration
You can configure iPassaHarte editing iPassaHarte.ini, it has to be in the same folder of the binary file

```ini
#the two serial port used by iPassaHarte
[SERIAL1]
port=COM1
baudrate=1200
databits=8
parity=0
stopbits=1

[SERIAL2]
port=COM4
baudrate=1200
databits=8
parity=0
stopbits=1

[SOCKETSERVER]
#server socket port
port=23
```
### Project info  
- it can be compiled using cmake
- it uses C++ Boost libraries and they are required to compile the sw (used version is 1.67). You need to modify Boost include path in CMakeLists.txt
- you can use Windows API to handle serial communication instead of Boost. In this case you need to compile modifying set(SERIAL_PLATFORM boost) in set(SERIAL_PLATFORM win) in CMakeLists.txt
### Why it is named iPassaHarte
In Italian "il Passa Carte" is someone that takes cards and pass them to another person(persons are serial ports in this case). In Italy we have many dialects and specifically in Florence we use to aspirate 'c' letter(also some other letters in fact, and sometimes whole sentences), so it becomes an 'h'. Dialects are great ! you should visit us someday !
