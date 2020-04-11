#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "cube.h"

class Window
{
public:
    GLFWwindow* windowMain;

    Window (int windowWidth, int windowHeight);
};

#endif //WINDOW_H