
cmake_minimum_required(VERSION 3.0.0)
project(test_app)

## Target
set(CMAKE_CXX_STANDARD 11)

set(HEADERS ${HEADERS}
    TimeoutSerial.h
    iniconfig.hpp
    TLV.h
    MethodDecider.h
    GetData.h
)

set(SOURCES ${SOURCES}
    TimeoutSerial.cpp
    iniconfig.cpp
    TLV.cpp
    MethodDecider.cpp
    GetData.cpp
    main.cpp
)

add_executable(${CMAKE_PROJECT_NAME} ${HEADERS} ${SOURCES})

if(APPLE AND EXISTS /usr/local/opt/openssl/include)
    set(OPENSSL_ROOT_DIR /usr/local/opt/openssl/include)
endif()

## Link libraries
set(BOOST_LIBS date_time system chrono thread)
#find_package(cpprestsdk REQUIRED NAMES cpprest cpprestsdk)
find_package(Boost COMPONENTS ${BOOST_LIBS} REQUIRED)

find_package(Threads REQUIRED)
find_package (OpenSSL REQUIRED)

INCLUDE_DIRECTORIES(
    /usr/include/cpprest
    /usr/include/pplx
)
#LINK_DIRECTORIES(usr/lib/x86_64-linux-gnu)

target_link_libraries(${CMAKE_PROJECT_NAME}
    ${CMAKE_THREAD_LIBS_INIT} 
    ${Boost_LIBRARIES} 
    ${OPENSSL_SSL_LIBRARY} 
    ${OPENSSL_CRYPTO_LIBRARY} 
    #cpprestsdk::cpprest
)