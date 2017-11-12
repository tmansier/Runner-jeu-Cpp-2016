#include "SlidingBackground.h"
#include "SFML/Graphics.hpp"

using namespace std;

//=======================================
// Constructeur
//=======================================

SlidingBackground::SlidingBackground(sf::Texture &image, int w, int h, unsigned int speed)
    :_width(w), _height(h), _speed(speed), _left(image, 0, 0, w, h), _right(image, w, 0, w, h) {
    _left.resize(w,h);
    _right.resize(w,h);
}

//=======================================
// Destructeur
//=======================================
SlidingBackground::~SlidingBackground()
{

}

//=======================================
// Accesseurs en lecture et écriture
//=======================================

int SlidingBackground::getspeed() const
{
    return _speed;
}

void SlidingBackground::setSpeed(unsigned int speed) {
    _speed = speed;
}


//=======================================
//Défilement du fond d'écran
//=======================================
void SlidingBackground::draw(sf::RenderWindow *window) {
    int x, y;

    _left.getPos(x, y);// affectation des positions au premier fond d'écran

    //on verifie que le premier fond d'écran esy encore visible sinon on l'initialise à la suite du suivant
    if (x-_speed <= -_width)
    {
        _left.setPos(_right.getPosition().x + _width - 10, 0);
    }

    else
    {
        _left.decaleX(-_speed);
    }

    // affectation des positions du deuxième fond d'écran
    _right.getPos(x, y);

    //on verifie que le 2e fond d'écran est encore visible sinon on l'initialise à la suite du premier
    if (x-_speed <= -_width)
    {
        _right.setPos(_left.getPosition().x + _width - 10, 0);
    }

    else
    {
        _right.decaleX(-_speed);
    }

    // dessine les deux fonds dans la fenêtre
    _left.draw(window);

    _right.draw(window);
}



