#ifndef GRAPHICELEMENT_H
#define GRAPHICELEMENT_H

#include <SFML/Graphics.hpp>

class GraphicElement : public sf::Sprite {
 private:
  sf::Texture _image;// image du sprite
  int _x, _y, _w, _h;// position horizontale et verticale, largeur, hauteur

 public:
  GraphicElement(sf::Texture &image, int x, int y, int w, int h);
  ~GraphicElement();
  void draw(sf::RenderWindow * window);
  void draw(sf::RenderWindow * window , sf::Vector2f position);
  void resize(int w, int h);
  void updatePos(sf::Vector2f position);
  void setPos(int x, int y);
  void getPos(int &x, int &y);
  void decaleX(int decalage);

};

#endif // GRAPHICELEMENT_H
