cmake_minimum_required(VERSION 3.5)

set(This OrderBook)

project(${This} C CXX)

# C/C++ standards
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_POSITION_INDEPENDENT_CODE)

# Enable testing
enable_testing()

# Headers
set(Headers
        src/OrderBook.h
        src/SSLClient.h
        libs/json.hpp)
# Source files 
set(Sources
        src/OrderBook.cpp
        src/SSLClient.cpp)

# Set Boost directories
set(BOOST_ROOT "/usr/local")
set(Boost_INCLUDE_DIRS "${BOOST_ROOT}/include")
set(Boost_LIBRARIES "${BOOST_ROOT}/lib/libboost_system.a" "${BOOST_ROOT}/lib/libboost_filesystem.a" "${BOOST_ROOT}/lib/libboost_json.a")

# Set OpenSSL directories
set(OPENSSL_ROOT_DIR "/usr")
find_package(OpenSSL REQUIRED)

# Add include directories for Boost and OpenSSL libraries
include_directories(${Boost_INCLUDE_DIRS} ${OPENSSL_INCLUDE_DIR})

# Add tests 
add_subdirectory(tests)

add_library(OrderBookLib STATIC ${Headers} ${Sources})

# Add executable
add_executable(${This} src/main.cpp)

# Link Boost and OpenSSL libraries to the executable
target_link_libraries(${This} ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES} OrderBookLib)

# Add Boost and OpenSSL library directories to linker search path
link_directories(${BOOST_ROOT}/lib ${OPENSSL_LIB_DIR})
