
cmake_minimum_required(VERSION 3.0.0)
project(serio)

## Target
set(CMAKE_CXX_STANDARD 11)

set(HEADERS ${HEADERS}
    adapter.h
    package.h
    TimeoutSerial.h
    TLV.h
    iniconfig.hpp
    MethodDecider.h
    CheckData.h
    httpClientHandler.hpp
)

set(SOURCES ${SOURCES}
    main.cpp
    TimeoutSerial.cpp
    TLV.cpp 
    adapter.cpp
    iniconfig.cpp
    MethodDecider.cpp
    CheckData.cpp
    httpClientHandler.cpp
)

add_executable(${CMAKE_PROJECT_NAME} ${HEADERS} ${SOURCES})

if(APPLE AND EXISTS /usr/local/opt/openssl/include)
    set(OPENSSL_ROOT_DIR /usr/local/opt/openssl/include)
endif()

## Link libraries
set(BOOST_LIBS date_time system chrono thread)

#find_package(cpprest REQUIRED NAMES libcpprest)
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
    /usr/lib/x86_64-linux-gnu/libcpprest.so
)