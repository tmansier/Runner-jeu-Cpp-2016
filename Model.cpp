#include "AnimatedGraphicElement.h"
#include "Movableelement.h"
#include "Balle.h"
#include "View.h"
#include "Model.h"
#include "Bonus.h"
#include "GraphicElement.h"
#include "Movableelement.h"
#include "StopWatch.h"
#include "SlidingBackground.h"
#include <fstream>
#include"Obstacle.h"
#include <sstream>
#include <iostream>
#include <SFML/Graphics.hpp>

size_t n;

using namespace std;

//=======================================
// Constructeurs
//=======================================
Model::Model(int w, int h)
  :  _w(w), _h(h) {
    _b = new Ball(100,400,50,50,0,0,100); // création de la balle
    piece = 0;// initialisation à 0 du nombre de pièce
    superpose = false; // initialisation du booléen supperpose à faux
    superposebonus = false; // initialisation du booléen supperposebonus à faux
    initspeed = -5; // initialisation de la vitesse des obstacles à -5

}
//=======================================
// Destructeurs
//=======================================
Model::~Model(){
    delete _b;// suppression de la balle

}
//==================================================================
// réinitialisation de la balle lors d'une nouvelle partie
//==================================================================
void Model::restart()
{
    _b->setx(100);// initialisation de la position de la balle sur l'axe horizontal en début d'écran
    _b->sety(400);// initialisation de la position de la balle sur l'axe vertical en accord avec le décor

    // initialisation de la vitesse à 0 (vitesse nulle)
    _b->setdx(0);
    _b->setdy(0);

    // initialisation du booléen "en saut": la balle est à la base au sol
    _b->setJump(false);

    piece = 0; // initialisation du nombre de pièce à 0
    superpose = false; // initialisation du booléen superpose à faux : il n'y a pas encore d'obstacle à l'écran
    superposebonus = false; // initialisation du booléen superposebonus à faux : il n'y a pas encore de bonus à l'écran
}

//=========================
//=========================
// DEPLACEMENTS
//=========================
//=========================

//=============================================
// Avancement des éléments (obstacles, bonus)
//=============================================
void Model::nextStep(){

// fait bouger la balle
_b->move();

for (MovableElement*m : _elements)
{
    // fait avancer les obstacles
    m->move();

    // Si le bonus sort de l'écran, il est supprimé
    if(m->out())
        SupprimerObstacle(m);
}
for (Bonus*n : _elementsbonus)
{
    // fait avancer les bonus
    n->move();

    // Si le bonus sort de l'écran, il est supprimé
    if(n->out())
        SupprimerBonus(n);
}

}

//============================================================
// Déplacement de la balle en fonction des touches du clavier
//============================================================
void Model::moveBAll(bool left)
{

    // Si la balle est en saut
    if (_b->Isjumping())
    {
        // Et si la touche de gauche est enfoncée :
       if (left == true)
       {
            // on affecte -10 à la position de la balle, ce qui l'a fait déplacer vers la gauche
            _b->setdx(-10);
            _b->move();

       }
       // Ou si la touche droite est enfoncée :
       else if (left ==false)
       {

            // on affecte 10 à la position de la balle, ce qui l'a fait déplacer vers la droite
           _b->setdx(10);
           _b->move();
       }
    }

    // Si la balle n'est pas en saut
    else
    {
        // Et si la touche de gauche est enfoncée :
        if (left == true)
        {
            // on affecte -15 à la position de la balle, ce qui l'a fait déplacer vers la gauche
            _b->setdx(-15);
            _b->move();

        }

        // Ou si la touche droite est enfoncée :
        if (left ==false)
        {
            // on affecte 15 à la position de la balle, ce qui l'a fait déplacer vers la droite
            _b->setdx(15);
            _b->move();

        }
    }
}

//=====================
// Arrêt de la balle
//=====================

