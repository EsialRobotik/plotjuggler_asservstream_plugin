cmake_minimum_required(VERSION 3.7)

project(plotjuggler_asservStream)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g  -O2 -fno-omit-frame-pointer")
set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -O2")

set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake"
    )

#-------  Include Qt dependencies -------
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTOUIC ON)

find_package(Qt5 REQUIRED COMPONENTS
    Core
    Widgets
    Concurrent
    Xml
    Svg
    WebSockets
    SerialPort)
    
include_directories(
    3rdparty
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5Concurrent_INCLUDE_DIRS}
    ${Qt5Xml_INCLUDE_DIRS}
    ${Qt5WebSockets_INCLUDE_DIRS}
    ${Qt5Svg_INCLUDE_DIRS}
    ${Qt5SerialPort_INCLUDE_DIRS}
    )

set(QT_LIBRARIES
    Qt5::Core
	Qt5::Widgets
	Qt5::Concurrent
	Qt5::Xml
	Qt5::Svg
	Qt5::WebSockets
	Qt5::SerialPort)

add_definitions( ${QT_DEFINITIONS} -DQT_PLUGIN )
set( PJ_LIBRARIES ${QT_LIBRARIES} )



find_package(PlotJuggler REQUIRED)
message(STATUS "PlotJuggler FOUND")

find_library(libconfig config++)
message(STATUS "libconfig FOUND")

include_directories(${PlotJuggler_INCLUDE_DIRS})
list(APPEND ${PJ_LIBRARIES} ${PlotJuggler_LIBRARIES} )
set(PJ_PLUGIN_INSTALL_DIRECTORY bin )


#------- Create the libraries -------

QT5_WRAP_UI ( UI_SRC asservstreamcontrolpanel.ui )
SET( SRC
    AsservStream_uartDecoder.cpp
    AsservStream.cpp
    AsservStreamControlPanel.cpp
    )

add_library(AsservStream SHARED ${SRC} ${UI_SRC}  )

target_link_libraries(AsservStream
    ${PJ_LIBRARIES} ${Qt5Widgets_LIBRARIES} ${Qt5Xml_LIBRARIES} ${Qt5SerialPort_LIBRARIES}  plotjuggler_base config++)
    
    
get_filename_component(pluginBuildDir "." REALPATH BASE_DIR "${CMAKE_BINARY_DIR}")    
target_compile_definitions(AsservStream PRIVATE PLUGIN_NAME="Esial Robotik asserv stream" PLUGIN_BUIL_DIR="${pluginBuildDir}")


configure_file(network_struct.cfg network_struct.cfg COPYONLY)

#------- Install the libraries -------

install(
    TARGETS
        AsservStream
    DESTINATION
        ${PJ_PLUGIN_INSTALL_DIRECTORY}  )

