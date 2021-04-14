cmake_minimum_required(VERSION 3.17)
project(ble_scanner VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS -pthread)

add_executable(ble_scanner main.cpp hc_scanner_thread.cpp hc_scanner_thread.h utils/mosquitto/mosquitto_wrapper.cpp utils/mosquitto/mosquitto_wrapper.h utils/file/Parser.cpp utils/file/Parser.h utils/wifi/WifiHandler.cpp utils/wifi/WifiHandler.h utils/process/shell_process.cpp utils/process/shell_process.h)

# find_package(libpaho /home/pi/libs/)
# target_link_libraries(ble_scanner mosquitto ${libpaho})
# target_link_libraries(ble_scanner /home/pi/libs/paho.mqtt.c/build/src/libpaho-mqtt3a.so)
# target_link_libraries (ble_scanner mosquitto /usr/local/lib/libpaho-mqtt3a.so)
target_link_libraries (ble_scanner mosquitto stdc++fs)
