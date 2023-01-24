add_executable(suzanne "suzanne_example.cpp")
if (MSVC)
    set_target_properties(
            suzanne PROPERTIES
            VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/")
endif ()

file(COPY ../../assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/../assets/)

target_link_libraries(suzanne
        NewtonRenderer)