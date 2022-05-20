#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include <GL/glew.h>

class IndexBuffer
{
private:
    GLuint renderer_id;
    int unsigned count;
public:
    IndexBuffer(unsigned int* indices, int count);
    ~IndexBuffer();
    void Bind() const;
    inline unsigned int getCount() const { return count; }
};

#endif /* INDEX_BUFFER_H */
