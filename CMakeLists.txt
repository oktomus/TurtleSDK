cmake_minimum_required( VERSION 3.0 )


execute_process(
	COMMAND git submodule update --init --recursive
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_subdirectory(distant)

# Include directories common
include_directories( ${OPENGL_INCLUDE_DIRS} )
include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/distant/glm" )
include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/src" )
include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/distant/gl3w/include" )
include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/distant/imgui" )
include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/distant/glfw/include" )
include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/distant/stb" )

add_subdirectory(src)

##################################################################################
# Project
##################################################################################

project( TurtleSDK )

##################################################################################
# Non source files (shaders, models, textures)
##################################################################################

message(STATUS "Copy TurtleLib files into ${CMAKE_CURRENT_BINARY_DIR}/turtleLib")
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/turtleLib" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

##################################################################################
# Package Management
##################################################################################

find_package( OpenGL REQUIRED )

##################################################################################
# Include directories
##################################################################################


##################################################################################
# Program
##################################################################################

add_executable( ${PROJECT_NAME} "main.cpp")

##################################################################################
# Linked libraries
##################################################################################

target_link_libraries( ${PROJECT_NAME} ${OPENGL_gl_LIBRARY} )
target_link_libraries( ${PROJECT_NAME} gl3w )
target_link_libraries( ${PROJECT_NAME} glfw)
target_link_libraries( ${PROJECT_NAME} turtle)
target_link_libraries( ${PROJECT_NAME} imgui )
