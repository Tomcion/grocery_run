#ifndef TEXTURE_H
#define TEXTURE_H

#include "../3rd_party/stb_image/stb_image.h"

#include "Renderer.h"

class Texture
{
public:
    Texture(const char* filepath);
    ~Texture();
    void Bind();
    void Bind(GLuint slot);
private:
    GLuint renderer_id;
    const char* filepath;
    unsigned char* image_buffer;
    int width, height, BPP;
};

#endif /* TEXTURE_H */
