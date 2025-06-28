cmake_minimum_required(VERSION 3.10.0)
project(computer VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)
set(MY_INCLUDE_DIR ${CMAKE_HOME_DIRECTORY}/include/)
#message(STATUS "CMAKE_SOURCE_DIR = ${CMAKE_HOME_DIRECTORY}/include")

add_subdirectory(src)