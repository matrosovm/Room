#define GLEW_STATIC

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "window.h"
#include "cube.h"
#include "parser.h"
#include "movement.h"

void SetBuffers(const Cube& cb, GLuint* vbo, GLuint* vao, GLuint* textureContainer, size_t offset)
{
    for (size_t i = 0; i < 6; ++i)
    {
        glBindVertexArray(vao[i + offset]);
        {
            glBindBuffer(GL_ARRAY_BUFFER, vbo[i + offset]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(cb.GetVertices(i)), cb.GetVertices(i).data(), GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *) 0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *) (3 * sizeof(GLfloat)));
            glEnableVertexAttribArray(1);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
        glBindVertexArray(0);

        glBindTexture(GL_TEXTURE_2D, textureContainer[i + offset]);
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, cb.GetTextureWidth(i),
                         cb.GetTextureHeight(i), 0, GL_RGB, GL_UNSIGNED_BYTE, cb.GetTexture(i));
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        glBindTexture(GL_TEXTURE_2D, 0);

    }
}

void DrawConfigurationCube(GLuint* vao, GLuint* textureContainer, size_t offset)
{
    for (size_t i = 0; i < 6; ++i)
    {
        glBindTexture(GL_TEXTURE_2D, textureContainer[i + offset]);
        glBindVertexArray(vao[i + offset]);
            glDrawArrays(GL_TRIANGLES, 0, 18);
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

int main()
{
    Cube            room;
    std::list<Cube> cubes;

    ConfigParser(room, cubes, "config.txt");

    cubeSize   = glm::vec3(room.GetWidth(), room.GetHeight(), room.GetLength());
    cameraPos  = glm::vec3(room.GetPositionX(), room.GetPositionY(), room.GetPositionZ());
    startCoord = cameraPos;

    int countContainer = 6 * (cubes.size() + 1);

    GLuint vbo[countContainer];
    GLuint vao[countContainer];
    GLuint textureContainer[countContainer];

    Window window(1600, 1200);
    Shader shaderCube("vertex.shader.glsl",
                    "fragment.shader.glsl");

    glGenTextures(countContainer, textureContainer);
    glGenVertexArrays(countContainer, vao);
    glGenBuffers(countContainer, vbo);

    SetBuffers(room, vbo, vao, textureContainer, 0);

    size_t offset = 6;
    for (const auto& cube : cubes)
    {
        SetBuffers(cube, vbo, vao, textureContainer, offset);
        offset += 6;
    }

    while (!glfwWindowShouldClose(window.windowMain))
    {
        const bool* keysPointer = keys;
        Movement(room, cubes, keysPointer);

        glfwPollEvents();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderCube.Use();

        glm::mat4 model(1.0f);
        glm::mat4 view(1.0f);
        glm::mat4 projection(1.0f);

        view       = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        model      = glm::translate(model, {room.GetPositionX(), room.GetPositionY(), room.GetPositionZ()});
        projection = glm::perspective(glm::radians(45.0f), static_cast<float>(1600 / 1200),
                                     0.05f, 100.0f);

        GLint loc = glGetUniformLocation(shaderCube.program, "model");
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(model));

        loc = glGetUniformLocation(shaderCube.program, "view");
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(view));

        loc = glGetUniformLocation(shaderCube.program, "projection");
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(projection));

        DrawConfigurationCube(vao, textureContainer, 0);

        offset = 6;
        for (const auto& cube : cubes)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, {cube.GetPositionX(),
                               cube.GetPositionY(), cube.GetPositionZ()});

            loc = glGetUniformLocation(shaderCube.program, "model");
            glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(model));

            DrawConfigurationCube(vao, textureContainer, offset);
            offset += 6;
        }
        glfwSwapBuffers(window.windowMain);
    }

    glDeleteTextures(countContainer, textureContainer);
    glDeleteVertexArrays(countContainer, vao);
    glDeleteBuffers(countContainer, vbo);

    glfwTerminate();
}