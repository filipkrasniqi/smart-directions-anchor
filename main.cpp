#include <iostream>
#include "hc_scanner_thread.h"
#include "utils/wifi/WifiHandler.h"
#include "utils/file/Parser.h"
#include <thread>
#include <fstream>

#include <linux/wireless.h>
#include <sys/ioctl.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <vector>

int main() {
    // TODO usa WifiSniffer in c++ che esegue sudo iw dev wlan0 scan | cat TP-LINK
    std::string address = "80.211.69.17";
    Parser *parser = new Parser();
    WifiHandler *wifi = new WifiHandler();
    
    std::cout << parser->getNodeID() << " " << parser->getSDInstanceID() << std::endl;

    if(parser->getNodeID() < 0) {
        if(parser->getSDInstanceID() < 0) {
            return 0;
        }
        // TODO non sono ok! rifaccio la trafila: invio sdInstanceID + WIFI rssis
        std::vector<WifiScan> wifis = wifi->getScanResults();
        // TODO ora dovrei fare una CURL, passando il dict wifi nell'url /node/<mac_node>/init/
        // TODO provare: https://stackoverflow.com/questions/26021536/c-http-request-with-poco/26026828#26026828, https://stackoverflow.com/questions/1011339/how-do-you-make-a-http-request-with-c
        exit(0);

    } else {
        // TODO controllo con server se sono OK: invio MAC
    }
    // TODO controllare che sia configurato correttamente, se no, chiedere inizializzazione del nodo
    // se non è presente node.setup, lo chiedo al server tramite il mio MAC ADDRESS che mi ritorna id nodo e si inizializza la posizione
    // il nodo rimane in loop a chiedere ed il sistema si segna che c'è un nodo da associare ad un gruppo di building
    // 1) creazione gruppi building
    // 2) lista di attesa per i nodi, se più gruppi di building presenti
    // 2.a) se arriva una richiesta da parte di un nodo, non guardo nemmeno se ce l'hanno già altri, lo reinizializzo; guardo solo se c'è un nodo uguale in stato di conferma;
    // 3) associazione di un nodo ad un gruppo di building tramite UI
    // 4) inferenza della posizione; se voglio, creo nome;
    // 5) comunico al nodo, che è ad ora in stato di conferma
    // 6) nodo si sblocca e conferma il suo stato

    //if()
    std::string macAddress = wifi->getMac();

    MQTTPublisher *publisher = new MQTTPublisher(address, macAddress);
    std::cout << "Publisher initialized " << std::endl;
    auto *thread = new HCScannerThread();
    std::thread tw1 = thread->start(publisher);
    int _;
    std::cout << "Type something to end: " << std::endl;
    std::cin >> _;
	thread->end();
    tw1.join();
    return 0;
}
