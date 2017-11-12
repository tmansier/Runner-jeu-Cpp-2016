#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <iostream>
#include <SFML/Graphics.hpp>

class StopWatch
{
    public:

        StopWatch(bool initrunning = false);

        virtual ~StopWatch();

        sf::Time getElapsedTime() const;


        bool isRunning() const;
        void start();

        void stop();

        void restart(bool stillrunning = false);


    private:
        sf::Clock   _clock;// l'horloge
        sf::Time    _buffer;// sauvegarde le temps
        bool        _running;// booléen permettant de savoir si la montre est en marche ou pas
};

#endif // STOPWATCH_H
