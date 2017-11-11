cmake_minimum_required( VERSION 3.0 )
project( TurtleSDK )

##################################################################################
# Externals
##################################################################################
set(GLFW_ROOT "${CMAKE_SOURCE_DIR}/distant/glfw")
set(GL3W_ROOT "${CMAKE_SOURCE_DIR}/distant/gl3w")
set(GLM_ROOT "${CMAKE_SOURCE_DIR}/distant/glm")
set(IMGUI_ROOT "${CMAKE_SOURCE_DIR}/distant/imgui")
set(STB_ROOT "${CMAKE_SOURCE_DIR}/distant/stb")

set(GLFW_INC "${GLFW_ROOT}/include")
set(GL3W_INC "${GL3W_ROOT}/include")
set(GLM_INC "${GLM_ROOT}")
set(IMGUI_INC "${IMGUI_ROOT}")
set(STB_INC "${STB_ROOT}")

set(GL3W_SRC "${GL3W_ROOT}/src/gl3w.c")

if (NOT EXISTS ${GL3W_INC} OR
        NOT EXISTS ${GLFW_INC} OR
        NOT EXISTS ${GLM_INC} OR
        NOT EXISTS ${IMGUI_INC})
        message(STATUS "Updating submodules")
        execute_process(COMMAND git submodule init)
        execute_process(COMMAND git submodule update)
endif()

if (NOT EXISTS ${GL3W_SRC})
        message(STATUS "Generating gl3w source files")
        execute_process(COMMAND python gl3w_gen.py
                                        WORKING_DIRECTORY ${GL3W_ROOT})
endif()

if (NOT EXISTS ${IMGUI_ROOT}/imgui_impl_glfw_gl3.cpp OR
        NOT EXISTS ${IMGUI_ROOT}/imgui_impl_glfw_gl3.h)
    message(STATUS "Generating imgui glfw implementation files")
    file(COPY
        ${IMGUI_ROOT}/examples/opengl3_example/imgui_impl_glfw_gl3.cpp
        ${IMGUI_ROOT}/examples/opengl3_example/imgui_impl_glfw_gl3.h
        DESTINATION ${IMGUI_ROOT})
endif()

file (GLOB IMGUI_SRC "${IMGUI_ROOT}/*.cpp")

# Compile GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${GLFW_ROOT})

find_package(OpenGL REQUIRED)

include_directories(
        ${GLFW_INC}
        ${GL3W_INC}
        ${GLM_INC}
        ${OPENGL_INCLUDE_DIR}
        ${IMGUI_INC}
        ${STB_INC}
)

##################################################################################
# Non source files (shaders, models, textures)
##################################################################################

message(STATUS "Copy TurtleLib files into ${CMAKE_CURRENT_BINARY_DIR}/turtleLib")
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/turtleLib" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

##################################################################################
# Turtle LIB
##################################################################################

set(TURTLE_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

file( GLOB hfiles "${TURTLE_SRC_DIR}/*/*.h" )
file( GLOB cfiles "${TURTLE_SRC_DIR}/*/*.cpp" )
set( headers ${headers} ${hfiles} )
set( sources ${sources} ${cfiles} )

file( GLOB hfiles "${TURTLE_SRC_DIR}/*.h" )
file( GLOB cfiles "${TURTLE_SRC_DIR}/*.cpp" )
set( headers ${headers} ${hfiles} )
set( sources ${sources} ${cfiles} )


include_directories(
    ${TURTLE_SRC_DIR}/src
)


add_executable(
    ${PROJECT_NAME}
    ${sources}
    ${headers}
    ${GL3W_SRC}
    ${IMGUI_SRC}
    )

target_link_libraries(
    ${PROJECT_NAME}
    ${OPENGL_gl_LIBRARY}
    glfw
    )

target_include_directories(
    ${PROJECT_NAME} PRIVATE
    ${TURTLE_SRC_DIR}
    )
