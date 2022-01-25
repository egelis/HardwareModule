cmake_minimum_required(VERSION 3.7)


project(HardwareModule)

set(CMAKE_CXX_STANDARD 17)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(EXECUTABLE_OUTPUT_PATH ../../../../bin)
set(MODBUSLIB
        "ModbusLib/modbus.cpp"
        "ModbusLib/modbus.hpp"
        "ModbusLib/modbus_ls.cpp"
        "ModbusLib/modbus_ls.hpp"
        "ModbusLib/modbus_ls_dust.cpp"
        "ModbusLib/modbus_ls_dust.hpp"
        "ModbusLib/serial.cpp"
        "ModbusLib/serial.hpp")

include_directories(../3rd_party/paho/include/)
include_directories(Template/)
file(GLOB PAHO_CPP_LIB ../3rd_party/paho/lib/libpaho*.a)


add_executable(HardwareModule main.cpp utils.h MqttClient.cpp MqttClient.h states.h stopwatch.h ${MODBUSLIB})
target_link_libraries(HardwareModule ${PAHO_CPP_LIB})
