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
AnimatedGraphicElement::AnimatedGraphicElement(const std::vector<sf::IntRect> &clipRects, sf::Texture &image, int x, int y, int w, int h):
    _clip_rects(clipRects),
    GraphicElement(image,x,y,w,h),
    _current_clip_rect(0)
{
    //redimensionne le rectangle de lecture
    this->resize(w,h);
}

//=======================================
// DESSIN DE LA BALLE
//=======================================

// permet de faire marcher le bonhomme (= balle)
void AnimatedGraphicElement::draw(sf::RenderWindow *window)
{
    // Tant que le compteur est inférieur à 18 :
    if (_current_clip_rect < 18)
    {
        //Mettre l'image de la balle dans le rectangle de lecture courant
        setTextureRect(_clip_rects.at(_current_clip_rect));
    }

    // Sinon remettre le compteur à 0
    else
    {
        _current_clip_rect = 0;
    }

    // Dessine le rectangle de lecture courant( la balle )
    window->draw(*this);
}

// Affectation des positions
void AnimatedGraphicElement::move()
{
  setPosition(sf::Vector2f(getPosition().x , getPosition().y));
}

//Permet de passer au rectangle de lecture suivant
void AnimatedGraphicElement::setNextcurrentcliprect()
{
    _current_clip_rect +=1;
}
