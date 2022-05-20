#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Call.h"

class Renderer
{
public:
    static void Draw(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shader);
    static void Clear();
};
#endif /* RENDERER_H */
