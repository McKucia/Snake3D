#pragma once
#include <string>
#include "glm/glm/glm.hpp"

class Shader{
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();
    void Use();
    unsigned int getProgram() const { return programID_; }
    void setFloat(const std::string& name, float value) const;
    void setInt(const std::string& name, int value) const;
    void setMat4f(const std::string& name, const glm::mat4& matrix);
    void setVec3f(const std::string& name, float v1, float v2, float v3);

    void setVec3f(const std::string& name, const glm::vec3& value);

private:
    unsigned int programID_;
    void CreateAndCompileShader(const std::string& vertexCode, const std::string& fragmentCode);
};