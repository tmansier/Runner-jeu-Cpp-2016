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

using namespace std;

//=====================
//=====================
// GESTION DU TEMPS
//=====================
//=====================

//=======================================
// Constructeur
//=======================================

StopWatch::StopWatch(bool initrunning) : _buffer(sf::Time::Zero), _running(initrunning)
{

}

//=======================================
// Destructeur
//=======================================

StopWatch::~StopWatch()
{
}

//=======================================
// Donne le temps écoulé lors du jeu
//=======================================
sf::Time StopWatch::getElapsedTime() const
{
    // si la montre est en marche :
    if(_running)

        // on incrémente le buffer
        return (_buffer + _clock.getElapsedTime());

    return _buffer;
}

//===============================================================
// Fonction booléenne renvoyant si la montre est en marche
//===============================================================

bool StopWatch::isRunning() const
{
    return _running;
}

//========================
// Démarrage de l'horloge
//========================

void StopWatch::start()
{
    // si la montre est à l'arrêt:
    if(!_running)
    {
        // passer le booléen à vrai et démarrer l'horloge
        _running = true;
        _clock.restart();
    }
}

//========================
// Arrêt de l'horloge
//========================

void StopWatch::stop()
{
    // si la montre est en marche
    if(_running)
    {
       // On ajoute dans le buffer le temps écoulé
        _buffer += _clock.getElapsedTime();

       // on passe le booléen à faux
        _running = false;
    }
}

//==========================
// Redémarrage de l'horloge
//==========================

void StopWatch::restart(bool stillrunning)
{
    // le buffer est remis à 0
    _buffer = sf::Time::Zero;

    //
    _running = stillrunning;

    //redémarrage de l'horloge
    _clock.restart();
}
