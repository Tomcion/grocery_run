#include "Shader.h"

Shader::Shader(const char* path)
{
    Call(GLuint program = glCreateProgram());

    std::tuple<std::string, std::string> source = ParseShader(path);
    GLuint vs = CompileShader(GL_VERTEX_SHADER, std::get<0>(source));
    GLuint fs = CompileShader(GL_FRAGMENT_SHADER, std::get<1>(source));

    Call(glAttachShader(program, vs));
    Call(glAttachShader(program, fs));
    Call(glLinkProgram(program));
    Call(glValidateProgram(program));
    Call(glDeleteShader(vs));
    Call(glDeleteShader(fs));

    renderer_id = program;
}

Shader::~Shader()
{
    Call(glDeleteProgram(renderer_id));
}

std::tuple<std::string, std::string> Shader::ParseShader(const char* path)
{
    std::stringstream shaders[2];
    std::ifstream file(path);
    std::string line;

    enum ShaderType : char
    {
        NONE = -1, VERTEX, FRAGMENT
    };

    ShaderType currentShader = NONE;

    if (!file.good()) std::cout << "Failed to load the shaders file \n";

    while(getline(file, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                currentShader = VERTEX;
            } else if (line.find("fragment") != std::string::npos)
            {
                currentShader = FRAGMENT;
            }
        } else {
            shaders[(int)currentShader] << line << std::endl;
        }
    }

    return std::make_tuple(shaders[0].str(), shaders[1].str());
}

GLuint Shader::CompileShader(GLenum type, const std::string& source)
{
    Call(GLuint shader = glCreateShader(type));
    const char* src = source.c_str();
    Call(glShaderSource(shader, 1, &src, nullptr));
    Call(glCompileShader(shader));

    GLint isCompiled = 0;
    Call(glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled));
    if (isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        Call(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength));

        char* errorLog = new char[maxLength];
        Call(glGetShaderInfoLog(shader, maxLength, &maxLength, errorLog));

        std::cout << "Failed to compile the " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader \n";

        delete[] errorLog;
        Call(glDeleteShader(shader));
        return 0;
    }

    return shader;
}

void Shader::Bind() const
{
    Call(glUseProgram(renderer_id));
}

void Shader::setUniform4f(const char* uniform_name, float r, float g, float b, float a)
{
    Call(glUniform4f(getUniformLocation(uniform_name), r, g, b, a));
}

void Shader::setUniform1i(const char* uniform_name, int value)
{
    Call(glUniform1i(getUniformLocation(uniform_name), value));
}

void Shader::setUniformMat4f(const char* uniform_name, const glm::mat4& matrix)
{
    Call(glUniformMatrix4fv(getUniformLocation(uniform_name), 1, GL_FALSE, &matrix[0][0]));
}

int Shader::getUniformLocation(const char* uniform_name)
{
    int location = glGetUniformLocation(renderer_id, uniform_name);

    if (location == -1) std::cout << "[Warning]: Uniform '" << uniform_name << "' not found!\n";

    return location;
}
