#ifndef OPENGL_MOVEMENT_H
#define OPENGL_MOVEMENT_H

#include "window.h"
#include "cube.h"

inline glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  -3.0f);
inline glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
inline glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
inline glm::vec3 cubeSize    = glm::vec3(3.0f, 3.0f,  3.0f);
inline glm::vec3 startCoord  = glm::vec3(0.0f, 0.0f,  0.0f);

inline bool keys[1024];

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPosition, double yPosition);
void Movement(Cube& room, std::list<Cube>& cubes, const bool* keys);

#endif //OPENGL_MOVEMENT_H
