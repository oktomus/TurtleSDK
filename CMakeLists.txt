cmake_minimum_required( VERSION 3.0 )


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
find_package( GLUT REQUIRED )
find_package( GLEW REQUIRED )

##################################################################################
# Include directories
##################################################################################

#OpenGL
include_directories( ${OPENGL_INCLUDE_DIRS} )

# freeglut
if(NOT ${GLUT_FOUND})
    message("GLUT not found, using local includes")
    include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/libs/freeglut/include" )
else()
    include_directories( ${GLUT_INCLUDE_DIRS} )
endif()

# glew
if(NOT ${GLEW_FOUND})
    message("GLEW not found, using local includes")
    include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/libs/glew/include" )
else() 
    include_directories( ${GLEW_INCLUDE_DIRS} )
endif()

# glm
include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/libs/glm" )

# src 
include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/src" )


##################################################################################
# Program
##################################################################################

# Retrieve source files
file( GLOB incList "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" )
file( GLOB inlList "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp" )
file( GLOB srcList "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" )

# Target program
set( resList ${resList} ${inlList} )
set( resList ${resList} ${incList} )
add_executable( ${PROJECT_NAME} ${srcList} ${resList} )

##################################################################################
# Linked libraries
##################################################################################

# Opengl
target_link_libraries( ${PROJECT_NAME} ${OPENGL_gl_LIBRARY} )

# Glut

if(NOT ${GLUT_FOUND})
    target_link_libraries( ${PROJECT_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/libs/freeglut/lib64" )
else()
    target_link_libraries( ${PROJECT_NAME} ${GLUT_glut_LIBRARY} )
endif()

# Glew

if(NOT ${GLUT_FOUND})
    target_link_libraries( ${PROJECT_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/libs/glew/lib64" )
else()
    target_link_libraries( ${PROJECT_NAME} ${GLEW_LIBRARIES} )
endif() 

# Model
target_link_libraries( ${PROJECT_NAME} Model )
