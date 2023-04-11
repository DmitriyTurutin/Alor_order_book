//
// Created by gnome on 4/10/23.
//

#ifndef MY_PROJECT_ORDERBOOK_H
#define MY_PROJECT_ORDERBOOK_H

#include "SSLClient.h"
#include <boost/asio.hpp>
#include <iostream>

// TODO: 1. buffer from websocket stream
// TODO: 2. get depth snapshot 
// TODO: 3. drop any event where u < lastUpdateId in the snapshot
// TODO: 4. The first processed event should have U <= lastUpdateId AND u >= lastUpdateId
// TODO: 5. While listening to the stream, each new event's pu should be equal to the previous event's u, otherwise initialize the process from step 2. 
// TODO: 6 If quantity 0 remove the price level
// TODO: 7. rewrite to use DI, inject ISSLClient
class OrderBook {
public:
    struct Level {
        double price;
        double amount;
    };

    OrderBook();

    void run_forever(std::string &message);

    static std::string depth_snapshot();

    void process_data();
    
    void buffer_data();

private:
    std::vector<Level> asks;
    std::vector<Level> bids;
    std::uint64_t lastUpdateId;
    std::unique_ptr<SSLClient> ssl_client;
    
    std::vector<Level> parse_json(std::string json);

    void populate_levels(const std::string &json_str);
};


#endif //MY_PROJECT_ORDERBOOK_H
