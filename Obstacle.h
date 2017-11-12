#ifndef OBSTACLE_H
#define OBSTACLE_H
#include "Movableelement.h"


class Obstacle : public MovableElement
{
private:

public:

    Obstacle(float x, float y, float w, float h, float dx, float dy , int id);
    void move() override;
};

#endif // OBSTACLE_H
