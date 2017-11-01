add_subdirectory(glfw)

cmake_minimum_required(VERSION 3.0)

project(imgui)

# Copy glfw imgui implementation to sources directory
file(COPY 
    imgui/examples/opengl3_example/imgui_impl_glfw_gl3.cpp
    imgui/examples/opengl3_example/imgui_impl_glfw_gl3.h
    DESTINATION
    imgui)

file ( GLOB HEADERS imgui/*.h imgui/*.hpp)

file ( GLOB SOURCES imgui/*.cpp)

include_directories( "glfw/include" )
add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE imgui)
target_link_libraries( ${PROJECT_NAME} glfw)
