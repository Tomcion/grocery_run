#include "VertexArray.h"

VertexArray::VertexArray()
{
    Call(glGenVertexArrays(1, &renderer_id));
    Bind();
}

VertexArray::~VertexArray()
{
    Call(glDeleteVertexArrays(1, &renderer_id));
}

void VertexArray::AddAttr(int count)
{
    attributeLenghts.push_back(count);
}

void VertexArray::Buffer(const VertexBuffer& vbo)
{
    vbo.Bind();
    long offset = 0;
    
    int stride = 0;
    for (int i = 0; i < attributeLenghts.size(); i++)
        stride += attributeLenghts[i] * sizeof(float);
    
    for (int i = 0; i < attributeLenghts.size(); i++)
    {
        Call(glEnableVertexAttribArray(i));
        Call(glVertexAttribPointer(i, attributeLenghts[i], GL_FLOAT, GL_FALSE, stride, (const void*)offset));
        offset += attributeLenghts[i] * sizeof(float);
    }
}


void VertexArray::Bind() const
{
    Call(glBindVertexArray(renderer_id));
}
