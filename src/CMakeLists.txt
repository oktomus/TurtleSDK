project(turtle)


file( GLOB hfiles "${CMAKE_CURRENT_SOURCE_DIR}/model/*.h" )
file( GLOB cfiles "${CMAKE_CURRENT_SOURCE_DIR}/model/*.cpp" )
set( headers ${headers} ${hfiles} )
set( sources ${sources} ${cfiles} )

file( GLOB hfiles "${CMAKE_CURRENT_SOURCE_DIR}/shader/*.h" )
file( GLOB cfiles "${CMAKE_CURRENT_SOURCE_DIR}/shader/*.cpp" )
set( headers ${headers} ${hfiles} )
set( sources ${sources} ${cfiles} )

file( GLOB hfiles "${CMAKE_CURRENT_SOURCE_DIR}/camera/*.h" )
file( GLOB cfiles "${CMAKE_CURRENT_SOURCE_DIR}/camera/*.cpp" )
set( headers ${headers} ${hfiles} )
set( sources ${sources} ${cfiles} )

file( GLOB hfiles "${CMAKE_CURRENT_SOURCE_DIR}/*.h" )
file( GLOB cfiles "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" )
set( headers ${headers} ${hfiles} )
set( sources ${sources} ${cfiles} )


add_library(${PROJECT_NAME} ${headers} ${sources})
target_link_libraries( ${PROJECT_NAME} glfw)
target_link_libraries( ${PROJECT_NAME} gl3w)

target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR})
