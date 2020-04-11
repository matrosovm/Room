#include "movement.h"

bool firstMouse = false;

GLfloat deltaTime = 0.0f, lastFrame = 0.0f;
GLfloat yaw = -90.0f, pitch = 0.0f;
GLfloat lastX = 800, lastY = 600;
GLfloat cameraSpeed;

enum Mode
{
    FORWARD = 1,
    BACK = -1,
    LEFT = -1,
    RIGHT = 1,
};

void CheckMainCollision(Mode mode, glm::vec3& front, bool& key)
{
    if (cameraPos.z + static_cast<float>(mode) * cameraSpeed * front.z >= startCoord.z + cubeSize.z - 0.11f)
    {
        key = false;
        cameraPos.x += static_cast<float>(mode) * cameraSpeed * front.x;
        cameraPos.y += static_cast<float>(mode) * cameraSpeed * front.y;
        cameraPos.z = startCoord.z + cubeSize.z - 0.11f;
    }
    else if (cameraPos.z + static_cast<float>(mode) * cameraSpeed * front.z <= startCoord.z - cubeSize.z + 0.11f)
    {
        key = false;
        cameraPos.x += static_cast<float>(mode) * cameraSpeed * front.x;
        cameraPos.y += static_cast<float>(mode) * cameraSpeed * front.y;
        cameraPos.z = startCoord.z - cubeSize.z + 0.11f;
    }
    if (cameraPos.y + static_cast<float>(mode) * cameraSpeed * front.y >= startCoord.y + cubeSize.y - 0.11f)
    {
        key = false;
        cameraPos.x += static_cast<float>(mode) * cameraSpeed * front.x;
        cameraPos.y = startCoord.y + cubeSize.y - 0.11f;
        cameraPos.z += static_cast<float>(mode) * cameraSpeed * front.z;
    }
    else if (cameraPos.y + static_cast<float>(mode) * cameraSpeed * front.y <= startCoord.y - cubeSize.y + 0.11f)
    {
        key = false;
        cameraPos.x += static_cast<float>(mode) * cameraSpeed * front.x;
        cameraPos.y = startCoord.y - cubeSize.y + 0.11f;
        cameraPos.z += static_cast<float>(mode) * cameraSpeed * front.z;
    }
    if (cameraPos.x + static_cast<float>(mode) * cameraSpeed * front.x >= startCoord.x + cubeSize.x - 0.11f)
    {
        key = false;
        cameraPos.x = startCoord.x + cubeSize.x - 0.11f;
        cameraPos.y += static_cast<float>(mode) * cameraSpeed * front.y;
        cameraPos.z += static_cast<float>(mode) * cameraSpeed * front.z;
    }
    else if (cameraPos.x + static_cast<float>(mode) * cameraSpeed * front.x <= startCoord.x - cubeSize.x + 0.11f)
    {
        key = false;
        cameraPos.x = startCoord.x - cubeSize.x + 0.11f;
        cameraPos.y += static_cast<float>(mode) * cameraSpeed * front.y;
        cameraPos.z += static_cast<float>(mode) * cameraSpeed * front.z;
    }

}

