set(SOURCES
        Camera.cpp
        Camera.h
        IndexBuffer.cpp
        IndexBuffer.h
        Intersections.h
        Mesh.cpp
        Mesh.h
        OBJLoader.h
        renderedTexture.cpp
        renderedTexture.h
        Renderer.cpp
        Renderer.h
        Shader.cpp
        Shader.h
        Shapes.cpp
        Shapes.h
        Texture.cpp
        Texture.h
        VertexArray.cpp
        VertexArray.h
        VertexBuffer.cpp
        VertexBuffer.h
        VertexBufferLayout.h
        common/types.h
        utils/error.cpp
        utils/error.h
        utils/timer.cpp
        utils/timer.h
        )
#
#add_library(sources STATIC ${SOURCES})
#
#
#target_include_directories(sources PUBLIC
#        ${PROJECT_SOURCE_DIR}/vendor
#        ${PROJECT_SOURCE_DIR}/src
#        )
#
#target_link_libraries(sources
#        PRIVATE glfw
#        PRIVATE libglew_static
#        PRIVATE glm
#        PRIVATE common
#        PUBLIC stb
#        PUBLIC imgui
#        )
#
#LINK_DIRECTORIES(
#        "${CMAKE_BINARY_DIR}/src/"
#)

target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})

if(MSVC)
    set_target_properties(
            ${PROJECT_NAME} PROPERTIES
            VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/")
endif()

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../assets/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/../assets/)

target_include_directories(${PROJECT_NAME} PUBLIC
        ${PROJECT_SOURCE_DIR}/vendor
        )

target_link_libraries(${PROJECT_NAME}
        PRIVATE glfw
        PRIVATE libglew_static
        PRIVATE glm
        PUBLIC imgui
        PUBLIC stb
        )

macro(ADD_FRAMEWORK fwname appname)
    find_library(FRAMEWORK_${fwname}
            NAMES ${fwname}
            PATHS ${CMAKE_OSX_SYSROOT}/System/Library
            PATH_SUFFIXES Frameworks
            NO_DEFAULT_PATH)
    if( ${FRAMEWORK_${fwname}} STREQUAL FRAMEWORK_${fwname}-NOTFOUND)
        MESSAGE(ERROR ": Framework ${fwname} not found")
    else()
        TARGET_LINK_LIBRARIES(${appname} PRIVATE ${FRAMEWORK_${fwname}})
        MESSAGE(STATUS "Framework ${fwname} found at ${FRAMEWORK_${fwname}}")
    endif()
endmacro(ADD_FRAMEWORK)

add_framework(OpenGl ${PROJECT_NAME})
add_framework(Cocoa ${PROJECT_NAME})
add_framework(IOKit ${PROJECT_NAME})
add_framework(CoreVideo ${PROJECT_NAME})
add_framework(CoreFoundation ${PROJECT_NAME})
add_framework(GLUT ${PROJECT_NAME})
