cmake_minimum_required(VERSION 3.17)
project(iPassaHarte)

set(CMAKE_CXX_STANDARD 20)

set(PLATFORM win)

list(APPEND INCLUDES "${PROJECT_SOURCE_DIR}/driver/serial/${PLATFORM}" "${PROJECT_SOURCE_DIR}/libs/serial/" "${PROJECT_SOURCE_DIR}/services" "${PROJECT_SOURCE_DIR}/utils"
        "${PROJECT_SOURCE_DIR}/driver/socket/server" "C:\\Users\\lgiuliani\\Documents\\boost_1_67_0")
add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY)
#link_libraries(boost_system)
link_libraries(ws2_32)

add_executable(iPassaHarte main.cpp driver/serial/${PLATFORM}/Serial.cpp libs/serial/SerialReaderLib.cpp driver/serial/${PLATFORM}/SerialReader.cpp services/SystemServices.cpp utils/utils.cpp driver/socket/server/ServerSocket.cpp)

target_include_directories(iPassaHarte PUBLIC
        "${PROJECT_BINARY_DIR}"
        ${INCLUDES}
        )