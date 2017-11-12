#include "Bonus.h"

Bonus::Bonus(float x, float y, float w, float h, float dx, float dy, int id)
{
    _x = x;;// postion en horizontal
    _y = y;// position en vertical
    _w = w;// largeur
    _h = h;// hauteur
    _dx = dx;// vitesse verticale
    _dy = dy;// vitesse horizontale
    _id = id;// identifiant de l'obstacle qui permettra de définir son type et ce qu'il va faire
}

// déplace les bonus sur l'axe horizontal
void Bonus::move()
{
    _x += _dx;

}
