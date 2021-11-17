cmake_minimum_required(VERSION 3.13.1)

project(pnut-butta)

message("")
message( STATUS "CMAKE_BINARY_DIR: " ${CMAKE_BINARY_DIR} )
message( STATUS "CMAKE_SOURCE_DIR: " ${CMAKE_SOURCE_DIR} )
message( STATUS "CMAKE_COMMAND: " ${CMAKE_COMMAND} )
message( STATUS "CMAKE_VERSION: " ${CMAKE_VERSION} )
message( STATUS "CMAKE_CXX_COMPILER: " ${CMAKE_CXX_COMPILER} )
message( STATUS "CMAKE_PROJECT_NAME: " ${CMAKE_PROJECT_NAME} )

set(COMPILE_FLAGS "-std=c++14 -Wall -Wextra -pedantic")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY CMAKE_CXX_COMPILER${CMAKE_BINARY_DIR}/bin)
set(HEADER_FILES
        thirdparty/flag.h
        include/GameOptions.hpp
        include/Game.hpp
        include/Util.hpp
        include/Colours.hpp)
set(SOURCE_FILES
        src/GameOptions.cpp
        src/Game.cpp
        src/Util.cpp
        src/main.cpp)

add_definitions(${COMPILE_FLAGS})
add_executable(${PROJECT_NAME}
        ${HEADER_FILES}
        ${SOURCE_FILES})

include_directories(
        include
        thirdparty)