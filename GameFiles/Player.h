#ifndef PLAYER_H
#define PLAYER_H

#include "../GameObjects/GameObject.h"
#include "Obstacle.h"

class Player : public GameObject
{
public:
    Player(float width, float height, const glm::vec4 &color);
    Player(float width, float height, const char* filepath);
    bool CheckForCollision(const Obstacles& obstacles);
    bool CollisionWithBounds();
    bool CollisionWithObstacles(const Obstacles& obstacles);
};

#endif /* PLAYER_H */
