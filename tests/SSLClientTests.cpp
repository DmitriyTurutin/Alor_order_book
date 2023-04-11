#include <gtest/gtest.h>
#include "SSLClient.h"

TEST(SSLClientTest, ConnectTest) {
    SSLClient client("www.example.com", "443");
    EXPECT_NO_THROW(client.connect());
}
TEST(SSLClientTest, RequestTest) {
    SSLClient client("www.example.com", "443");
    client.connect();
    std::string response = client.request("GET / HTTP/1.1\r\nHost: www.example.com\r\n\r\n");
    ASSERT_FALSE(response.empty());
}