void CheckCollision(Cube& cube, const GLfloat& cameraSpeed, glm::vec3& front, Mode mode, bool& key)
{
    if (cameraPos.z + static_cast<float>(mode) * cameraSpeed * front.z > cube.GetPositionZ() - cube.GetLength() - 0.11f &&
        cameraPos.z + static_cast<float>(mode) * cameraSpeed * front.z < cube.GetPositionZ() + cube.GetLength() &&
        cameraPos.x + static_cast<float>(mode) * cameraSpeed * front.x <= cube.GetPositionX() + cube.GetWidth() &&
        cameraPos.x + static_cast<float>(mode) * cameraSpeed * front.x >= cube.GetPositionX() - cube.GetWidth() &&
        cameraPos.y + static_cast<float>(mode) * cameraSpeed * front.y <= cube.GetPositionY() + cube.GetHeight() &&
        cameraPos.y + static_cast<float>(mode) * cameraSpeed * front.y >= cube.GetPositionY() - cube.GetHeight())
    {
        key = false;
        cameraPos.x += mode * cameraSpeed * front.x;
        cameraPos.y += mode * cameraSpeed * front.y;
        cameraPos.z = cube.GetPositionZ() - cube.GetLength() - 0.11;

    }
    else if (cameraPos.z + static_cast<float>(mode) * cameraSpeed * front.z < cube.GetPositionZ() + cube.GetLength() + 0.11f &&
             cameraPos.z + static_cast<float>(mode) * cameraSpeed * front.z > cube.GetPositionZ() - cube.GetLength() &&
             cameraPos.x + static_cast<float>(mode) * cameraSpeed * front.x <= cube.GetPositionX() + cube.GetWidth() &&
             cameraPos.x + static_cast<float>(mode) * cameraSpeed * front.x >= cube.GetPositionX() - cube.GetWidth() &&
             cameraPos.y + static_cast<float>(mode) * cameraSpeed * front.y <= cube.GetPositionY() + cube.GetHeight() &&
             cameraPos.y + static_cast<float>(mode) * cameraSpeed * front.y >= cube.GetPositionY() - cube.GetHeight())
    {
        key = false;
        cameraPos.x += mode * cameraSpeed * front.x;
        cameraPos.y += mode * cameraSpeed * front.y;
        cameraPos.z = cube.GetPositionZ() + cube.GetLength() + 0.11;

    }
    if (cameraPos.y + static_cast<float>(mode) * cameraSpeed * front.y < cube.GetPositionY() + cube.GetHeight() + 0.11f &&
        cameraPos.y + static_cast<float>(mode) * cameraSpeed * front.y > cube.GetPositionY() - cube.GetHeight() &&
        cameraPos.x + static_cast<float>(mode) * cameraSpeed * front.x <= cube.GetPositionX() + cube.GetWidth() &&
        cameraPos.x + static_cast<float>(mode) * cameraSpeed * front.x >= cube.GetPositionX() - cube.GetWidth() &&
        cameraPos.z + static_cast<float>(mode) * cameraSpeed * front.z <= cube.GetPositionZ() + cube.GetLength() &&
        cameraPos.z + static_cast<float>(mode) * cameraSpeed * front.z >= cube.GetPositionZ() - cube.GetLength())
    {
        key = false;
        cameraPos.x += cameraSpeed * front.x;
        cameraPos.y = cube.GetPositionY() + cube.GetHeight() + 0.11;
        cameraPos.z += cameraSpeed * front.z;
    }
    else if (cameraPos.y + static_cast<float>(mode) * cameraSpeed * front.y > cube.GetPositionY() - cube.GetHeight() - 0.11f &&
             cameraPos.y + static_cast<float>(mode) * cameraSpeed * front.y < cube.GetPositionY() + cube.GetHeight() &&
             cameraPos.x + static_cast<float>(mode) * cameraSpeed * front.x <= cube.GetPositionX() + cube.GetWidth() &&
             cameraPos.x + static_cast<float>(mode) * cameraSpeed * front.x >= cube.GetPositionX() - cube.GetWidth() &&
             cameraPos.z + static_cast<float>(mode) * cameraSpeed * front.z <= cube.GetPositionZ() + cube.GetLength() &&
             cameraPos.z + static_cast<float>(mode) * cameraSpeed * front.z >= cube.GetPositionZ() - cube.GetLength())
    {
        key = false;
        cameraPos.x += cameraSpeed * front.x;
        cameraPos.y = cube.GetPositionY() - cube.GetHeight() - 0.11;
        cameraPos.z += cameraSpeed * front.z;
    }
    if (cameraPos.x + static_cast<float>(mode) * cameraSpeed * front.x > cube.GetPositionX() - cube.GetWidth() - 0.11f &&
        cameraPos.x + static_cast<float>(mode) * cameraSpeed * front.x < cube.GetPositionX() + cube.GetWidth() &&
        cameraPos.y + static_cast<float>(mode) * cameraSpeed * front.y <= cube.GetPositionY() + cube.GetHeight() &&
        cameraPos.y + static_cast<float>(mode) * cameraSpeed * front.y >= cube.GetPositionY() - cube.GetHeight() &&
        cameraPos.z + static_cast<float>(mode) * cameraSpeed * front.z <= cube.GetPositionZ() + cube.GetLength() &&
        cameraPos.z + static_cast<float>(mode) * cameraSpeed * front.z >= cube.GetPositionZ() - cube.GetLength())
    {
        key = false;
        cameraPos.x = cube.GetPositionX() - cube.GetWidth() - 0.11;
        cameraPos.y += mode * cameraSpeed * front.y;
        cameraPos.z += mode * cameraSpeed * front.z;

    }
    else if (cameraPos.x + static_cast<float>(mode) * cameraSpeed * front.x < cube.GetPositionX() + cube.GetWidth() + 0.11f &&
             cameraPos.x + static_cast<float>(mode) * cameraSpeed * front.x > cube.GetPositionX() - cube.GetWidth() &&
             cameraPos.y + static_cast<float>(mode) * cameraSpeed * front.y <= cube.GetPositionY() + cube.GetHeight()   &&
             cameraPos.y + static_cast<float>(mode) * cameraSpeed * front.y >= cube.GetPositionY() - cube.GetHeight()   &&
             cameraPos.z + static_cast<float>(mode) * cameraSpeed * front.z <= cube.GetPositionZ() + cube.GetLength()   &&
             cameraPos.z + static_cast<float>(mode) * cameraSpeed * front.z >= cube.GetPositionZ() - cube.GetLength()  )
    {
        key = false;
        cameraPos.x = cube.GetPositionX() + cube.GetWidth() + 0.11;
        cameraPos.y += mode * cameraSpeed * front.y;
        cameraPos.z += mode * cameraSpeed * front.z;
    }
}

