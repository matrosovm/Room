#include "window.h"
#include "movement.h"

Window::Window(int windowWidth, int windowHeight)
{
    int width;
    int height;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    this->windowMain = glfwCreateWindow(windowWidth, windowHeight, "OpenGL", nullptr, nullptr);

    if (windowMain == nullptr)
    {
        std::cerr << "failed to create a window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(windowMain);
    glfwSetInputMode(windowMain, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetKeyCallback(windowMain, KeyCallback);
    glfwSetCursorPosCallback(windowMain, MouseCallback);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "failed to initialized GLEW" << std::endl;
    }

    glfwGetFramebufferSize(windowMain, &width, &height);
    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);
}

