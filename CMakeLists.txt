cmake_minimum_required(VERSION 3.17)
project(ble_scanner VERSION 0.1)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS -pthread)

add_executable(ble_scanner main.cpp old_scanner_thread.cpp old_scanner_thread.h hc_scanner_thread.cpp hc_scanner_thread.h utils/mosquitto/mosquitto_wrapper.cpp utils/mosquitto/mosquitto_wrapper.h utils/wifi/WifiInfo.cpp utils/wifi/WifiInfo.h utils/process/shell_process.cpp utils/process/shell_process.h)

# find_package(libpaho /home/pi/libs/)
# target_link_libraries(ble_scanner mosquitto ${libpaho})
# target_link_libraries(ble_scanner /home/pi/libs/paho.mqtt.c/build/src/libpaho-mqtt3a.so)
# target_link_libraries (ble_scanner mosquitto /usr/local/lib/libpaho-mqtt3a.so)
target_link_libraries (ble_scanner mosquitto)