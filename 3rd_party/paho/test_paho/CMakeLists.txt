cmake_minimum_required(VERSION 3.1)


project(test_paho)

set(CMAKE_CXX_STANDARD 14)

set (THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)


SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")



add_executable(test_paho main.cpp)

include_directories(../include/)
file(GLOB PAHO_CPP_LIB ../lib/libpaho*.a)

target_link_libraries(test_paho ${PAHO_CPP_LIB} )
