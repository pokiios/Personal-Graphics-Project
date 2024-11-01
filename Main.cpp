#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor; \n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

int main()
{
    // Initalise GLFW
    glfwInit();

    // OpenGL 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // GLFW should know it's using core profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Creating an array of vertex points to create triangle
    GLfloat vertices[] =
    {
        // First vertex
        -0.5, -0.5 * float(sqrt(3)) / 3, 0.f,
        // Second Vertex
        0.5f, -0.5 * float(sqrt(3)) / 3, 0.f,
        // Third Vertex
        0.0, 0.5 * float(sqrt(3)) / 3, 0.f
    };

    // Reference Window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Personal Project", NULL, NULL);

    // failsafe
    if (window == NULL)
    {
        std::cout << "failed to create window" << std::endl;
        return -1;
    }

    glfwMakeContextCurrent(window);

    gladLoadGL();

    // Get viewport of screen
    glViewport(0, 0, 800, 600);

    // Create reference to vertex shader so that compiler can read the source code
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Create reference to fragment shader so that compiler can read the source code
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Create shader program
    GLuint shaderProgram = glCreateProgram();

    // Attach vertex and fragment shaders to shader program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Delete shaders as they're now in the shader program
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Vertex Array Object, Vertex Buffer Object
    GLuint vao, vbo;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    // Bind vao and vbo to respective array and buffer
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Rendering Process here
    // Set colour buffer to navy blue
    glClearColor(0.07, 0.13, 0.17, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    // Send buffer to front
    glfwSwapBuffers(window);

    // Keep window open until forced to close
    while (!glfwWindowShouldClose(window))
    {
        // Check Input
        processInput(window);

        // Rendering Process here
        // Set colour buffer to navy blue
        glClearColor(0.07, 0.13, 0.17, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(vao);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Send buffer to front
        glfwSwapBuffers(window);

        // Take care of all GLFW events
        glfwPollEvents();
    }

    // Clean up
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(shaderProgram);


    //Destroy window if While loop ends
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}
