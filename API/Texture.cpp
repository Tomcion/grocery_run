#include <iostream>

#include "Texture.h"


Texture::Texture(const char* filepath)
    : renderer_id(0), filepath(filepath), image_buffer(nullptr), width(0), height(0), BPP(0)
{
    stbi_set_flip_vertically_on_load(1);
    image_buffer = stbi_load(filepath, &width, &height, &BPP, 4);

    if(image_buffer == nullptr)
    {
        std::cout << "Failed to load image: " << filepath << std::endl;
        std::cout << "Reason: " << stbi_failure_reason() << std::endl;
    }

    Call(glGenTextures(1, &renderer_id));
    Call(glBindTexture(GL_TEXTURE_2D, renderer_id));

    Call(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    Call(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    Call(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    Call(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    Call(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_buffer));
    Call(glBindTexture(GL_TEXTURE_2D, 0));

    stbi_image_free(image_buffer);
}

Texture::~Texture()
{
    Call(glDeleteTextures(1, &renderer_id));
}

void Texture::Bind(GLuint slot)
{
    Call(glActiveTexture(GL_TEXTURE0 + slot));
    Call(glBindTexture(GL_TEXTURE_2D, renderer_id));
}
