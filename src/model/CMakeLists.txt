cmake_minimum_required(VERSION 3.0)

project(Model)

file ( GLOB HEADERS *.h *.hpp)

file ( GLOB SOURCES *.cpp)

add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR})
