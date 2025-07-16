cmake_minimum_required (VERSION 3.14.0)
project(3elfs)

set(MY_INCLUDE_DIR ${CMAKE_HOME_DIRECTORY}/includes/)
set(MY_SRC_DIR ${CMAKE_HOME_DIRECTORY}/src/) 

add_executable(3elfs ${MY_SRC_DIR}/main.cpp)
target_include_directories(3elfs PUBLIC ${MY_INCLUDE_DIR})