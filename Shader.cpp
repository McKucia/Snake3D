#include "Shader.hpp"
#include <sstream>
#include <fstream>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
    std::ifstream vertexFile;
    std::ifstream fragmentFile;

    std::stringstream vertexStream;
    std::stringstream fragmentStream;

    std::string vertexCode;
    std::string fragmentCode;

    vertexFile.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
    fragmentFile.exceptions ( std::ifstream::failbit | std::ifstream::badbit );

    try{
        vertexFile.open(vertexPath, std::ios::in);
        fragmentFile.open(fragmentPath, std::ios::in);

        vertexStream << vertexFile.rdbuf();
        fragmentStream << fragmentFile.rdbuf();

        vertexCode = vertexStream.str();
        fragmentCode = fragmentStream.str();

        vertexFile.close();
        fragmentFile.close();
    }
    catch (std::ifstream::failure e){
        std::cerr << e.what() << " - cannot open shader file.\n";
    }

    CreateAndCompileShader(vertexCode, fragmentCode);
}

void Shader::Use() {
    glUseProgram(programID_);
}

void Shader::CreateAndCompileShader(const std::string& vertexCodeString, const std::string& fragmentCodeString) {
    unsigned int vertexShader;
    unsigned int fragmentShader;
    int success;
    char infoLog[512];

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    const char* vertexCode = vertexCodeString.c_str();
    const char* fragmentCode = fragmentCodeString.c_str();

    glShaderSource(vertexShader, 1, &vertexCode, nullptr);
    glShaderSource(fragmentShader, 1, &fragmentCode, nullptr);

    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << "Failed to compile vertex shader " << infoLog << "\n";
    }

    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cerr << "Failed to compile fragment shader: " << infoLog << "\n";
    }

    programID_ = glCreateProgram();
    glAttachShader(programID_, vertexShader);
    glAttachShader(programID_, fragmentShader);

    glLinkProgram(programID_);
    glGetProgramiv(programID_, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(programID_, 512, nullptr, infoLog);
        std::cerr << "Failed to link program: " << infoLog << "\n";
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader() {
    glDeleteProgram(programID_);
}

void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(programID_, name.c_str()), value);
}

void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(programID_, name.c_str()), value);
}

void Shader::setMat4f(const std::string &name, const glm::mat4& matrix) {
    glUniformMatrix4fv(glGetUniformLocation(programID_, name.c_str()), 1, GL_FALSE, &matrix[0][0]);
}

void Shader::setVec3f(const std::string &name, float v1, float v2, float v3) {
    glUniform3f(glGetUniformLocation(programID_, name.c_str()), v1, v2, v3);
}

void Shader::setVec3f(const std::string& name, const glm::vec3& value) {
    glUniform3fv((glGetUniformLocation(programID_, name.c_str())), 1, &value[0]);
}
