#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

int main()
{

    // Initalise GLFW
    glfwInit();

    // OpenGL 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // GLFW should know it's using core profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

    // Set colour buffer to navy blue
    glClearColor(0.07, 0.13, 0.17, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Send buffer to front
    glfwSwapBuffers(window);

    // Keep window open until forced to close
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
    }

    //Destroy window if While loop ends
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
