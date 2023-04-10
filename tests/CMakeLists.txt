cmake_minimum_required(VERSION 3.5)

set(This OrderBookTests) 

# Test sources
set(Sources
        SSLClientTests.cpp)
# Locate the Google Test framework
find_package(GTest REQUIRED)

set(OPENSSL_ROOT_DIR "/usr")
find_package(OpenSSL REQUIRED)
# Add include directories for the Google Test framework and the src directory
include_directories(${GTEST_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/src)

# Add a test executable
add_executable(${This} ${Sources})

# Link the test executable with the Google Test framework and 
target_link_libraries(${This} ${GTEST_BOTH_LIBRARIES} ${OPENSSL_LIBRARIES} OrderBookLib)

link_directories(${OPENSSL_LIB_DIR})
# Add the test directory to the CTest configuration
add_test(NAME ${This} COMMAND ${This})
