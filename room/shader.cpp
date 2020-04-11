#include "shader.h"

Shader::Shader(const GLchar* vertexFile, const GLchar* fragmentFile)
{
    string vertexCode;
    string fragmentCode;

    ifstream vertexShaderFile;
    ifstream fragmentShaderFile;

    vertexShaderFile.exceptions(ifstream::failbit);
    fragmentShaderFile.exceptions(ifstream::failbit);
    try
    {
        vertexShaderFile.open(vertexFile);
        fragmentShaderFile.open(fragmentFile);

        stringstream streamV, streamF;
        streamV << vertexShaderFile.rdbuf();
        streamF << fragmentShaderFile.rdbuf();

        vertexShaderFile.close();
        fragmentShaderFile.close();

        vertexCode = streamV.str();
        fragmentCode = streamF.str();
    }
    catch(ifstream::failure& e)
    {
        cerr << "сan't read shader file" << endl;
    }

    const GLchar* vertexCodeC   = vertexCode.c_str();
    const GLchar* fragmentCodeC = fragmentCode.c_str();

    GLuint vertexShader;
    GLuint fragmentShader;
    GLint  success;
    GLchar infoLog[512];

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertexShader, 1, &vertexCodeC, nullptr);
    glShaderSource(fragmentShader, 1, &fragmentCodeC, nullptr);

    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        cerr << "can't compile vertex shader\n" << infoLog << endl;
    }

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        cerr << "cant't compile fragment shader\n" << infoLog << endl;
    }

    this->program = glCreateProgram();
    glAttachShader(this->program, vertexShader);
    glAttachShader(this->program, fragmentShader);
    glLinkProgram(this->program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glGetProgramiv(this->program, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(this->program, 512, nullptr, infoLog);
        cerr << "can't link program\n" << infoLog << endl;
    }
}

void Shader::Use()
{
    glUseProgram(this->program);
}