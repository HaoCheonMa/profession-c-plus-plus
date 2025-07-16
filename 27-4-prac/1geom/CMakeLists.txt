cmake_minimum_required (VERSION 3.14.0)
project(1geom)

set(MY_INCLUDE_DIR ${CMAKE_HOME_DIRECTORY}/includes/)
set(MY_SRC_DIR ${CMAKE_HOME_DIRECTORY}/src/) 

add_executable(1geom ${MY_SRC_DIR}/main.cpp)
target_include_directories(1geom PUBLIC ${MY_INCLUDE_DIR})