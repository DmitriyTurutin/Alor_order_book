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
    SSLClient(std::string host, std::string port);

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


    std::tuple<std::size_t, bool> get_payload_length();

    std::vector<char> raed_payload(std::size_t payload_length, bool mask, std::vector<char> &masking_key);

    std::vector<char> read_masking_key(bool mask);
};


#endif //MY_PROJECT_SSLCLIENT_H
