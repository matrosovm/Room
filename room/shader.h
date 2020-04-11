#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>

using namespace std;

class Shader
{
public:
    GLuint  program;
    Shader(const GLchar* vertexFile, const GLchar* fragmentFile);

    void Use();
};

#endif //SHADER_H