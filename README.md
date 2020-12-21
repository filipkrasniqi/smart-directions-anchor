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

Nodes communicate towards brain by using the MQTT protocol. An update on the topics will follow this guide, together with the connection to a new custom broker handling permissions (TODO). Currently the topics used by the nodes are

- **ble/rssi**, with a message containing <MAC_ADDRESS_RBERRY_PI>$<SNIFFED_MAC_ADDRESS>$<RSSI_VAL>.

## Code

