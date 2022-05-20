#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#include <assert.h>

#define Call(x) ClearErrors(); x; assert(LogError(__FILE__, __LINE__));

void ClearErrors();

bool LogError(const char* file, int line);

class Renderer
{
public:
    static void Draw(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shader);
    static void Clear();
};
#endif /* RENDERER_H */
