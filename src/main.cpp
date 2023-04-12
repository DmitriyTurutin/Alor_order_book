#include <iostream>
#include "OrderBook.h"

int main() {

    try {
        // Send the websocket request
        std::string request = "GET /stream?streams=btcusdt@depth10 HTTP/1.1\r\n";
        request += "Host: fstream.binance.com\r\n";
        request += "Upgrade: websocket\r\n";
        request += "Connection: Upgrade\r\n";
        request += "Sec-WebSocket-Key: x3JJHMbDL1EzLkh9GBhXDw==\r\n";
        request += "Sec-WebSocket-Version: 13\r\n\r\n";
        
        OrderBook orderBook;
        
        orderBook.run_forever(request);
        
    } catch (...) {
        std::cerr << "An error occurred, exiting." << std::endl;
        return 1;
    }

    return 0;
}
