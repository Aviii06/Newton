#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include "Shapes.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "utils/timer.h"

int main(void)
{
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
    {
        return -1;
    }

    //FOR MACOS
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    int Width = 640, Height = 400;
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(Width, Height, "Newton", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glEnable(GL_DEPTH_TEST);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "F";
    }

    // Postions of the vertex
    float size = 100.0f;
    // float positions[] = {
    //     -size, size, -size,         0.0, 0.0,           0.1, 0.3, 0.8,
    //     size, size, -size,          1.0, 0.0,           0.8, 0.44, 0.32,
    //     -size, -size, -size,        1.0, 1.0,           0.12, 0.5, 0.21,
    //     size, -size, -size,         0.0, 1.0,           0.144, 0.33, 0.48, 
    //     -size, size, size,          0.0, 0.0,           0.52, 0.23, 0.21,
    //     size, size, size,           1.0, 0.0,           0.25, 0.43, 0.71,   
    //     -size, -size, size,         1.0, 1.0,           0.56, 0.35, 0.19,
    //     size, -size, size,          0.0, 1.0,           0.34, 0.31, 0.43,
    // };
    // unsigned int indices[] = {
    //     0, 1, 2, // Side 0
    //     2, 1, 3,
    //     4, 0, 6, // Side 1
    //     6, 0, 2,
    //     7, 5, 6, // Side 2
    //     6, 5, 4,
    //     3, 1, 7, // Side 3 
    //     7, 1, 5,
    //     4, 5, 0, // Side 4 
    //     0, 5, 1,
    //     3, 7, 2, // Side 5 
    //     2, 7, 6
    // };

    shape::quad3d q(size);
    float* positions = q.getPositions();
    unsigned int* indices = q.getIndices();
    size_t indSize = q.getIndicesSize();
    size_t posSize = q.getPositionsSize();

    GLCall( glEnable(GL_BLEND) );
    GLCall( glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) );

    VertexArray va;
    VertexBuffer vb(positions, posSize);

    IndexBuffer ib(indices, indSize);

    VertexBufferLayout layout;
    layout.AddFloat(3); // Positions
    layout.AddFloat(2); // Tex coords
    layout.AddFloat(3); // Colors

    va.AddBuffer(vb, layout);

    Shader shader("../assets/shaders/Basic.vertexShader.hlsl", "../assets/shaders/basic.pixelShader.hlsl");
    shader.Bind();

    Texture texture("../assets/textures/mandelbrot.png");
    texture.Bind();

    Timer timer;
    float time = timer.getTimeMs();

    //Shader
    shader.SetUniform1i("u_Texture", 0);
    shader.SetUniform1f("u_Time", time);

    float aspect = (float)Width/Height;
    shader.SetUniform1f("u_Aspect", aspect);

    Renderer renderer;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(window, true);
    ImGui::StyleColorsDark();

    //MVP matrix 
    glm::mat4 projectionMatrix = glm::ortho(0.0f, (float)Width,
                                            0.0f, (float)Height,
                                             -1.0f, 1.0f);
    
    float field_of_view = 45.0f;
    float closestDistance = 0.1f;
    float farthestDistance = 500.0f;
    
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0,0,0));
    glm::mat4 viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0,0,0));

    glm::vec3 translationModel(0, 0, -300.0);
    glm::vec3 translationView(0, 0, 0);

    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.Clear();

        modelMatrix = glm::translate(glm::mat4(1.0f), translationModel);
        viewMatrix = glm::translate(glm::mat4(1.0f), translationView);
        
        float rotation = time/100.0;
        modelMatrix = glm::rotate(modelMatrix,  glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));

        shader.Bind();
        shader.SetUniform4f("u_Color", 0.1, 0.3, 0.8, 1.0);
        time = timer.getTimeMs();

        projectionMatrix = glm::perspective(glm::radians(field_of_view), aspect, closestDistance, farthestDistance);
            
        shader.SetUniform1f("u_Time", time);
        shader.SetUniformMat4f("u_Model", modelMatrix);
        shader.SetUniformMat4f("u_View", viewMatrix);
        shader.SetUniformMat4f("u_Proj", projectionMatrix);

        renderer.Draw(va, ib, shader);
        
        // IMGUI
        ImGui_ImplGlfwGL3_NewFrame();

        ImGui::SliderFloat3("Translation1", &translationModel.x, -960.0f, 960.0f);
        ImGui::SliderFloat("Field of View", &field_of_view, 15.0f, 90.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
        glClear(GL_DEPTH_BUFFER_BIT);
    }

    glfwTerminate();
    return 0;
}
