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

std::string OrderBook::depth_snapshot() {
    // Send get request to https://fapi.binance.com/fapi/v1/depth?symbol=BTCUSDT&limit=1000
    // Create context
    using boost::asio::ip::tcp;
    
    boost::asio::io_context io_context;

    // Resolve the hostname
    tcp::resolver resolver(io_context);
    tcp::resolver::results_type endpoints =
        resolver.resolve("example.com", "http");

    // Connect to the server
    tcp::socket socket(io_context);
    boost::asio::connect(socket, endpoints);

    // Send the HTTP request
    boost::asio::streambuf request;
    std::ostream request_stream(&request);
    request_stream << "GET /index.html HTTP/1.1\r\n"
                   << "Host: example.com\r\n"
                   << "Connection: close\r\n\r\n";
    boost::asio::write(socket, request);


    return std::string();
    
}





