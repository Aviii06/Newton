add_executable(main "main.cpp")

if (MSVC)
    set_target_properties(
            main PROPERTIES
            VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/")
endif ()

file(COPY ../assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/../assets/)

target_link_libraries(main
        Vivid)