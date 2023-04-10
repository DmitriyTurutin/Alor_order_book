#include <iostream>
#include "SSLClient.h"

int main() {

    try {
        // Send the websocket request
        std::string request = "GET /stream?streams=btcusdt@depth HTTP/1.1\r\n";
        request += "Host: fstream.binance.com\r\n";
        request += "Upgrade: websocket\r\n";
        request += "Connection: Upgrade\r\n";
        request += "Sec-WebSocket-Key: x3JJHMbDL1EzLkh9GBhXDw==\r\n";
        request += "Sec-WebSocket-Version: 13\r\n\r\n";

        SSLClient ssl_client("fstream.binance.com", "443");

        ssl_client.connect();

        ssl_client.request(request);

        std::cout << ssl_client.read_stream() << std::endl << std::endl;
        
    } catch (...) {
        std::cerr << "An error occurred, exiting." << std::endl;
        return 1;
    }

    return 0;
}
