#include "Shader.h"


struct Shader::ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

Shader::ShaderProgramSource Shader::ParsShader(const std::string filepath)
{
    std::ifstream stream(filepath);

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    }

    return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

Shader::Shader(const std::string filepath)
    : m_RendererID(0)
{
    m_RendererID = glCreateProgram();
    ShaderProgramSource source = ParsShader(filepath);
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, source.VertexSource);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, source.FragmentSource);
    glAttachShader(m_RendererID, vs);
    glAttachShader(m_RendererID, fs);
    glLinkProgram(m_RendererID);
    glValidateProgram(m_RendererID);

    glDeleteShader(vs);
    glDeleteShader(fs);
}

Shader::~Shader()
{
    glDeleteProgram(m_RendererID);
}

void Shader::bind() const
{
    glUseProgram(m_RendererID);
}

void Shader::unbind() const
{
    glUseProgram(0);
}

void Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    int uniformLok = glGetUniformLocation(m_RendererID, name.c_str());
    glUniform4f(uniformLok, v0, v1, v2, v3);
}

void Shader::setUniform3f(const std::string& name, float v0, float v1, float v2)
{
    int uniformLok = glGetUniformLocation(m_RendererID, name.c_str());
    glUniform3f(uniformLok, v0, v1, v2);
}

void Shader::setUniform2f(const std::string& name, float v0, float v1)
{
    int uniformLok = glGetUniformLocation(m_RendererID, name.c_str());
    glUniform2f(uniformLok, v0, v1);
}

void Shader::setUniform1i(const std::string& name, int value)
{
    int uniformLok = glGetUniformLocation(m_RendererID, name.c_str());
    glUniform1i(uniformLok, value);
}

void Shader::setUniformMat4f(const std::string& name, glm::mat4& matrix)
{
    glUseProgram(m_RendererID);
    int uniformLok = glGetUniformLocation(m_RendererID, name.c_str());
    glUniformMatrix4fv(uniformLok, 1, GL_FALSE, glm::value_ptr(matrix));
}