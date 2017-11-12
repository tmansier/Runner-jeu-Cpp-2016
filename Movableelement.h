#ifndef MOVABLEELEMENT_H
#define MOVABLEELEMENT_H

class MovableElement
{
protected:
    int _x; // position horizontale
    int _y;// position verticale
    int _w;// largeur
    int _h;// hauteur
    int _dx;// vitesse horizontale
    int _dy;// vitesse verticale
    int _id;// identifiant
public:
    MovableElement();
    virtual void move () = 0;
    bool out() const;
    void setdx(float dx);
    void setdy(float dy);
    int getx() const;
    int gety() const;
    int getdx() const;
    int getdy() const;
    int getw() const;
    int geth() const;
    void sety(int y);
    int getid();
    virtual ~MovableElement();
};

#endif // MOVABLEELEMENT_H
