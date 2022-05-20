#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(unsigned int* indices, int count)
    : count(count)
{
    Call(glGenBuffers(1, &renderer_id));
    Bind();
    Call(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
    Call(glDeleteBuffers(1, &renderer_id));
}

void IndexBuffer::Bind() const
{
    Call(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_id));
}
