cmake_minimum_required(VERSION 3.7)

project(HardwareGUI VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#set(Qt5Mqtt_DIR "../../../external_libs/ls_mqtt/lib/cmake/Qt5Mqtt")

find_package(QT NAMES Qt5 COMPONENTS Widgets Network Mqtt REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Network Mqtt REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        topicfilterproxymodel.h
        topicfilterproxymodel.cpp
	logmodel.cpp
	logmodel.h
	topics.h
)

set(MODBUSLIB "../../Common/ModbusLib/modbus.cpp"
        "../../Common/ModbusLib/modbus.hpp"
        "../../Common/ModbusLib/modbus_ls.hpp"
        "../../Common/ModbusLib/modbus_ls.cpp"
        "../../Common/ModbusLib/modbus_ls_dust.cpp"
        "../../Common/ModbusLib/modbus_ls_dust.hpp"
        "../../Common/ModbusLib/serial.cpp"
        "../../Common/ModbusLib/serial.hpp"
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(HardwareGUI
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(HardwareGUI SHARED
            ${PROJECT_SOURCES}
            ${MODBUSLIB}
        )
    else()
        add_executable(HardwareGUI
            ${PROJECT_SOURCES}
            ${MODBUSLIB}
        )
    endif()
endif()

target_link_libraries(HardwareGUI PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network Qt${QT_VERSION_MAJOR}::Mqtt)

set_target_properties(HardwareGUI PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(HardwareGUI)
endif()
