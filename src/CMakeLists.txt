set(SOURCES
        IndexBuffer.cpp
        IndexBuffer.h
        Intersections.h
        Mesh.cpp
        Mesh.h
        OBJLoader.h
        RenderedTexture.cpp
        RenderedTexture.h
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

target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})

if (MSVC)
    set_target_properties(
            ${PROJECT_NAME} PROPERTIES
            VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/")
endif ()

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
        PRIVATE glad
        )
