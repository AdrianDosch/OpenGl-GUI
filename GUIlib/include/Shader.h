
#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <GL/glew.h>
#include <glm.hpp>
#include <gtc\type_ptr.hpp>

namespace GUI
{

struct Shader
{
 private:
    unsigned int m_RendererID;
    
    struct ShaderProgramSource;

    static ShaderProgramSource ParsShader(const std::string filepath);
    
    static unsigned int CompileShader(unsigned int type, const std::string& source);

public:
    Shader(const std::string filepath);
    Shader(){}
    ~Shader();

    void bind() const;
    void unbind() const;

    void setUniform1i(const std::string& name, int value);
    void setUniform2f(const std::string& name, float v0, float v1);
    void setUniform3f(const std::string& name, float v0, float v1, float v2);
    void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
    void setUniformMat4f(const std::string& name, glm::mat4& matrix);
};
}//end namespace
#endif 
