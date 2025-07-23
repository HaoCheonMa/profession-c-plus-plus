cmake_minimum_required (VERSION 3.14.0)

get_filename_component(PROJECT_FOLDER_NAME ${CMAKE_SOURCE_DIR} NAME)
project(${PROJECT_FOLDER_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/includes/)
set(MY_SRC_DIR ${CMAKE_SOURCE_DIR}/src/) 

set(BUILD_CPR_TESTS OFF)
set(CMAKE_USE_OPENSSL OFF)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
                         GIT_TAG da40186618909b1a7363d4e4495aa899c6e0eb75) # Replace with your desired git commit from: https://github.com/libcpr/cpr/releases
FetchContent_MakeAvailable(cpr)

add_executable(${PROJECT_NAME} ${MY_SRC_DIR}/main.cpp ${MY_SRC_DIR}/tools.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${MY_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE cpr::cpr)