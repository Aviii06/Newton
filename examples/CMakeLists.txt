add_executable(suzanne SuzanneExample.cpp)
add_executable(renderer2d Renderer2DExample.cpp)

if (MSVC)
    set_target_properties(
            suzanne PROPERTIES
            VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/")
    set_target_properties(
            renderer2d PROPERTIES
            VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/")
endif ()

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../assets/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/../assets/)

target_link_libraries(suzanne
        NewtonRenderer)
target_link_libraries(renderer2d
        NewtonRenderer)