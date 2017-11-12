#ifndef SLIDINGBACKGROUND_H
#define SLIDINGBACKGROUND_H

#include "GraphicElement.h"
#include <iostream>


class SlidingBackground
{
  private:
    GraphicElement _left;// premier fond d'écran
    GraphicElement _right;// deuxième fond d'écran
    int _width;// largeur du fond d'écran
    int _height;// la hauteur du fond d'écran
    int _speed;// sa vitesse de défilement

  public:
    SlidingBackground(sf::Texture &image, int w, int h, unsigned int speed);
    ~SlidingBackground();
    void draw(sf::RenderWindow *window); // le principe est de faire suivre deux fonds ayant la même image
    void setSpeed(unsigned int speed);
    int getspeed() const;
};

#endif // SLIDINGBACKGROUND_H