void Movement(Cube& room, std::list<Cube>& cubes, const bool* keys)
{
    GLfloat currentFrame = glfwGetTime();

    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    cameraSpeed = 4.0f * deltaTime;

    if (keys[GLFW_KEY_W])
    {
        bool key = true;

        CheckMainCollision(FORWARD, cameraFront, key);

        for (auto& cube : cubes)
        {
            CheckCollision(cube, cameraSpeed, cameraFront, FORWARD, key);
        }

        if (key)
            cameraPos += cameraSpeed * cameraFront;
    }
    if (keys[GLFW_KEY_S])
    {
        bool key = true;

        CheckMainCollision(BACK, cameraFront, key);

        for (auto& cube : cubes)
        {
            CheckCollision(cube, cameraSpeed, cameraFront, BACK, key);
        }

        if (key)
            cameraPos -= cameraSpeed * cameraFront;
    }
    if (keys[GLFW_KEY_A])
    {
        bool key = true;

        glm::vec3 front = glm::normalize(glm::cross(cameraFront, cameraUp));

        CheckMainCollision(LEFT, front, key);

        for (auto& cube : cubes)
        {
            CheckCollision(cube, cameraSpeed, front, LEFT, key);
        }
        if (key)
            cameraPos -= cameraSpeed * front;
    }
    if (keys[GLFW_KEY_D])
    {
        bool key = true;

        glm::vec3 front = glm::normalize(glm::cross(cameraFront, cameraUp));

        CheckMainCollision(RIGHT, front, key);

        for (auto& cube : cubes)
        {
            CheckCollision(cube, cameraSpeed, front, RIGHT, key);
        }
        if (key)
            cameraPos += cameraSpeed * front;
    }
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key == GLFW_KEY_K && action == GLFW_PRESS)
        cubeSize = glm::vec3(100.0f, 100.0f, 100.0f);
    if (action == GLFW_PRESS)
        keys[key] = true;
    else if (action == GLFW_RELEASE)
        keys[key] = false;
}

void MouseCallback(GLFWwindow* window, double xPosition, double yPosition)
{
    if (firstMouse)
    {
        lastX = xPosition;
        lastY = yPosition;
        firstMouse = false;
    }

    GLfloat xOffset = xPosition - lastX;
    GLfloat yOffset = lastY - yPosition;
    lastX = xPosition;
    lastY = yPosition;

    GLfloat sensitivity = 0.1;
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    yaw += xOffset;
    pitch += yOffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    else if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;

    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    cameraFront = glm::normalize(front);
}
