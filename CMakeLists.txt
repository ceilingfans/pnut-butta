cmake_minimum_required(VERSION 3.13.1)

message("")
message( STATUS "CMAKE_BINARY_DIR: " ${CMAKE_BINARY_DIR} )
message( STATUS "CMAKE_SOURCE_DIR: " ${CMAKE_SOURCE_DIR} )
message( STATUS "CMAKE_COMMAND: " ${CMAKE_COMMAND} )
message( STATUS "CMAKE_VERSION: " ${CMAKE_VERSION} )
message( STATUS "CMAKE_C_COMPILER: " ${CMAKE_C_COMPILER} )
message( STATUS "CMAKE_PROJECT_NAME: " ${CMAKE_PROJECT_NAME} )
message( STATUS "CMAKE_FINDCMAKE: " ${CMAKE_SOURCE_DIR}/CMAKE )

project(pnut-butta)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(HEADER_FILES
        thirdparty/flag.h
        include/GameOptions.hpp
        include/Game.hpp
        include/Util.hpp)
set(SOURCE_FILES
        src/Game.cpp
        src/Util.cpp
        src/main.cpp)

add_executable(${PROJECT_NAME}
        ${HEADER_FILES}
        ${SOURCE_FILES})

include_directories(
        include
        thirdparty)