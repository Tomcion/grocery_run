#include "Renderer.h"

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
