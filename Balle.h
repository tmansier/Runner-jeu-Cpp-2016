#ifndef BALLE_H
#define BALLE_H
#include <SFML/Graphics.hpp>
#include "Movableelement.h"

class Ball: public MovableElement
{
private:
bool _jumping; // booléen : la balle est en saut ou pas
int _pointdevie; // nombre de vies

public:
// Constructeur
Ball (int x, int y, int w, int h, int dx, int dy, int pointdevie);
virtual ~Ball() = default;

// Methodes
void move() override;
void Jump();
bool Isjumping();
void setJump (bool jumping);
int getpointvie();
void enleverpointvie(unsigned int suppr);
void ajouterpointvie(unsigned int ajout);
void setpointdevie (unsigned int points);
void sety(int y);
void setx(int x);
};

#endif // BALLE_H
