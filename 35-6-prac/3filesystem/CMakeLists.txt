cmake_minimum_required (VERSION 3.14.0)

get_filename_component(PROJECT_FOLDER_NAME ${CMAKE_SOURCE_DIR} NAME)
project(${PROJECT_FOLDER_NAME})

set(MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/includes/)
set(MY_SRC_DIR ${CMAKE_SOURCE_DIR}/src/) 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} ${MY_SRC_DIR}/main.cpp ${MY_SRC_DIR}/tools.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${MY_INCLUDE_DIR})