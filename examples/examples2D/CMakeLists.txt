add_executable(renderer2d "renderer_2D_example.cpp")
add_executable(marchingSquare "marching_squares.cpp")

if (MSVC)
    set_target_properties(
            renderer2d PROPERTIES
            VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/")
    set_target_properties(
            renderer2d PROPERTIES
            VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/")
endif ()

file(COPY ../../assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/../assets/)

target_link_libraries(renderer2d
        Vivid)
target_link_libraries(marchingSquare
        Vivid)