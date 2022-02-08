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
    SerialPort )
    
find_package(Boost COMPONENTS system REQUIRED)
    

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

#--------------------------------------------------------
#-------------- Build with CATKIN (ROS1) ----------------
if( CATKIN_DEVEL_PREFIX OR catkin_FOUND OR CATKIN_BUILD_BINARY_PACKAGE)

    set(COMPILING_WITH_CATKIN 1)
    message(STATUS "COMPILING_WITH_CATKIN")
    add_definitions(-DCOMPILED_WITH_CATKIN)

    find_package(catkin REQUIRED COMPONENTS plotjuggler )
    catkin_package(
        CATKIN_DEPENDS plotjuggler
        )
    include_directories(${catkin_INCLUDE_DIRS})
    list(APPEND ${PJ_LIBRARIES} ${catkin_LIBRARIES} )
    set(PJ_PLUGIN_INSTALL_DIRECTORY ${CATKIN_PACKAGE_BIN_DESTINATION} )

    #--------------------------------------------------------
    #-------------- Build with AMENT (ROS2) -----------------
elseif( DEFINED ENV{AMENT_PREFIX_PATH})

    set(COMPILING_WITH_AMENT 1)
    message(STATUS "COMPILING_WITH_CATKIN")
    add_definitions(-DCOMPILED_WITH_AMENT)

    find_package(ament_cmake REQUIRED)
    find_package(plotjuggler REQUIRED)
    set(PJ_PLUGIN_INSTALL_DIRECTORY lib/${PROJECT_NAME} )

    #--------------------------------------------------------
    #------------- Build without any ROS support ------------
else()

    find_package(PlotJuggler REQUIRED)
    message(STATUS "PlotJuggler FOUND")

    include_directories(${PlotJuggler_INCLUDE_DIRS})
    list(APPEND ${PJ_LIBRARIES} ${PlotJuggler_LIBRARIES} )
    set(PJ_PLUGIN_INSTALL_DIRECTORY bin )

endif()

#------- Create the libraries -------

QT5_WRAP_UI ( UI_SRC asservstreamcontrolpanel.ui )
SET( SRC
    AsservStream_uartDecoder.cpp
    AsservStream.cpp
    AsservStreamControlPanel.cpp
    )

add_library(AsservStream SHARED ${SRC} ${UI_SRC}  )

target_link_libraries(AsservStream
    ${PJ_LIBRARIES} ${Qt5Widgets_LIBRARIES} ${Qt5Xml_LIBRARIES} ${Qt5SerialPort_LIBRARIES} ${Boost_SYSTEM_LIBRARY} plotjuggler_base)
target_compile_definitions(AsservStream PRIVATE PLUGIN_NAME="Esial Robotik asserv stream")



if (COMPILING_WITH_AMENT)
    ament_target_dependencies(PlotJugglerStreamSample plotjuggler)
endif()
#------- Install the libraries -------

install(
    TARGETS
        AsservStream
    DESTINATION
        ${PJ_PLUGIN_INSTALL_DIRECTORY}  )

