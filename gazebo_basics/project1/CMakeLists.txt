cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

find_package(gazebo REQUIRED)
include_directories(${GAZEBO_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS})
list(APPEND CMAKE_CXX_FLAGS "${GAZEBO_CXX_FLAGS}")

add_library(welcome SHARED script/welcome.cpp)
target_link_libraries(welcome ${GAZEBO_LIBRARIES})

# export GAZEBO_PLUGIN_PATH=${GAZEBO_PLUGIN_PATH}:/home/sherlock/Desktop/robotics_software_nd/gazebo_basics/project1/build
