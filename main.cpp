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
#include "OBJLoader.h"
#include "Mesh.h"

#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include "utils/timer.h"

int main(void)
{
    GLFWwindow* window;

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
    
    Vector<Vertex> verts;
    Vector<unsigned int> inds;

    loadOBJ("../assets/obj/monkey.obj", verts, inds);

    Vector<Vertex> verts2;
    Vector<unsigned int> inds2;
    loadOBJ("../assets/obj/0.obj", verts2, inds2);

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    // GLCall( glEnable(GL_CULL_FACE) );

    VertexBufferLayout layout;
    layout.AddFloat(3); // Positions
    layout.AddFloat(2); // Tex coords
    layout.AddFloat(3); // Colors
    layout.AddFloat(3); // Normal
    layout.AddFloat(1); // isLit

    Renderer renderer;
    Renderer renderer2;

    Shader shader("../assets/shaders/phong.vertexShader.hlsl", "../assets/shaders/phong.pixelShader.hlsl");
    shader.Bind();

    Shader shader2("../assets/shaders/phong.vertexShader.hlsl", "../assets/shaders/phong.pixelShader.hlsl");
    shader2.Bind();

    Texture texture("../assets/textures/mandelbrot.png");
    texture.Bind();

    Texture texture2("../assets/textures/mandelbrot.png");
    texture2.Bind();

    Vector<Texture> textures;
    textures.push_back(texture);

    Vector<Texture> textures2;
    textures2.push_back(texture2);

    glm::vec4 lightColor(1.0, 1.0, 0.5, 1.0);
    glm::vec3 lightPos(0, 1000, 1000);

    Mesh mesh2(verts2, inds2, layout);
    mesh2.Draw(shader2, renderer2, lightPos);

    Mesh mesh(verts, inds, layout);
    mesh.Draw(shader2, renderer, lightPos);

    Timer timer;
    float time = timer.getTimeMs();

    //Shader
    shader.SetUniform1i("u_Texture", 0);
    shader.SetUniform1f("u_Time", time);
    shader2.SetUniform1i("u_Texture", 0);
    shader2.SetUniform1f("u_Time", time);


    float aspect = (float)Width / Height;
    shader.SetUniform1f("u_Aspect", aspect);
    shader2.SetUniform1f("u_Aspect", aspect);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(window, true);
    ImGui::StyleColorsDark();

    //MVP matrix 
    glm::mat4 projectionMatrix = glm::ortho(0.0f, (float)Width,
        0.0f, (float)Height,
        -1.0f, 1.0f);

    float field_of_view = 60.0f;
    float closestDistance = 0.1f;
    float farthestDistance = 500.0f;

    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    glm::mat4 modelMatrix2 = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    glm::mat4 viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

    // glm::vec3 translationModel(0, -118.857, -314.019); //Default values for optimal viewing
    // glm::vec3 translationView(-20, -100, 96.262);
    // float viewRotAngle = 43.088;

    glm::vec3 translationModel(0, 0, -406); //Default values for optimal viewing
    glm::vec3 translationModel2(0, 200, -406);
    glm::vec3 translationView(0, -100, 100);
    float viewRotAngle = 0;

    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.Clear();
        renderer2.Clear();

        modelMatrix = glm::translate(glm::mat4(1.0f), translationModel);
        modelMatrix2 = glm::translate(glm::mat4(1.0f), translationModel2);
        viewMatrix = glm::translate(glm::mat4(1.0f), translationView);

        float rotation = time / 100.0;
        //modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
        //modelMatrix2 = glm::rotate(modelMatrix2, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));

        viewMatrix = glm::rotate(viewMatrix, glm::radians(viewRotAngle), glm::vec3(1.0f, 0.0f, 0.0f));

        shader.Bind();
        shader.SetUniform4f("u_Color", 0.1, 0.3, 0.8, 1.0);
        shader2.SetUniform4f("u_Color", 0.1, 0.3, 0.8, 1.0);
        time = timer.getTimeMs();

        projectionMatrix = glm::perspective(glm::radians(field_of_view), aspect, closestDistance, farthestDistance);

        shader.SetUniform1f("u_Time", time);
        shader.SetUniformMat4f("u_Model", modelMatrix);
        shader.SetUniformMat4f("u_View", viewMatrix);
        shader.SetUniformMat4f("u_Proj", projectionMatrix);
        shader.SetUniform4f("lightColor", lightColor);
        shader.SetUniform3f("lightPos", lightPos);
        mesh.Draw(shader, renderer, lightPos);

        shader2.Bind();
        shader2.SetUniform1f("u_Time", time);
        shader2.SetUniformMat4f("u_Model", modelMatrix2);
        shader2.SetUniformMat4f("u_View", viewMatrix);
        shader2.SetUniformMat4f("u_Proj", projectionMatrix);
        shader2.SetUniform4f("lightColor", lightColor);
        shader2.SetUniform3f("lightPos", lightPos);
        mesh2.Draw(shader2, renderer, lightPos);
        

        // IMGUI
        ImGui_ImplGlfwGL3_NewFrame();

        ImGui::SliderFloat3("Translation Model", &translationModel.x, -960.0f, 960.0f);
        ImGui::SliderFloat3("Translation View", &translationView.x, -100.0f, 100.0f);
        ImGui::SliderFloat3("Light Position", &lightPos.x, -1000.0f, 1000.0f);
        ImGui::SliderFloat("Angle of Camera", &viewRotAngle, -90.0f, 90.0f);
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