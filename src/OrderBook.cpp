//
// Created by gnome on 4/10/23.
//

#include "OrderBook.h"

OrderBook::OrderBook()
        : ssl_client(std::make_unique<SSLClient>("fstream.binance.com","443")) {
    
    ssl_client->connect();
}

void OrderBook::run_forever(std::string& message) {
    ssl_client->request(message);
    while (true) {
        std::cout << ssl_client->read_stream() << std::endl << std::endl;
    }
}

void OrderBook::get_depth_snapshot() {

}