void Model::stopballx()
{
    // met la vitesse à 0
    _b->setdx(0);

    // affecte la vitesse nulle qui stoppe la balle
    _b->move();
}

//=======================================
// Position de la balle
//=======================================
void Model::getBallPostion(int & x ,int & y)
{
  x = _b->getx();
  y = _b->gety();
}

sf::Vector2f Model::SetBallPostion()
{
sf::Vector2f vector = sf::Vector2f(_b->getx(),_b->gety());
return vector;

}

//=========================
//=========================
// DIMENSIONS DE LA BALLE
//=========================
//=========================


// accesseurs en lecture de la hauteur
int Model::geth()
{
    return _h;
}

// accesseurs en lecture de la hauteur
int Model::getw()
{
    return _w;
}

// donne les dimenssions à la balle
void Model::getballDimension(int & w, int & h)
{
    w = _b->getw();
    h = _b->geth();
}

//=========================
//=========================
// POINTS DE VIE
//=========================
//=========================

//==============================
// Retire des points de vie
//==============================
void Model::retirerpointvieballe(int ptsperdu)
{
    // Tant que notre cota de points de vie n'est pas inférieur à 0 :
    if (_b->getpointvie() - ptsperdu >= 0)
    {
        // On appelle la fonction enleverpointvie de la classe Balle pour retirer les points voulus
        _b->enleverpointvie(ptsperdu);
    }

    // Si le joueur a un score inférieur à 0 ( si il a perdu ) :
    else
    {
        // les points de vie se réinitialise à 0
        _b->setpointdevie(0);
    }

}

//==============================
// Ajoute des points de vie
//==============================
void Model::ajouterpointdevieballe(int ptsajout)
{
    // Tant que notre cota de points de vie n'est pas supérieur à 100 ( nombre max de vies ):
    if (_b->getpointvie() + ptsajout <= 100)
    {
        // On appelle la fonction ajouterpointvie de la classe Balle pour ajouter les points voulus
        _b->ajouterpointvie(ptsajout);
    }

    // Si le joueur possède toutes ses vies :
    else
    {
        // Il ne peut plus en récuperer, il reste donc à 100
        _b->setpointdevie(100);
    }

}

//======================================================
// Accesseurs en lecture et écriture des points de vie
//======================================================

int Model::getpointdevieballe()
{
    return _b->getpointvie();
}

void Model::setpointvieballe(int nb)
{
    _b->setpointdevie(nb);
}

//=========================
//=========================
// SAUT
//=========================
//=========================

//==============================
// Initialise le saut
//==============================
void Model::startjump()
{
    // Si la balle n'est pas en saut
    if(!_b->Isjumping())
    {
        // On passe le booléen "en saut" en vrai
        _b->setJump(true);

        // on affecte -15 à la position de la balle, ce qui la fait décoller
        _b->setdy(-15);

    }
}

//==============================
// Gère le saut
//==============================
void Model::Evolutionjump()
{
    // Tant que la balle est en saut
    if(_b->Isjumping())
    {
        // on ajoute une vitesse à la balle qui lui permet de descendre au fur et à mesure
        _b->setdy(_b->getdy()+1);

        // Si la balle est au maximum de son saut ( position à 400 )
        if(_b->gety() == 400)
        {
            // la vitesse de la balle devient nulle, elle ne monte donc plus
            _b->setdy(0);
            // le booléen "en saut" devient faux pour sortir de la fonction
            _b->setJump(false);
        }

        if(_b->gety() >= 400){
                _b->setdy(0);
                _b->setJump(false);
       }

        // Si la balle dépasse la position max en saut:
        if (_b->gety() > 400)
        {
            // Elle revient à celle-ci
            _b->sety(400);
        }
    }


}

//=========================
//=========================
// OBSTACLES
//=========================
//=========================

const std::set<MovableElement *> & Model::get_element() const
{
    return _elements;
}

