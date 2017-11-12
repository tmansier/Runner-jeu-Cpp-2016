#ifndef ANIMATEDGRAPHICELEMENT_H
#define ANIMATEDGRAPHICELEMENT_H
#include <SFML/Graphics.hpp>
#include "GraphicElement.h"
#include "StopWatch.h"



class AnimatedGraphicElement : public GraphicElement
{
private:
    int _current_clip_rect;// compteur permettant de changer le rectangle de lecture courant


    std::vector<sf::IntRect> _clip_rects;// vecteur des rectangles de lecture des images de l'animation

public:
    AnimatedGraphicElement(const std::vector<sf::IntRect> & clipRects , sf::Texture & image , int x ,int y ,int w , int h);
    void draw(sf::RenderWindow *window);
    void draw(sf::RenderWindow *window , sf::Vector2f position);
    void move();
    void setNextcurrentcliprect();
};

#endif // ANIMATEDGRAPHICELEMENT_H
