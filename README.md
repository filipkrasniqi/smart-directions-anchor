**Downloading and building**

After git cloning, please clean the cmake-build-rasp1 directory (or eventually create your desired build folder). Then, go to the root of the project and run make clean. You'll have the build directory filled with the linked files. From now on, you'll need to recompile from the build directory (cd cmake-build-rasp1) by running cmake --build .

**Make sniffer work**

You need to install hcitools and hcidump. You also need dev libraries related to bluetooth and MQTT to be installed (look at the cmake file. You'll see which dependencies are used).

**Protocol**

MQTT protocol will publish on the broker address on topic ble/rssi a message containing 

<MAC_ADDRESS_RBERRY_PI>$<SNIFFED_MAC_ADDRESS>$<RSSI_VAL> 