//==============================
// Ajoute un obstacle
//==============================
void Model::AjouterObstacle()
{
    // création d'un obstacle avec un identifiant aléatoire entre 0 et 2 permettant d'avoir des obstacles différents
    Obstacle * o = new Obstacle(800,400,50,50,initspeed,0,rand()%3 );

    // suivant l'obstacle sa position verticale est différente

    // si c'est l'obstacle 0
    if ( o->getid() == 0)
    {
        // on le place à 400 en vertical
        o->sety(400);
    }

    // si c'est l'obstacle 1
    if (o->getid() == 1)
    {
        // on le place à 300 en vertical
        o->sety(300);
    }

    // si c'est l'obstacle 0
    if (o->getid() == 2)
    {
        // on le place à 400 en vertical
        o->sety(400);
    }

    // Pour tous les obstacles apparaissant sur l'écran
    for (MovableElement*m : _elements)
    {
        // Si l'obstacle touche un autre obstacle
        if (o->getx() + o->getw() > m->getx() && o->getx() < m->getx() + m->getw())
        {
            // le booléen superpose passe à vrai
            superpose = true;
        }

    }

    // Pour tous les bonus apparaissant sur l'écran
    for (Bonus*b : _elementsbonus)
    {
        // Si l'obstacle touche un bonus
        if (o->getx() + o->getw() > b->getx() && o->getx() < b->getx() + b->getw())
        {
            // le booléen superpose passe à vrai
            superpose = true;
        }
    }

    // Tant que des éléments ne se supperposent pas
    if(!superpose)
    {
        //on ajoute l'obstacle créé dans le tableau set stockant ceux-ci
        _elements.insert(o);
    }

    else
    {
        // Si l'obstacle est superposé à un autre ou un bonus, on le supprime
        delete o;
    }

    // on remet ensuite le booléen superpose à faux une fois avoir verifier la superposition de l'obstacle avec les autres éléments
    superpose = false;
}

//============================================
// Collision de la balle avec un obstacle
//============================================
void Model::Collision()
{
    // Pour tous les obstacles de l'écran
    for (MovableElement* obstacle: _elements)
    {
        // Si la balle et l'obstacle se touche:
        if (_b->getx() + _b->getw() > obstacle->getx() && _b->getx() < obstacle->getx() + obstacle->getw() && _b->gety() +  _b->getw() > obstacle->gety() && _b->gety() < obstacle->gety() + obstacle->geth())
        {
            // on appelle la fonction SupprimerObstacle, qui va supprimer celu-ci
            SupprimerObstacle(obstacle);

            // Selon le type d'obstacles, la perte de vies est plus ou moins importante

            // Si c'est l'obstacle 0:
            if (obstacle->getid() == 0)
            {
                // on ne retire que 10 points de vie
                retirerpointvieballe(10);
            }

            // Si c'est l'obstacle 1:
            if (obstacle->getid() == 1)
            {
                // on  retire 20 points de vie
                retirerpointvieballe(20);
            }

            // Si c'est l'obstacle 2:
            if (obstacle->getid() == 2)
            {
                // on retire alors 30 points de vie
                retirerpointvieballe(30);
            }

        }
    }
    // VERIFICATION du nombre d'obstacles ( pour le programmeur )
    cout << _elements.size() << endl;

}


//============================================
// Supprime un obstacle
//============================================
void Model::SupprimerObstacle(MovableElement *m)
{
    _elements.erase(m); // Le supprime du tableau set de stockage
   delete m; // Supprime l'obstacle
}

//=========================
//=========================
// BONUS
//=========================
//=========================

const std::set<Bonus *> & Model::get_elementbonus() const
{
    return _elementsbonus;
}

