#ifndef SHADER_H
#define SHADER_H

#include <tuple>
#include <string>

#include <glm/glm.hpp>

#include <GL/glew.h>

class Shader
{
private:
    GLuint renderer_id;
    std::tuple<std::string, std::string> ParseShader(const char* path);
    GLuint CompileShader(GLenum type, const std::string& source);
public:
    Shader(const char* path);
    ~Shader();

    void setUniform4f(const char* uniform_name, float r, float g, float b, float a);
    void setUniform1i(const char* uniform_name, int value);
    void setUniformMat4f(const char* uniform_name, const glm::mat4& matrix);
    int getUniformLocation(const char* uniform_name);
    void Bind() const;
};

#endif /* SHADER_H */
