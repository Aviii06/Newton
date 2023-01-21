set(SOURCES
        inputs/InputHandler.cpp
        renderer/IndexBuffer.cpp
        renderer/Mesh.cpp
        renderer/Renderer.cpp
        renderer/Shader.cpp
        renderer/Texture.cpp
        renderer/VertexArray.cpp
        renderer/VertexBuffer.cpp
        renderer/Camera.cpp
        renderer/PointLight.cpp
        renderer/shapes/Quad3d.cpp
        renderer/shapes/Sphere.cpp
        Editor/Window.cpp
        Editor/Application.cpp
        renderer/Camera.cpp
        renderer/PointLight.cpp
        renderer/shapes/Quad3d.cpp
        renderer/shapes/Sphere.cpp
        utils/error.cpp
        utils/timer.cpp
        )

set(HEADERS
        inputs/InputHandler.h
        renderer/IndexBuffer.h
        renderer/Mesh.h
        renderer/Renderer.h
        renderer/Shader.h
        renderer/shapes/Shape.h
        renderer/Texture.h
        renderer/VertexArray.h
        renderer/VertexBuffer.h
        renderer/VertexBufferLayout.h
        renderer/Camera.h
        renderer/PointLight.h
        renderer/shapes/Quad3d.h
        renderer/shapes/Sphere.h
        Editor/Window.h
        Editor/Application.h
        renderer/Camera.h
        renderer/PointLight.h
        renderer/shapes/Quad3d.h
        renderer/shapes/Sphere.h
        common/types.h
        confs/Config.h
        utils/error.h
        utils/timer.h
        NewtonRenderer.h
        )

add_library(NewtonRenderer SHARED ${SOURCES} ${HEADERS})


target_include_directories(NewtonRenderer PUBLIC
        ${PROJECT_SOURCE_DIR}/vendor
        )

target_link_libraries(NewtonRenderer
        glfw
        libglew_static
        glm
        imgui
        stb
        glad
        )
