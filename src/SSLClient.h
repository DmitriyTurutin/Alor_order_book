//
// Created by gnome on 4/10/23.
//

#ifndef MY_PROJECT_SSLCLIENT_H
#define MY_PROJECT_SSLCLIENT_H


#include <string>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

using boost::asio::ip::tcp;

class SSLClient {
public:
    SSLClient(const std::string &host, const std::string &port);

    void connect();

    std::string request(const std::string &message);

    // TODO: decompose
    std::string read_stream();

private:
    std::string m_host;
    std::string m_port;
    boost::asio::io_context m_io_context;
    boost::asio::ssl::context m_ssl_context;
    tcp::socket m_socket{m_io_context};
    boost::asio::ssl::stream<tcp::socket &> m_ssl_socket{m_socket, m_ssl_context};
    
    std::pair<int, std::size_t> read_header();
};


#endif //MY_PROJECT_SSLCLIENT_H
