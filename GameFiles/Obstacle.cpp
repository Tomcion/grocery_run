#include "Obstacle.h"

Obstacle::Obstacle(float y, float gapHeight, const glm::vec4& color, float width)
{
    upCollumn = std::make_unique<GameObject>(width, 700.0f, color);
    downCollumn = std::make_unique<GameObject>(width, 700.0f, color);
    CreateObstacle(y, gapHeight, width);
}

Obstacle::Obstacle(float y, float gapHeight, const char* filepath, float width)
{
    upCollumn = std::make_unique<GameObject>(width, 700.0f, filepath);
    downCollumn = std::make_unique<GameObject>(width, 700.0f, filepath);
    CreateObstacle(y, gapHeight, width);
}

void Obstacle::CreateObstacle(float y, float gapHeight, float width)
{
    position = glm::vec3(900.0 + width / 2, y + (700.0f - 300.0f) / 2, 0.0f);
    upCollumn->position = glm::vec3(position.x, position.y + gapHeight/2 + 350.0f, 0.0f);
    downCollumn->position = glm::vec3(position.x, position.y - gapHeight/2 - 350.0f, 0.0f);
    min_x = - width / 2;
}

void Obstacle::Render(const glm::mat4& proj)
{
    position.x -= 6.0f;
    upCollumn->position.x = position.x;
    downCollumn->position.x = position.x;
    upCollumn->Render(proj);
    downCollumn->Render(proj);
}

Obstacles::Obstacles(const glm::vec4& color, float width, float gapHeight)
    : color(color), width(width), gapHeight(gapHeight), useTexture(false)
{
}

Obstacles::Obstacles(const char* filepath, float width, float gapHeight)
    : filepath(filepath), width(width), gapHeight(gapHeight), useTexture(true)
{
}

void Obstacles::AddObstacle(float y)
{
    if(useTexture)
        obstacles.push_back(new Obstacle(y, gapHeight, filepath, width));
    else
        obstacles.push_back(new Obstacle(y, gapHeight, color, width));

}

void Obstacles::Render(const glm::mat4& proj)
{
    for(int i = 0; i < obstacles.size(); i++)
    {
        Filter(i);
        if(obstacles.size() != 0)
            obstacles[i]->Render(proj);
    }
}

bool Obstacles::Filter(int index)
{
    if(obstacles[index]->position.x <= obstacles[index]->min_x)
    {
        delete obstacles[index];
        obstacles.erase(obstacles.begin());
        return false;
    }
    return true;
}

void Obstacles::Reset()
{
    for(int i = 0; i < obstacles.size(); i++)
    {
        delete obstacles[i];
    }
    obstacles.clear();
}