//============================================
// Ajoute un bonus
//============================================
void Model::AjouterBonus()
{
    // création d'un bonus avec un identifiant aléatoire entre 0 et 1 permettant de définir des bonus différents
    Bonus * b = new Bonus(800,350,25,25,initspeed,0,rand()%2);

    // Pour tous les obstacles de l'écran
    for (MovableElement*m : _elements)
    {

        // Si le bonus touche un obstacle:
        if (b->getx() + b->getw() > m->getx() && b->getx() < m->getx() + m->getw())
        {
            // le booléen superposebonus passe à vrai
            superposebonus = true;
        }

    }

    // Pour tous les bonus de l'écran
    for (Bonus*c : _elementsbonus)
    {
        // Si le bonus touche un autre bonus:
        if (b->getx() + b->getw() > c->getx() && b->getx() < c->getx() + c->getw())
        {
            // le booléen superposebonus passe à vrai
            superposebonus = true;
        }
    }

    // Tant que les bonus ne sont supperposés à rien
    if (!superposebonus)
    {
        //on ajoute le bonus créé dans le tableau set stockant ceux-ci
        _elementsbonus.insert(b);
    }


    // on remet ensuite le booléen superposebonus à faux une fois avoir verifier la superposition du bonus avec les autres éléments
    superposebonus = false;

}

//============================================
// Collision de la balle avec un bonus
//============================================
void Model::CollisionBonus()
{
    // Pour tous les bonus de l'écran
    for (Bonus * bonus: _elementsbonus)
    {
        // Si la balle et le bonus se touche:
        if (_b->getx() + _b->getw() > bonus->getx() && _b->getx() < bonus->getx() + bonus->getw() && _b->gety() + _b->getw()  > bonus->gety() && _b->gety() < bonus->gety() + bonus->geth() )
        {
            // on appelle la fonction SupprimerBonus (implémentée plus bas), qui va supprimer celu-ci
            SupprimerBonus(bonus);

             // Selon le type de bonus, il ne va pas réaliser la même action :

             // Si c'est le bonus 0:
            if ( bonus->getid() == 0)
            {
               // le nombre de pièces augmente de 1
               piece += 1;
            }

            // Si c'est le bonus 1:
            if ( bonus->getid() == 1)
            {
                // il permet d'ajouter 10 vies au compteur de vie
                ajouterpointdevieballe(10);
            }
        }
    }

    // VERIFICATION du nombre de bonus ( pour le programmeur )
    cout << _elementsbonus.size() << endl;
}

//============================================
// Supprime un bonus
//============================================
void Model::SupprimerBonus(Bonus *m)
{
    _elementsbonus.erase(m); // Le supprime du tableau set de stockage
    delete m; // Supprime l'obstacle

}

//============================================
// Pièces
//============================================
int Model::getnbpiece()
{
    return piece;
}

//=========================
//=========================
// VITESSE DES ELEMENTS
//=========================
//=========================

//============================================
// Vitesse des obstacles
//============================================

// Accesseur en lecture
int Model::getinitspeed()
{
    return initspeed;
}

// change la vitesse des nouveaux obstacles
void Model::changeinitspeed(int dx)
{
    initspeed = dx;
}
// affecte la vitesse à chaque obstacles (nouveaux et déjà existant)
void Model::setspeedobstacle(MovableElement * m , int dx)
{
    changeinitspeed(dx);
    m->setdx(dx);

}

//============================================
// Vitesse des bonus
//============================================

// affectation de la vitesse au bonus
void Model::setspeedbonus(Bonus * b,int dx)
{

    b->setdx(dx);
}

//============================================
// Vitesse du fond d'écran
//============================================

//affectation de la vitesse au fond
void Model::setspeedbackground(SlidingBackground * sb , int dx)
{
    sb->setSpeed(dx);
}


//=============================================
//=============================================
// SUPPRESSION DES ELEMENTS DES TABLEAUX
//=============================================
//=============================================

//============================================
// Suppression des obstacles
//============================================
void Model::resetsetelement()
{
    _elements.clear();
}

//============================================
// Suppression des bonus
//============================================
void Model::resetsetelementbonus()
{
    _elementsbonus.clear();
}
