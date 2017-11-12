#include "AnimatedGraphicElement.h"
#include "Movableelement.h"
#include "Balle.h"
#include "View.h"
#include "Model.h"
#include "GraphicElement.h"
#include "Movableelement.h"
#include "StopWatch.h"
#include "SlidingBackground.h"
#include <fstream>

#include <sstream>
#include <iostream>
#include <SFML/Graphics.hpp>

//=======================================
// Constructeurs
//=======================================
Ball::Ball(int x, int y, int w, int h, int dx, int dy, int pointdevie)
{
    _x = x;
    _y = y;
    _w = w;
    _h = h;
    _dx = dx;
    _dy = dy;
    _pointdevie = pointdevie;
}

//=======================================
// Déplacement de la balle
//=======================================
void Ball::move()
{
    // Tant que la balle est dans l'écran, elle peut bouger
    if(this->getx() > -1 && this->getx() + 50 < 801)
    {
        _x += _dx;
    }

    // Si la balle sort de l'écran, on réinitialise sa position à 0 pour qu'elle reste à l'écran
    if (this->getx() < 0)
    {
        _x = 0;
        _x += _dx;
    }

    // Si la balle sort de l'écran, on réinitialise sa position à la fin de l'écran pour qu'elle reste à l'écran
    if (this->getx() + 50 > 800)
    {
        _x = 750;
        _x += _dx;
    }

    // on ajoute une vitesse à la position y de la balle utilisée lors des sauts
        _y += _dy;

}

void Ball::sety(int y)
{
    _y = y;
}

//=====================
//=====================
// SAUTS
//=====================
//=====================

//=================================================================
// Fonction booléenne permettant de savoir si la balle est en saut
//=================================================================
bool Ball::Isjumping()
{
    return _jumping;
}

void Ball::setJump (bool jumping)
{
    _jumping=jumping;
}


//=====================
//=====================
// POINTS DE VIE
//=====================
//=====================

int Ball::getpointvie()
{
    return _pointdevie;
}

//=======================================
// Enlève des points de vie
//=======================================
void Ball::enleverpointvie(unsigned int suppr)
{
    _pointdevie -= suppr;
}

//=======================================
// Ajoute des points de vie
//=======================================
void Ball::ajouterpointvie(unsigned int ajout)
{
    _pointdevie += ajout;
}

void Ball::setpointdevie(unsigned int points)
{
    _pointdevie = points;
}
void Ball::setx(int x)
{
    _x = x;
}


