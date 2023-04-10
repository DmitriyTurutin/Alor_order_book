cmake_minimum_required(VERSION 3.5)

project(my_project)

# Set Boost directories
set(BOOST_ROOT "/usr/local")
set(Boost_INCLUDE_DIRS "${BOOST_ROOT}/include")
set(Boost_LIBRARIES "${BOOST_ROOT}/lib/libboost_system.a" "${BOOST_ROOT}/lib/libboost_filesystem.a")

# Set OpenSSL directories
set(OPENSSL_ROOT_DIR "/usr")
find_package(OpenSSL REQUIRED)

# Add include directories for Boost and OpenSSL libraries
include_directories(${Boost_INCLUDE_DIRS} ${OPENSSL_INCLUDE_DIR})

# Add executable
add_executable(my_project src/main.cpp src/OrderBook.cpp src/OrderBook.h src/SSL_Client.cpp src/SSL_Client.h)

# Link Boost and OpenSSL libraries to the executable
target_link_libraries(my_project ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES})

# Add Boost and OpenSSL library directories to linker search path
link_directories(${BOOST_ROOT}/lib ${OPENSSL_LIB_DIR})
