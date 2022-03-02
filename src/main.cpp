#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

struct ShaderSource
{
    std::string VertexSource;
    std::string PixelSource;
};

static ShaderSource ParseShader(const std::string& filePath)
{
    std::ifstream stream(filePath);

    std::string line;
    std::stringstream ss[2];

    enum class ShaderType{
        NONE = -1,
        VERTEX = 0,
        PIXEL = 1
    };
    ShaderType type = ShaderType::NONE;
    while(getline(stream, line))
    {
        if(line.find("#shader") != std::string::npos)
        {
            if(line.find("vertex") != std::string::npos)
            {
                type = ShaderType::VERTEX;
            }
            else if(line.find("pixel") != std::string::npos){
                type = ShaderType::PIXEL;
            }
        }
        else{
            ss[(int)type] << line << "\n";
        }
    }

    return { ss[0].str(), ss[1].str() };
}
static unsigned int CompileShader(unsigned int type, const std::string &source)
{
    unsigned int id = glCreateShader(type);
    const char *src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char *message = (char *)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);

        std::cout << "Failed to compile the shader" << std::endl;
        std::cout << message << std::endl;
    }

    return id;
}

static unsigned int CreateShader(const std::string &vertexShader, const std::string &pixelShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vertexS = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int pixelS = CompileShader(GL_FRAGMENT_SHADER, pixelShader);

    glAttachShader(program, vertexS);
    glAttachShader(program, pixelS);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vertexS);
    glDeleteShader(pixelS);

    return program;
}

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
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Newton", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "F";
    }

    // Postions of the vertex
    float positions[] = {
        -0.5f, -0.5f,
        0.5f, -0.5f,
        0.5f, 0.5f,
        -0.5f, 0.75f,
        };
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };


    unsigned int buffer;
    glGenBuffers(1, &buffer);              // creating a buffer
    glBindBuffer(GL_ARRAY_BUFFER, buffer); // binding the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    //IMPORTANT FOR MACOS
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(positions[0]) * 2, (const void *)0); // Explaing the bufer data
    glEnableVertexAttribArray(0);

    unsigned int ibo;
    glGenBuffers(1, &ibo);              // creating a buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo); // binding the buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    ShaderSource source = ParseShader("assets/shaders/basic.shader");

    unsigned int shader = CreateShader(source.VertexSource, source.PixelSource);
    glUseProgram(shader);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}