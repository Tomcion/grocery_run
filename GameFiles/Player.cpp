#include "Player.h"

Player::Player(float width, float height, const glm::vec4 &color)
    :GameObject(width, height, color)
{
}

Player::Player(float width, float height, const char* filepath)
    :GameObject(width, height, filepath)
{
}

bool Player::CheckForCollision(const Obstacles &obstacles)
{
    return CollisionWithBounds() || CollisionWithObstacles(obstacles);
}

bool Player::CollisionWithBounds()
{
    if (position.y + height/2 > 700.0f || position.y - height/2 < 0.0f)
        return true;
    return false;
}

bool Player::CollisionWithObstacles(const Obstacles& obstacles)
{
    for (int i = 0; i < obstacles.getCount(); i++)
    {
        if (obstacles.getObstacle(i)->position.x - obstacles.getWidth()/2 < position.x + width/2 &&
           obstacles.getObstacle(i)->position.x + obstacles.getWidth()/2 >  position.x - width/2)
        {
            if (obstacles.getObstacle(i)->position.y - obstacles.getGapH()/2 > position.y - height/2 ||
               obstacles.getObstacle(i)->position.y + obstacles.getGapH()/2 < position.y + height/2)
                return true;
        }
    }
    return false;
}

