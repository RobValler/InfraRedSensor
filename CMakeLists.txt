#*****************************************************************
# * Copyright (C) 2017-   Robert Valler - All rights reserved.
# *
# * This file is part of the project: Auto
# *
# * This project can not be copied and/or distributed
# * without the express permission of the copyright holder
# *****************************************************************

cmake_minimum_required(VERSION 3.22.0)
project ( sensor_inf_red )
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set (CMAKE_CXX_STANDARD 17)
set (Wall)
set (W1)
set (Wfloat-conversion)

# Conan stuff
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

#PACKAGES ROS2
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
# add other ros2 packages here as well
#ament_package()

#INCLUDES
include_directories(${CMAKE_SOURCE_DIR}/src})

#SOURCE FILES
file(GLOB SOURCES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

file(GLOB HEADERS
    ${CMAKE_SOURCE_DIR}/src/*.h
)

#GENERATE - main app
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} )
target_link_libraries(${PROJECT_NAME}
                ${CONAN_LIBS}
)
                
#GENERATE - ROS2 
ament_target_dependencies(${PROJECT_NAME}
               rclcpp
               std_msgs
)                
