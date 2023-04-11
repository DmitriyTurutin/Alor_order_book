#include "OrderBook.h"

OrderBook::OrderBook()
        : ssl_client(std::make_unique<SSLClient>("fstream.binance.com","443")) {
    
    ssl_client->connect();
    std::cout << depth_snapshot();
}

void OrderBook::run_forever(std::string& message) {
    ssl_client->request(message);
    while (true) {
        std::cout << ssl_client->read_stream() << std::endl << std::endl;
    }
}

std::vector<OrderBook::Level> OrderBook::parse_json(std::string json) {
    return std::vector<OrderBook::Level>();
}

std::string OrderBook::depth_snapshot() {
    // Send GET request to https://fapi.binance.com/fapi/v1/depth?symbol=BTCUSDT&limit=1000
    boost::asio::io_context io_context;

    // Resolve the hostname and port
    tcp::resolver resolver(io_context);
    tcp::resolver::results_type endpoints =
            resolver.resolve("fapi.binance.com", "443");

    // Establish a secure SSL/TLS connection to the server
    boost::asio::ssl::context ssl_context(boost::asio::ssl::context::tlsv12_client);
    boost::asio::ssl::stream<tcp::socket> ssl_socket(io_context, ssl_context);
    boost::asio::connect(ssl_socket.lowest_layer(), endpoints);
    ssl_socket.handshake(boost::asio::ssl::stream_base::handshake_type::client);

    // Send an HTTPS GET request with the query parameters
    std::string request =
            "GET /fapi/v1/depth?symbol=BTCUSDT&limit=10 HTTP/1.1\r\n"
            "Host: fapi.binance.com\r\n"
            "Accept: */*\r\n"
            "Connection: close\r\n"
            "\r\n";
    boost::asio::write(ssl_socket, boost::asio::buffer(request));

    // Read the response and print it out
    boost::asio::streambuf response_buffer;
    boost::asio::read_until(ssl_socket, response_buffer, "\r\n");
    std::istream response_stream(&response_buffer);
    std::string http_version;
    response_stream >> http_version;
    unsigned int status_code;
    response_stream >> status_code;
    std::string status_message;
    std::getline(response_stream, status_message);
    if (!response_stream || http_version.substr(0, 5) != "HTTP/") {
        std::cerr << "Error: Invalid response\n";
    }
    if (status_code != 200) {
        std::cerr << "Error: Server returned status code " << status_code << "\n";
    }
    boost::asio::read_until(ssl_socket, response_buffer, "\r\n\r\n");
    std::string header;
    boost::system::error_code error;
    while (std::getline(response_stream, header) && header != "\r") {}
    std::stringstream response_body_stream;
    while (boost::asio::read(ssl_socket, response_buffer,
                             boost::asio::transfer_at_least(1), error)) {
        response_body_stream << &response_buffer;
    }
    if (error != boost::asio::error::eof) {
        std::cerr << "Error: " << error.message() << "\n";
    }
    std::string response_body = response_body_stream.str();

    return response_body;
}





