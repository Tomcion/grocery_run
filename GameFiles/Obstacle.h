#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "../GameObjects/GameObject.h"

#include <memory>
#include <vector>

class Obstacle
{
private:
    std::unique_ptr<GameObject> upCollumn;
    std::unique_ptr<GameObject> downCollumn;
    void CreateObstacle(float y, float gapHeight, float width);
public:
    float min_x;
    glm::vec3 position;
    Obstacle(float y, float gapHeight, const glm::vec4& color, float width);
    Obstacle(float y, float gapHeight, const char* filepath, float width);
    void Render(const glm::mat4& proj);
};

class Obstacles
{
private:
    std::vector<Obstacle*> obstacles;
    glm::vec4 color;
    const char* filepath;
    float width;
    float gapHeight;
    bool useTexture;
public:
    Obstacles(const glm::vec4& color, float width, float gapHeight);
    Obstacles(const char* filepath, float width, float gapHeight);
    void AddObstacle(float y);
    void Render(const glm::mat4& proj);
    bool Filter(int index);
    void Reset();
    inline float getWidth() const { return width; }
    inline float getGapH() const { return gapHeight; }
    inline const Obstacle* getObstacle(int index) const { return obstacles[index]; }
    inline unsigned long getCount() const { return obstacles.size(); }
};

#endif /* OBSTACLE_H */
