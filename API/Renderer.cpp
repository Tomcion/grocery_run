#include "Renderer.h"
#include <iostream>

void ClearErrors()
{
//    while(glGetError() != GL_NO_ERROR);
}

bool LogError(const char* file, int line)
{
    while(GLenum error = glGetError())
    {
        std::cout << "[Error]: in " << file
        << " on line " << line << std::endl;
        std::cout << error << std::endl;
        return false;
    }
    return true;
}

void Renderer::Draw(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shader)
{
    shader.Bind();
    vao.Bind();
    ibo.Bind();
    Call(glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear()
{
    Call(glClear(GL_COLOR_BUFFER_BIT));
}
