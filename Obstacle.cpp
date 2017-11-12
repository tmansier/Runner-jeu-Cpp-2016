#include "Obstacle.h"

Obstacle::Obstacle(float x, float y, float w, float h, float dx, float dy, int id)
{
    _x = x;// postion en horizontal
    _y = y;// position en vertical
    _w = w;// largeur
    _h = h;// hauteur
    _dx = dx;// vitesse verticale
    _dy = dy;// vitesse horizontale
    _id = id; // identifiant de l'obstacle qui permettra de définir son type et ce qu'il va faire
}

// déplace les obstacles sur l'axe horizontal
void Obstacle::move()
{
    _x += _dx;

}
