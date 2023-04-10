#include <iostream>
#include <chrono>
#include <thread>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

using boost::asio::ip::tcp;

class SSLClient {
public:
    SSLClient(const std::string& host, const std::string& port)
            : m_host(host), m_port(port), m_ssl_context(boost::asio::ssl::context::tlsv12_client)
    {
        // Set up the SSL context
        m_ssl_context.set_default_verify_paths();
        m_ssl_context.set_verify_mode(boost::asio::ssl::verify_peer);
    }

    void connect() {
        try {
            // Resolve the host name and connect to the server 
            tcp::resolver resolver(m_io_context);
            auto endpoints = resolver.resolve(m_host, m_port);
            boost::asio::connect(m_ssl_socket.next_layer(), endpoints);

            // Perform the SSL handshake
            m_ssl_socket.handshake(boost::asio::ssl::stream_base::client);
        } catch(const boost::system::system_error& e) {
            std::cerr << "Error connecting to server: " << e.what() << std::endl;
            throw;
        }
    }

    std::string request(const std::string& message) {
        try {
            // Send the message
            boost::asio::write(m_ssl_socket, boost::asio::buffer(message));

            // Receive and return the response
            boost::asio::streambuf response_buf;
            boost::asio::read_until(m_ssl_socket, response_buf, "\r\n");
            std::istream response_stream(&response_buf);
            std::string http_version;
            response_stream >> http_version;
            unsigned int status_code;
            response_stream >> status_code;
            std::string status_message;
            std::getline(response_stream, status_message);
            std::string headers;
            while (std::getline(response_stream, headers) && headers != "\r") {
                // do nothing, headers are not used here
            }
            std::stringstream ss;
            ss << response_stream.rdbuf();
            return ss.str();
        } catch(const boost::system::system_error& e) {
            std::cerr << "Error sending message: " << e.what() << std::endl;
            throw;
        }
    }

    void read_stream() {
        try {
            while (true) {
                // Read the stream message
                boost::asio::streambuf stream_buf;
                boost::asio::read(m_ssl_socket, stream_buf, boost::asio::transfer_exactly(2219));
                std::stringstream ss;
                ss << &stream_buf;
                std::string message = ss.str();

                // Print the message
                std::cout << "Stream message: " << message << std::endl << std::endl << std::endl << std::endl;
            }
        } catch (const boost::system::system_error& e) {
            std::cerr << "Error reading stream: " << e.what() << std::endl;
            throw;
        }
    }


private:
    std::string m_host;
    std::string m_port;
    boost::asio::io_context m_io_context;
    boost::asio::ssl::context m_ssl_context;
    tcp::socket m_socket{m_io_context};
    boost::asio::ssl::stream<tcp::socket&> m_ssl_socket{m_socket, m_ssl_context};
};

int main() {
    SSLClient client("fstream.binance.com", "443");
    try {
        client.connect();

        // Send the websocket request
        std::string request = "GET /stream?streams=btcusdt@depth HTTP/1.1\r\n";
        request += "Host: fstream.binance.com\r\n";
        request += "Upgrade: websocket\r\n";
        request += "Connection: Upgrade\r\n";
        request += "Sec-WebSocket-Key: x3JJHMbDL1EzLkh9GBhXDw==\r\n";
        request += "Sec-WebSocket-Version: 13\r\n\r\n";
        std::string response = client.request(request);

        // Print the server response
        std::cout << "Response: " << response << std::endl;

        // Read and print stream responses until app is terminated
        client.read_stream();
    } catch(...) {
        std::cerr << "An error occurred, exiting." << std::endl;
        return 1;
    }

    return 0;
}
