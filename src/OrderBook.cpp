//
// Created by gnome on 4/10/23.
//

#include "OrderBook.h"

OrderBook::OrderBook()
        : ssl_client(std::make_unique<SSLClient>("fstream.binance.com","443")) {
    
    ssl_client->connect();
    depth_snapshot();
}

void OrderBook::run_forever(std::string& message) {
    ssl_client->request(message);
    while (true) {
        std::cout << ssl_client->read_stream() << std::endl << std::endl;
    }
}

std::vector<OrderBook::Level> OrderBook::parse_json(std::string json) {
}

void OrderBook::depth_snapshot() {
    // Send get request to https://fapi.binance.com/fapi/v1/depth?symbol=BTCUSDT&limit=1000
    // Create context
    using boost::asio::ip::tcp;
    
    boost::asio::io_context io_context;

    // Resolve the hostname
    tcp::resolver resolver(io_context);
    tcp::resolver::results_type endpoints =
            resolver.resolve("fapi.binance.com", "80");

}





