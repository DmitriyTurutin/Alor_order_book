#include <gtest/gtest.h>
#include "SSLClient.h"

TEST(SSLClientTest, ConnectTest) {
    SSLClient client("www.example.com", "443");
    EXPECT_NO_THROW(client.connect());
}