#include "Buffer/VertexBuffer.hpp"
#include "VertexArray/VertexArray.hpp"
#include <iostream>

#define GLEW_STATIC

#include "GLEW/glew.h"
#include "GLFW/glfw3.h"

#include "GPUProgram/GPUProgram.hpp"
#include "Shaders/Shader.hpp"

std::int32_t main()
{
    if (!glfwInit())
    {
        std::cerr << "Can't initialize GLFW" << std::endl;

        return EXIT_FAILURE;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1000, 600, "CloseGH",
        nullptr, nullptr);

    glfwMakeContextCurrent(window);
    
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;

        return EXIT_FAILURE;
    }

    // Generate vertex array object
    // Generate some buffer 
    // Bind it to GL_ARRAY_BUFFER
    // Fill GL_ARRAY_BUFFER with data
    // Specify the attribute 
    // Enable the attribute
    // Unbind the buffer 

    std::cout << "Hello, CloseGH again" << std::endl;

    VertexArray firstTriangle{};
    firstTriangle.Bind();
    
    VertexBuffer firstVertecies 
    { 
        {
            0.5f,  0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f
        }
    };
    firstVertecies.Bind();
    firstVertecies.FillData();

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
        3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    VertexArray secondTriangle{};
    secondTriangle.Bind();

    VertexBuffer secondVertecies
    {
        {
            -0.5f, 0.6f, 0.0f,
            -0.5f, -0.4f, 0.0f,
            0.5f, 0.6f, 0.0f
        }
    };
    secondVertecies.Bind();
    secondVertecies.FillData();

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
        3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    Shader firstVertexShader
    {
        GL_VERTEX_SHADER,
        {
            "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "}\0"
        }
    };
    Shader firstFragmenShader 
    {
        GL_FRAGMENT_SHADER,
        {
            "#version 330 core\n"
            "out vec4 color;\n"
            "void main()\n"
            "{\n"
            "   color = vec4(1.0f, 0.2f, 0.3f, 1.0f);\n"
            "}\0"
        }
    };

    Shader secondVertexShader{ firstVertexShader };
    Shader secondFragmenShader
    {
        GL_FRAGMENT_SHADER,
        {
            "#version 330 core\n"
            "out vec4 color;\n"
            "void main()\n"
            "{\n"
            "   color = vec4(1.0f, 0.9f, 0.0f, 1.0f);\n"
            "}\0"
        }
    };

    firstVertexShader.Compile();
    firstFragmenShader.Compile();

    GPUProgram firstProgram 
    { 
        std::move(firstVertexShader),
        std::move(firstFragmenShader)
    };
    firstProgram.Link();

    secondVertexShader.Compile();
    secondFragmenShader.Compile();

    GPUProgram secondProgram
    {
        std::move(secondVertexShader),
        std::move(secondFragmenShader)
    };
    secondProgram.Link();

    while (!glfwWindowShouldClose(window))
    {
        // glClearColor(1.0f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        firstProgram.Bind();

        firstTriangle.Bind();
        glDrawArrays(GL_TRIANGLES, 0, firstVertecies.GetCount());

        secondProgram.Bind();

        secondTriangle.Bind();
        glDrawArrays(GL_TRIANGLES, 0, secondVertecies.GetCount());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    
    return EXIT_SUCCESS;
}
