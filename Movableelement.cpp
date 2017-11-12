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
// Constructeur
//=======================================
MovableElement::MovableElement()
{

}

//=======================================
// Destructeur
//=======================================
MovableElement::~MovableElement()
{

}

//=======================================
// Accesseurs en écriture
//=======================================
void MovableElement::setdx(float dx)
{
    _dx = dx;
}

void MovableElement::setdy(float dy)
{
    _dy = dy;
}

void MovableElement::sety(int y)
{
    _y = y;
}

//=======================================
// Accesseurs en lecture
//=======================================

// Position horizontale d'un élément
int MovableElement::getx() const
{
    return _x;
}

// Position verticale d'un élément
int MovableElement::gety() const
{
    return _y;
}

// Largeur d'un élément
int MovableElement::getw() const
{
    return _w;
}

// hauteur d'un élément
int MovableElement::geth() const
{
    return _h;
}

// vitesse horizontale d'un élément
int MovableElement::getdx() const
{
    return _dx;
}

// vitesse verticale d'un élément
int MovableElement::getdy() const
{
    return _dy;
}

// retourne un booléen permettant de savoir si l'élément est toujours dans l'écran
bool MovableElement::out() const
{
    return getx() + getw() < 0;
}


// identifiant permettant de reconnaître un élément
int MovableElement::getid()
{
    return _id;
}
