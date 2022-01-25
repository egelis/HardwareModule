# Install script for directory: /home/egoreli/Prog/dust-uv_2021_09_29/external_libs/paho/build_paho/paho.mqtt.cpp-master/src/mqtt

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/egoreli/Prog/dust-uv_2021_09_29/external_libs/paho/build_paho/build_paho_cpp")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/../../include/mqtt" TYPE FILE FILES
    "/home/egoreli/Prog/dust-uv_2021_09_29/external_libs/paho/build_paho/paho.mqtt.cpp-master/src/mqtt/async_client.h"
    "/home/egoreli/Prog/dust-uv_2021_09_29/external_libs/paho/build_paho/paho.mqtt.cpp-master/src/mqtt/buffer_ref.h"
    "/home/egoreli/Prog/dust-uv_2021_09_29/external_libs/paho/build_paho/paho.mqtt.cpp-master/src/mqtt/buffer_view.h"
    "/home/egoreli/Prog/dust-uv_2021_09_29/external_libs/paho/build_paho/paho.mqtt.cpp-master/src/mqtt/callback.h"
    "/home/egoreli/Prog/dust-uv_2021_09_29/external_libs/paho/build_paho/paho.mqtt.cpp-master/src/mqtt/client.h"
    "/home/egoreli/Prog/dust-uv_2021_09_29/external_libs/paho/build_paho/paho.mqtt.cpp-master/src/mqtt/connect_options.h"
    "/home/egoreli/Prog/dust-uv_2021_09_29/external_libs/paho/build_paho/paho.mqtt.cpp-master/src/mqtt/create_options.h"
    "/home/egoreli/Prog/dust-uv_2021_09_29/external_libs/paho/build_paho/paho.mqtt.cpp-master/src/mqtt/delivery_token.h"
    "/home/egoreli/Prog/dust-uv_2021_09_29/external_libs/paho/build_paho/paho.mqtt.cpp-master/src/mqtt/disconnect_options.h"
    "/home/egoreli/Prog/dust-uv_2021_09_29/external_libs/paho/build_paho/paho.mqtt.cpp-master/src/mqtt/exception.h"
    "/home/egoreli/Prog/dust-uv_2021_09_29/external_libs/paho/build_paho/paho.mqtt.cpp-master/src/mqtt/iaction_listener.h"
    "/home/egoreli/Prog/dust-uv_2021_09_29/external_libs/paho/build_paho/paho.mqtt.cpp-master/src/mqtt/iasync_client.h"
    "/home/egoreli/Prog/dust-uv_2021_09_29/external_libs/paho/build_paho/paho.mqtt.cpp-master/src/mqtt/iclient_persistence.h"
    "/home/egoreli/Prog/dust-uv_2021_09_29/external_libs/paho/build_paho/paho.mqtt.cpp-master/src/mqtt/message.h"
    "/home/egoreli/Prog/dust-uv_2021_09_29/external_libs/paho/build_paho/paho.mqtt.cpp-master/src/mqtt/properties.h"
    "/home/egoreli/Prog/dust-uv_2021_09_29/external_libs/paho/build_paho/paho.mqtt.cpp-master/src/mqtt/response_options.h"
    "/home/egoreli/Prog/dust-uv_2021_09_29/external_libs/paho/build_paho/paho.mqtt.cpp-master/src/mqtt/server_response.h"
    "/home/egoreli/Prog/dust-uv_2021_09_29/external_libs/paho/build_paho/paho.mqtt.cpp-master/src/mqtt/ssl_options.h"
    "/home/egoreli/Prog/dust-uv_2021_09_29/external_libs/paho/build_paho/paho.mqtt.cpp-master/src/mqtt/string_collection.h"
    "/home/egoreli/Prog/dust-uv_2021_09_29/external_libs/paho/build_paho/paho.mqtt.cpp-master/src/mqtt/subscribe_options.h"
    "/home/egoreli/Prog/dust-uv_2021_09_29/external_libs/paho/build_paho/paho.mqtt.cpp-master/src/mqtt/thread_queue.h"
    "/home/egoreli/Prog/dust-uv_2021_09_29/external_libs/paho/build_paho/paho.mqtt.cpp-master/src/mqtt/token.h"
    "/home/egoreli/Prog/dust-uv_2021_09_29/external_libs/paho/build_paho/paho.mqtt.cpp-master/src/mqtt/topic.h"
    "/home/egoreli/Prog/dust-uv_2021_09_29/external_libs/paho/build_paho/paho.mqtt.cpp-master/src/mqtt/types.h"
    "/home/egoreli/Prog/dust-uv_2021_09_29/external_libs/paho/build_paho/paho.mqtt.cpp-master/src/mqtt/will_options.h"
    )
endif()

