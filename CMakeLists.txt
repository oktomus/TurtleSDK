cmake_minimum_required( VERSION 3.0 )

add_subdirectory(distant)
add_subdirectory(src)

##################################################################################
# Project
##################################################################################

project( TurtleSDK )

##################################################################################
# Package Management
##################################################################################

# OpenGL
find_package( OpenGL REQUIRED )

##################################################################################
# Include directories
##################################################################################

#OpenGL
include_directories( ${OPENGL_INCLUDE_DIRS} )

# glm
include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/distant/glm" )

# src 
include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/src" )
include_directories( "${CMAKE_CURRENT_SOURCE_DIR}" )

# gl3w
include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/distant/gl3w/includ" )
# imgui
include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/distant/imgui" )
# glfw
include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/distant/glfw/include" )


##################################################################################
# Program
##################################################################################

# Retrieve source files
file( GLOB incList "${CMAKE_CURRENT_SOURCE_DIR}/*.h" )
file( GLOB inlList "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp" )
file( GLOB srcList "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" )

# Target program
set( resList ${resList} ${inlList} )
set( resList ${resList} ${incList} )
add_executable( ${PROJECT_NAME} ${srcList} ${resList} )

##################################################################################
# Linked libraries
##################################################################################

# Opengl
target_link_libraries( ${PROJECT_NAME} ${OPENGL_gl_LIBRARY} )

target_link_libraries( ${PROJECT_NAME} gl3w )
target_link_libraries( ${PROJECT_NAME} glfw)
target_link_libraries( ${PROJECT_NAME} turtle)
target_link_libraries( ${PROJECT_NAME} imgui )
