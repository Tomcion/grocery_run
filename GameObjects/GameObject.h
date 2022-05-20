#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../API/Shader.h"
#include "../API/VertexArray.h"
#include "../API/VertexBuffer.h"
#include "../API/IndexBuffer.h"
#include "../API/Texture.h"
#include "../API/Renderer.h"

#include <memory>

class GameObject
{
private:
    std::unique_ptr<IndexBuffer> ibo;
    std::unique_ptr<VertexBuffer> vbo;
    std::unique_ptr<VertexArray> vao;
    std::unique_ptr<Shader> shader;
    std::unique_ptr<Texture> texture;
    void CreateObject();
protected:
    float width;
    float height;
    const char* imagePath;
    bool useTexture;
public:
    glm::vec3 position;
    glm::vec4 color;
    GameObject(float width, float height, const glm::vec4& color);
    GameObject(float width, float height, const char* image_path);
    void Render(const glm::mat4& proj);
    inline float getWidth() const { return width; }
    inline float getHeight() const { return height; }
};

#endif /* GAME_OBJECT_H */
