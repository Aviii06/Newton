set(SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/inputs/InputHandler.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer/IndexBuffer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer/Mesh.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer/Renderer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer/Shader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer/Texture.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer/VertexArray.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer/VertexBuffer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer/Camera.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer/PointLight.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer/shapes/Quad3d.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer/shapes/Sphere.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Editor/Window.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Editor/Application.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer/Camera.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer/PointLight.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer/shapes/Quad3d.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer/shapes/Sphere.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/utils/Error.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/utils/Timer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/UI.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer/Renderer2D.cpp
        )

set(HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/inputs/InputHandler.h
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer/IndexBuffer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer/Mesh.h
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer/Renderer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer/Shader.h
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer/shapes/Shape.h
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer/Texture.h
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer/VertexArray.h
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer/VertexBuffer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer/VertexBufferLayout.h
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer/Camera.h
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer/PointLight.h
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer/shapes/Quad3d.h
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer/shapes/Sphere.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Editor/Window.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Editor/Application.h
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer/Camera.h
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer/PointLight.h
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer/shapes/Quad3d.h
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer/shapes/Sphere.h
        ${CMAKE_CURRENT_SOURCE_DIR}/common/Types.h
        ${CMAKE_CURRENT_SOURCE_DIR}/confs/Config.h
        ${CMAKE_CURRENT_SOURCE_DIR}/utils/Error.h
        ${CMAKE_CURRENT_SOURCE_DIR}/utils/Timer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer/Renderer2D.h
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/UI.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Vivid.h
        )

add_library(Vivid SHARED ${SOURCES} ${HEADERS})

target_include_directories(Vivid PUBLIC
        ${PROJECT_SOURCE_DIR}/src
        )

target_include_directories(Vivid PUBLIC
        ${PROJECT_SOURCE_DIR}/vendor
        )

target_link_libraries(Vivid
        glfw
        libglew_static
        glm
        imgui
        stb
        glad
        )
