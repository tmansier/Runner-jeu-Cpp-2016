#ifndef _VIEW_
#define _VIEW_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GraphicElement.h"
#include "Movableelement.h"
#include "StopWatch.h"
#include "SlidingBackground.h"
#include "AnimatedGraphicElement.h"


static const auto BACKGROUND_IMAGE = "Images/city.png";
static const auto TIME_FONT = "Polices/Antique Olive.ttf";
static const auto TEXTFONT = "Polices/replay.ttf";
static const auto MUSICNAME = "Music/musicjeu.ogg";
static const auto OBSTACLEIMAGE ="Images/Bomb2.png";
static const auto BUTTONPLAYMENU ="Images/playbutton.png";
static const auto BUTTON = "Images/Button.png";
static const auto BUTTONBACK = "Images/Buttonback.png";
static const auto DECOMENUS = "Images/Menuboard.png";
static const auto BLUEROBOT="Images/SpritetotalBlueRobot.png";
static const auto VOLUME = "Images/Volume.png";
static const auto BARRE_VIE = "Images/Barrevie.png";
static const auto CROIX = "Images/Cross.png";
static const auto PLUSVOLUME = "Images/upVol.png";
static const auto MOINSVOLUME = "Images/downVol.png";
static const auto COIN = "Images/Piece2.png";
static const auto LIFE = "Images/life.png";
static const auto MECHANT1 = "Images/monstrena.png";
static const auto PICS = "Images/Pics.png";
static const auto BACKGROUND_IMAGE2 = "Images/city_1.png";
static const auto FICHIERANGLAIS = "ANGL.txt";
static const auto FICHIERFRANCAIS = "FR.txt";
static const auto FONTBLOCKTITLE = "Polices/blocked.ttf";
static const auto ANGLAISIMAGE = "Images/union-jack.jpg";
static const auto FRANCAISIMAGE = "Images/french-flag.png";
static const auto PAUSEIMAGE = "Images/pause.png";
static const auto IUTBORD = "Images/IUT-Bdx-1.png";
static const auto SFML = "Images/SFML Logo.png";


class GraphicElement;
class MovableElement;
class Model;

class View {
private:

    sf::RenderWindow * _window;// Fenêtre du jeu
    Model * _model;// le modèle

    int _w, _h;// largeur et hauteur de la fenêtre de jeu
    int _x, _y; // ses positions
    int _xsouris ,_ysouris;
    int _menu;// permet de gérer les différentes actions du menu
    int cpt;
    int cptscore;
    int l;
    int probl;
    int lb;
    int problb;
    int compteur;
    int cptcptscore; // le compteur permettant d'afficher seulement les 10 premiers scores
    int xbarredevie; // position des rectangles de vie dans la barre de vie
    int nivolume; // permet de récupérer le niveau du son
    int savespeed; // sauvegarde de la vitesse des obstacles
    int savespeedback2; // sauvegarde de la vitesse du fond d'écran
    int coinnbr;


    bool volume;
    bool francais; // booléen permettant de savoir si on est en français ou en anglais
    bool pause;// booléen permettant de savoir si l'écran de pause est activé ou pas

    std::string tps;
    std::string jouer;
    std::string para;
    std::string bout;
    std::string ret;
    std::string fdj;
    std::string rej;
    std::string textvolume;
    std::string coinstring;
    std::string scorescore; // texte possédant les 10 premiers scores


    StopWatch * _timer;// l'horloge
    StopWatch * _timerintro;


    AnimatedGraphicElement * _balle;// la balle


    //GRAPHICELEMENTS
    GraphicElement * _buttonplaysprite;
    GraphicElement * _buttonparasprite;
    GraphicElement * _buttonscoresprite;
    GraphicElement * _buttonquitsprite;
    GraphicElement * _back;// bouton quitter dans le menu
    GraphicElement * _Volspr;
    GraphicElement * _cross; // permet de voir quand le volume est éteint dans les paramêtres
    GraphicElement * _menudeco;
    GraphicElement * _downvol;
    GraphicElement * _upvol;
    GraphicElement * buttonpausequit;
    GraphicElement * _restart;
    GraphicElement * _backmenu;// bouton quitter quand on perd
    GraphicElement * _pause;
    GraphicElement * _mechant; // obstacles vert dans le jeu
    GraphicElement * _mechantGO; // obstacle vert quand on à perdu (décor)
    GraphicElement * _mechantpause; // obstacle vert dans la fenêtre pause (décor)
    GraphicElement * angl;
    GraphicElement * france;
    GraphicElement * _obstacle;
    GraphicElement * _pic;
    GraphicElement * _coin;// pièces
    GraphicElement * _life;
    GraphicElement * _barrevie;
    GraphicElement * _sfml;
    GraphicElement * _iutbordeaux;



    // TEXTURE
    sf::Texture _crosstext;
    sf::Texture _iconevolume;
    sf::Texture _buttonplaytext;// la base de chaque bouton du menu
    sf::Texture _backtext;
    sf::Texture _menusdecotext;
    sf::Texture _background;
    sf::Texture _background2;
    sf::Texture _downvtext;// bouton moins pour gérer le volume dansles paramêtres
    sf::Texture _upvtext; // bouton plus pour gérer le volume dansles paramêtres
    sf::Texture _pausetexture;
    sf::Texture anglaistexture;
    sf::Texture francaistexture;
    sf::Texture _balletext;
    sf::Texture _obstacletext;
    sf::Texture _mechanttext;
    sf::Texture _pictext;
    sf::Texture _cointext;// pièces
    sf::Texture _lifetext;
    sf::Texture _barrevietexture;
    sf::Texture _iuttext; // logo IUT
    sf::Texture _sfmltext;// logo sfml

    //FONT
    sf::Font _fontplaytext;
    sf::Font _titlefont;
    sf::Font _fonttimetext;

    // TEXT
    sf::Text _playtext;
    sf::Text _paratext;// affichage du mot parametres dans le menu
    sf::Text _scoretext;// affichage du mot score dans le menu
    sf::Text _quittext;
    sf::Text _paratextpara;// affichage du mot parametre dans les paramêtres
    sf::Text _backecrit;// bouton quitter dans le menu pause
    sf::Text _timetext;
    sf::Text _voltext;
    sf::Text _gameovertext;// affichage "fin du jeu"
    sf::Text _backmenuecrit;// affichage du bouton menu quand on perd
    sf::Text _restarttext;// Bouton rejouer quand on perd
    sf::Text _scorego; // texte déclarant le mot "score" lors du jeu
    sf::Text _scorescorescore; // texte affichant les points du score
    sf::Text _scoretitle; // affichage du mot "score" dans le jeu
    sf::Text _titletitle; // Titre "neon city"
    sf::Text _Language;
    sf::Text _quitpause;
    sf::Text coinecrit;


    //Slidingbackground
    SlidingBackground *_backgroundSprite;
    SlidingBackground *_backgroundSprite2;


    //SOUND
    sf::SoundBuffer buffer;
    sf::Sound sound;

    //RECTANGLE DE BARRE DE VIE
    sf::RectangleShape rectangle;

public:
    View(int w, int h);
    ~View();

    void setModel(Model * model);
    void draw();
    void syncronize();
    bool treatEvents();
    void RectangleLecture(std::vector<sf::IntRect> &rectanglesDeLecture);
    void RectangleLecture2(std::vector<sf::IntRect> &rectanglesDeLecture);
    std::string Lecturescore();
    std::string Lireligne(int numligne , std::string fichiername);
    void Restart();
    void Pause();


};
#endif
