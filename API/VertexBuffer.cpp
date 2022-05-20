#include "VertexBuffer.h"
#include "Renderer.h"


VertexBuffer::VertexBuffer(const void* vertices, GLsizeiptr size)
{
    Call(glGenBuffers(1, &renderer_id));
    Bind();
    Call(glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
    Call(glDeleteBuffers(1, &renderer_id));
}

void VertexBuffer::Bind() const
{
    Call(glBindBuffer(GL_ARRAY_BUFFER, renderer_id));
}
