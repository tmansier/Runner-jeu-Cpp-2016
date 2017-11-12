#include "GraphicElement.h"
#include <iostream>
#include <fstream>

using namespace std;

//=======================================
// Constructeurs
//=======================================
GraphicElement::GraphicElement(sf::Texture &image, int x, int y, int w, int h)
    : _image(image), _x(x), _y(y), _w(w), _h(h) {
    this->setTexture(image);
    this->setPosition(sf::Vector2f(_x,_y));
    this->resize(_w,_h);
}

//==========================================
// accesseur
//==========================================
void GraphicElement::getPos(int &x, int &y) {
    x = _x;
    y = _y;
}

//=======================================
// Change la position du graphicElement
//=======================================
void GraphicElement::setPos(int x, int y) {
    _x = x;
    _y = y;
    updatePos(sf::Vector2f(_x,_y));
}

//==========================================
// mis à jour la position du graphicElement
//==========================================
void GraphicElement::updatePos(sf::Vector2f position)
{
    this->setPosition(position.x, position.y);
}


//==========================================
// Dessine le GraphicElement sur la fenêtre
//==========================================
void GraphicElement::draw(sf::RenderWindow * window) {
    window->draw(*this);
}

//============================================================================================
// Dessine les obstacles et bonus sur la fenêtre : il faut d'abord récuperer leurs positions
//============================================================================================
void GraphicElement::draw(sf::RenderWindow * window , sf::Vector2f position) {
    setPosition(position);
    window->draw(*this);
}

//==========================================
// Redimensionne le GraphicElement courant
//==========================================
void GraphicElement::resize(int w, int h) {

    sf::FloatRect bounds = this->getLocalBounds();// Retourne les positions et tailles du sprite courant
    float width_factor = 1.0 * w / bounds.width;// facteur de mise à l'échelle pour la largeur
    float height_factor = 1.0 * h / bounds.height;// facteur de mise à l'échelle pour la largeur
    this->setScale(width_factor, height_factor);
}


//==========================================
// Défilement du fond d'écran
//==========================================
void GraphicElement::decaleX(int decalage) {
    _x += decalage;
    updatePos(sf::Vector2f(_x,_y));
}


//==========================================
// Destructeurs
//==========================================
GraphicElement::~GraphicElement()
{
}
