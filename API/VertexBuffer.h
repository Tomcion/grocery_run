#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <GL/glew.h>
#include "Call.h"


class VertexBuffer
{
private:
    GLuint renderer_id;
public:
    VertexBuffer(const void* vertices, GLsizeiptr size);
    ~VertexBuffer();
    void Bind() const;
};

#endif /* VERTEX_BUFFER_H */
