# Smart Directions: anchor
## Brief summary of the architecture
The smart directions architecture comprehends **anchors**, **effectors** and a **brain**. In addition to them, we have **devices**, that represent users. The **anchors** allow localization, whereas **effectors** are the components that provide feedback to the users. The **brain** is centralized and its main contribution is the activation of the effectors wrt the position of a device.

This code refers to the **anchors**. It is written in C++ and it is thought to be ran on a Raspberry with Raspbian OS.

## Downloading and building

After git cloning, please clean the cmake-build-rasp1 directory (or eventually create your desired build folder). Then, go to the root of the project and run 
```shell
make clean
```
. You'll have the build directory filled with the linked files. From now on, you'll need to recompile from the build directory (```cd cmake-build-rasp1```) by running ```cmake --build```.

## Used software: tools and libraries

You need to install hcitools and hcidump. You also need dev libraries related to bluetooth and MQTT to be installed (look at the [cmake](https://github.com/filipkrasniqi/smart-directions-publisher/blob/master/CMakeLists.txt) file. You'll see which dependencies are used).

## Protocol

Nodes communicate towards brain by using the MQTT protocol. An update on the topics will follow this guide, together with the connection to a new custom broker handling permissions. Currently the topics used by the nodes are

- **ble/rssi**, with a message containing <MAC_ADDRESS_RBERRY_PI>$<SNIFFED_MAC_ADDRESS>$<RSSI_VAL>.

## Code
### Execution
- **[main.cpp](https://github.com/filipkrasniqi/smart-directions-publisher/blob/master/main.cpp)**: executes two threads, that will be stopped gracefully in case of input. These are **HCScanner** and **MQTTPublisher**, whose job are, respectively, to **detect devices in the proximity** and **periodically communicate the detected devices** to the brain;
### Scanning of devices
- **[HCScanner](https://github.com/filipkrasniqi/smart-directions-publisher/blob/master/hc_scanner_thread.cpp)**: executes a shell command (```sudo hcitool lescan --duplicates | sudo hcidump```), that scans ble devices and takes useful info for localization. In particular, we use RSSI to infer, with a fixed threshold, whether a device is close. For each detected device, we publish on the aforementioned topic related to RSSI communication to the brain, with a sleep currently set to 50ms.
### MQTT publisher
- **[MQTTPublisher](https://github.com/filipkrasniqi/smart-directions-publisher/blob/master/utils/mosquitto/mosquitto_wrapper.cpp)**: C++ library that handles mqtt connection to the broker. Works as a wrapper of the [C mosquitto library](https://mosquitto.org/api/files/mosquitto-h.html). 

## Short term TODOs
- topic update
- connection to custom broker
- handling permissions with different users for MQTT
