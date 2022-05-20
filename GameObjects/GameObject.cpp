#include "GameObject.h"

#include <iostream>

GameObject::GameObject(float width, float height, const glm::vec4& color)
    : width(width), height(height), color(color), useTexture(false)
{
    CreateObject();
    shader = std::make_unique<Shader>("Shaders/Basic.glsl");
}

GameObject::GameObject(float width, float height, const char* image_path)
    : width(width), height(height), imagePath(image_path), useTexture(true)
{
    CreateObject();
    shader = std::make_unique<Shader>("Shaders/Textured.glsl");
    shader->Bind();
    texture = std::make_unique<Texture>(image_path);
    texture->Bind(0);
    shader->setUniform1i("u_Texture", 0);
}

void GameObject::CreateObject()
{
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    float vertices[] = {
         width / 2,  height / 2, 1.0f, 1.0f,
         width / 2, -height / 2, 1.0f, 0.0f,
        -width / 2, -height / 2, 0.0f, 0.0f,
        -width / 2,  height / 2, 0.0f, 1.0f,
    };


    ibo = std::make_unique<IndexBuffer>(indices, 6);
    vbo = std::make_unique<VertexBuffer>(vertices, 16 * sizeof(float));
    vao = std::make_unique<VertexArray>();
    vao->AddAttr(2);
    vao->AddAttr(2);
    vao->Buffer(*vbo);
}

void GameObject::Render(const glm::mat4& proj)
{
    shader->Bind();
    shader->setUniformMat4f("u_MVP", proj * glm::translate(glm::mat4(1.0f), position));
    if (useTexture)
    {
        texture->Bind(0);
        shader->setUniform1i("u_Texture", 0);
    } else {
        shader->setUniform4f("u_Color", color.r, color.g, color.b, color.a);
    }
    Renderer::Draw(*vao, *ibo, *shader);
}

