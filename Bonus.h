#ifndef BONUS_H
#define BONUS_H

#include "Movableelement.h"

class Bonus : public MovableElement
{
private :

public:
    Bonus(float x, float y, float w, float h, float dx, float dy , int id );
    void move() override;

};

#endif // BONUS_H
