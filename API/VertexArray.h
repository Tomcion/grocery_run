#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include <GL/glew.h>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Call.h"

#include <vector>


class VertexArray
{
private:
    GLuint renderer_id;
    std::vector<int> attributeLenghts;
public:
    VertexArray();
    ~VertexArray();
    void AddAttr(int count);
    void Buffer(const VertexBuffer& vbo);
    void Bind() const;
};

#endif /* VERTEX_ARRAY_H */
