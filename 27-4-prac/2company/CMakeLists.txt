cmake_minimum_required (VERSION 3.14.0)
project(2company)

set(MY_INCLUDE_DIR ${CMAKE_HOME_DIRECTORY}/includes/)
set(MY_SRC_DIR ${CMAKE_HOME_DIRECTORY}/src/) 

add_executable(2company ${MY_SRC_DIR}/main.cpp)
target_include_directories(2company PUBLIC ${MY_INCLUDE_DIR})