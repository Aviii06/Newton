set(SOURCES
        inputs/InputHandler.cpp
        inputs/InputHandler.h
        renderer/IndexBuffer.cpp
        renderer/IndexBuffer.h
        renderer/Mesh.cpp
        renderer/Mesh.h
        renderer/Renderer.cpp
        renderer/Renderer.h
        renderer/Shader.cpp
        renderer/Shader.h
        renderer/shapes/Shape.h
        renderer/Texture.cpp
        renderer/Texture.h
        renderer/VertexArray.cpp
        renderer/VertexArray.h
        renderer/VertexBuffer.cpp
        renderer/VertexBuffer.h
        renderer/VertexBufferLayout.h
        renderer/Camera.cpp
        renderer/Camera.h
        renderer/PointLight.cpp
        renderer/PointLight.h
        renderer/shapes/Quad3d.cpp
        renderer/shapes/Quad3d.h
        renderer/shapes/Sphere.cpp
        renderer/shapes/Sphere.h
        Editor/Window.cpp
        Editor/Window.h
        Editor/Application.cpp
        Editor/Application.h
        renderer/Camera.cpp
        renderer/Camera.h
        renderer/PointLight.cpp
        renderer/PointLight.h
        renderer/shapes/Quad3d.cpp
        renderer/shapes/Quad3d.h
        renderer/shapes/Sphere.cpp
        renderer/shapes/Sphere.h
        common/types.h
        confs/Config.h
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
