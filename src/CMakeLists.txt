set(HEADERS UI/UI.h UI/MenuBar.h UI/UIHeaders.h)
set(SOURCES UI/UI.cpp UI/MenuBar.cpp)

add_executable(Newton "main.cpp" ${HEADERS} ${SOURCES})

if (MSVC)
    set_target_properties(
            main PROPERTIES
            VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/")
endif ()

file(COPY ../assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/../assets/)

target_link_libraries(Newton
        Vivid)