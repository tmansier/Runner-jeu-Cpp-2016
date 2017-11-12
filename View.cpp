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
// PAUSE
//=====================
//=====================

//==============================
// Gestion de l'écran de pause
//==============================
void View::Pause()
{
    // sauvegarde la vitesse en cours des obstacles
    savespeed = _model->getinitspeed();

    // Sauvegarde de la vitesse du fond d'écran
    savespeedback2 = _backgroundSprite->getspeed();

    // on arrête la vitesse de tous les obstacles
    for (MovableElement * m : _model->get_element())
    {
        m->setdx(0);

    }

    // On arrête la vitesse de tous les bonus
    for (Bonus * n : _model->get_elementbonus())
    {
        n->setdx(0);
    }

    // On arrête la vitesse des de fonds d'écran
    _backgroundSprite->setSpeed(0);
    _backgroundSprite2->setSpeed(0);

    // le booléen pause passe à vrai
    pause = true;

    //on stoppe l'horloge
    _timer->stop();

}

//==============================
// Redémarrage du jeu
//==============================

void View::Restart()
{
        // On réaffecte leur ancienne vitesse à tous les obstacles
        for (MovableElement * m : _model->get_element())
        {
            m->setdx(savespeed);

        }

        // On réaffecte leur ancienne vitesse à tous les bonus
        for (Bonus * n : _model->get_elementbonus())
        {
            n->setdx(savespeed);
        }

        // On réaffecte leur ancienne vitesse aux fonds d'écran
        _backgroundSprite->setSpeed(savespeedback2);
        _backgroundSprite2->setSpeed(-savespeed);

        // le booléen pause passe à faux
        pause = false;
}

//====================================
// Création des rectangles de lecture
//====================================
void View::RectangleLecture(std::vector<sf::IntRect> &rectanglesDeLecture)
{
    //on le premier rectangle de lecture dans le vector de IntRec ( pour l'animation )
    rectanglesDeLecture.push_back(sf::IntRect(0,276, 200, 245));

    // on les insère un par un dans le vector de IntRec
    for(int i = 1 ; i < 18 ; ++i)
    {
        rectanglesDeLecture.push_back(sf::IntRect(i*205,276, 201, 240));
    }
}
//=====================
//=====================
// SCORES
//=====================
//=====================

//=========================================
// Enregistrement du score dans un fichier
//=========================================

string View::Lecturescore()
{

    ifstream fichier("score.txt", ios::in);  // on ouvre en lecture
    std::string texteentier;
    if(fichier)  // si l'ouverture a fonctionné
    {
        std::vector <int> intvec ;

        string contenu;  // déclaration d'une chaîne qui contiendra la ligne lue

            while (getline(fichier, contenu))
            {
                // on met dans "contenu" la ligne
            intvec.push_back(stoi(contenu));

            }

            std::sort (intvec.begin(), intvec.end());
            std::reverse(intvec.begin(),intvec.end());


            for (int i=0 ; i < 10 ; i++)
            {
                texteentier += to_string(intvec[i]) + "\n";
            }


    }

    fichier.close();
    return texteentier;


}

//=========================================
// Lecture ligne par ligne du fichier score
//=========================================

string View::Lireligne(int numligne, string fichiername)
{
    ifstream fichier(fichiername , ios::in);  // on ouvre en lecture

    if(fichier)  // si l'ouverture a fonctionné
    {
        string contenu;  // déclaration d'une chaîne qui contiendra la ligne lue

        //Pour toutes les lignes du fichier score :
        for (int i = 0; i< numligne ; i ++)
        {
            getline(fichier, contenu);  // on met dans "contenu" la ligne
        }

        // fermeture du fichier
        fichier.close();

        // retourne le contenu de la ligne
        return contenu;
    }

    // message d'erreur en cas de problème
    else
    {
        cerr << "Impossible d'ouvrir le fichier !" << endl;
        return "0";
    }
}


/****************** Nom de la fonction **********************
 View
******************** Auteur , Dates *************************
* Nom/Date :
********************* Description ***************************
* C'est le connstructucteur de view
* Il initialise l'affichage
*********************** Entrées *****************************
* deux entier : largeur et hauteur de la fenêtre
*********************** Sorties *****************************

************************************************************/

//=====================
//=====================
// CONSTRUCTEUR
//=====================
//=====================

View::View(int w, int h)
    : _w(w),_h(h)
{
    _menu = 5;// initialisation du menu à 5
    cpt = 0;// initialisation

    //=====================
    // Paramêtrage
    //=====================

    // création de la fenêtre de jeu
    _window = new sf::RenderWindow(sf::VideoMode(w, h, 32), "Runner", sf::Style::Close);    //RerderWindow ouvre une nouvelle fenetre de largeur w et hauteur h de titre "Runner"

    // limite le nombre d'image
    _window->setFramerateLimit(40);

    // Si le fichier image n'est pas chargé
    if (!_background.loadFromFile(BACKGROUND_IMAGE)) {
        std::cerr << "ERROR when loading image file: " // Message d'erreur
                  << BACKGROUND_IMAGE << std::endl;    // indiquant qu'il ne trouve pas le fichier
        exit(EXIT_FAILURE); // Sortie erreur
    }

    // si le fichier image est chargé
    else {

        // création du fond d'écran
        _backgroundSprite = new SlidingBackground (_background , _background.getSize().x , _background.getSize().y , 3);


    }

    // Si le fichier image n'est pas chargé
    if (!_balletext.loadFromFile(BLUEROBOT)) {

        std::cerr << "ERROR when loading image file: " // Message d'erreur
                  << BLUEROBOT << std::endl;    // indiquant qu'il ne trouve pas le fichier
        exit(EXIT_FAILURE); // Sortie erreur
    }

    // Si le fichier image est chargé
    else {

        vector <sf::IntRect> rectanglesDeLecture;// déclaration d'un vecteur de rectangles de lecture
        RectangleLecture(rectanglesDeLecture);// remplissage du vecteur des rectangles de lecture

        _balle = new AnimatedGraphicElement(rectanglesDeLecture,_balletext,100,400,1400,175); // création de la balle

    }

    // Si le fichier image n'est pas chargé
    if (!_fonttimetext.loadFromFile(TIME_FONT)) {

        std::cerr << "ERROR when loading image file: " // Message d'erreur
                  << TIME_FONT << std::endl;    // indiquant qu'il ne trouve pas le fichier
        exit(EXIT_FAILURE); // Sortie erreur
    }

    // Si le fichier image est chargé
    else {

        _timer = new StopWatch;// création de la montre
        _timetext.setCharacterSize(50);// taille du texte affichant le temps
        _timetext.setFont(_fonttimetext);// Font du texte affichant le temps
        _timetext.setColor(sf::Color::Black);// Couleur du texte affichant le temps
        _timetext.setPosition(285,-10);// Position du texte affichant le temps

        // définition des paramêtres d'affichage du score
        _scorego.setCharacterSize(50);
        _scorego.setFont(_fonttimetext);
        _scorego.setColor(sf::Color::White);
        _scorego.setPosition(300,300);

        // définition des paramêtres d'affichage du volume
        _voltext.setCharacterSize(50);
        _voltext.setFont(_fonttimetext);
        _voltext.setColor(sf::Color::Black);
        _voltext.setPosition(300,200);

        nivolume= sound.getVolume();// affectation du volume sonore à la variable
        textvolume = to_string(nivolume); // affecte le numéro du volume dans la variable
        _voltext.setString(textvolume);

        // paramêtrage de l'affichage du score des pièces
        coinecrit.setCharacterSize(30);
        coinecrit.setFont(_fonttimetext);
        coinecrit.setColor(sf::Color::Black);
        coinecrit.setPosition(500,500);

    }

    // si il y a un problème avec la musique
    if(!buffer.loadFromFile(MUSICNAME))
    {
        std::cerr << "ERROR when loading image file: " // Message d'erreur
                  << MUSICNAME << std::endl;    // indiquant qu'il ne trouve pas le fichier
        exit(EXIT_FAILURE); // Sortie erreur
    }

    //Si il n'y a pas d'erreur
    else
    {
        // paramêtrage du son
        sound.setVolume(100);
        sound.setBuffer(buffer);
        sound.setLoop(true);
        volume = false;
        if (volume)
        {
            sound.play();
        }

    }
    //=====================
    // Menu
    //=====================

    if (!_buttonplaytext.loadFromFile(BUTTON)) { // Si le fichier image des boutons n'est pas chargé
        std::cerr << "ERROR when loading image file: " // Message d'erreur
                  << BUTTON << std::endl;    // indiquant qu'il ne trouve pas le fichier
        exit(EXIT_FAILURE); // Sortie erreur
    }

    // Sinon création des 4 boutons du menu (play, paramêtres, scores, quit)
    else {

        _buttonplaysprite = new GraphicElement(_buttonplaytext,285,150,250,75);

        _buttonparasprite = new GraphicElement(_buttonplaytext,285,250,250,75);

        _buttonscoresprite = new GraphicElement(_buttonplaytext,285,350,250,75);

        _buttonquitsprite = new GraphicElement(_buttonplaytext,285,450,250,75);
    }

    //Ajouter font du menu
    if (!_fontplaytext.loadFromFile(TEXTFONT)) { // Si le fichier image n'est pas chargé
        std::cerr << "ERROR when loading image file: " // Message d'erreur
                  << TEXTFONT << std::endl;    // indiquant qu'il ne trouve pas le fichier
        exit(EXIT_FAILURE); // Sortie erreur
    }
    else {
        //JOUER
        _playtext.setCharacterSize(40);
        _playtext.setFont(_fontplaytext);
        _playtext.setColor(sf::Color::Black);
        _playtext.setPosition(360, 160);

        //PARAMETRE
        _paratext.setCharacterSize(40);
        _paratext.setFont(_fontplaytext);
        _paratext.setColor(sf::Color::Black);
        _paratext.setPosition(320, 265);

        _paratextpara.setCharacterSize(50);
        _paratextpara.setFont(_fontplaytext);
        _paratextpara.setColor(sf::Color::Black);
        _paratextpara.setPosition(310, 75);

        //SCORE
        _scoretext.setCharacterSize(40);
        _scoretext.setFont(_fontplaytext);
        _scoretext.setColor(sf::Color::Black);
        _scoretext.setPosition(350, 360);
        _scoretext.setString("SCORES");

        _scorescorescore.setCharacterSize(30);
        _scorescorescore.setFont(_fontplaytext);
        _scorescorescore.setColor(sf::Color::Black);
        _scorescorescore.setPosition(300,175);
        _scorescorescore.setString(Lecturescore());

        _scoretitle.setCharacterSize(50);
        _scoretitle.setFont(_fontplaytext);
        _scoretitle.setColor(sf::Color::Black);
        _scoretitle.setPosition(300,100);
        _scoretitle.setString("SCORES");

        // QUITTER
        _quittext.setCharacterSize(40);
        _quittext.setFont(_fontplaytext);
        _quittext.setColor(sf::Color::Black);
        _quittext.setPosition(355,460);

        // RETOUR
        _backecrit.setCharacterSize(30);
        _backecrit.setFont(_fontplaytext);
        _backecrit.setColor(sf::Color::Black);
        _backecrit.setPosition(377, 507);

        _backmenuecrit.setCharacterSize(40);
        _backmenuecrit.setFont(_fontplaytext);
        _backmenuecrit.setColor(sf::Color::Black);
        _backmenuecrit.setPosition(137, 400);
        _backmenuecrit.setString("MENU");

        // FIN DU JEU
        _gameovertext.setCharacterSize(150);
        _gameovertext.setFont(_fontplaytext);
        _gameovertext.setColor(sf::Color::Black);
        _gameovertext.setPosition(25, 25);
        _gameovertext.setString("FIN  DU  JEU");

        //REJOUER
        _restarttext.setCharacterSize(40);
        _restarttext.setFont(_fontplaytext);
        _restarttext.setColor(sf::Color::Black);
        _restarttext.setPosition(355, 500);


        // LANGUE
        _Language.setCharacterSize(50);
        _Language.setFont(_fontplaytext);
        _Language.setColor(sf::Color::Black);
        _Language.setPosition(50,300);

        // QUITTER PAUSE
        _quitpause.setCharacterSize(40);
        _quitpause.setFont(_fontplaytext);
        _quitpause.setColor(sf::Color::Black);
        _quitpause.setPosition(347,202);

    }


    if (!_menusdecotext.loadFromFile(DECOMENUS))
    {
        // Si le fond du menu n'est pas chargé
        std::cerr << "ERROR when loading image file: " // Message d'erreur
                  << DECOMENUS << std::endl;    // indiquant qu'il ne trouve pas le fichier
        exit(EXIT_FAILURE); // Sortie erreur
    }

    // Sinon on crée le fond du menu
    else
    {

        _menudeco = new GraphicElement(_menusdecotext,10,10,775,575);
    }


    if (!_iconevolume.loadFromFile(VOLUME))
    {
       // Si le fichier image du volume n'est pas chargé
        std::cerr << "ERROR when loading image file: " // Message d'erreur
                  << VOLUME << std::endl;    // indiquant qu'il ne trouve pas le fichier
        exit(EXIT_FAILURE); // Sortie erreur
    }

    // Sinon on crée l'icone volume
    else
    {
        _Volspr = new GraphicElement(_iconevolume,100,200,50,50);
    }


    if (!_backtext.loadFromFile(BUTTONBACK)) { // Si le fichier image du bonton quitter n'est pas chargé
        std::cerr << "ERROR when loading image file: " // Message d'erreur
                  << BUTTONBACK << std::endl;    // indiquant qu'il ne trouve pas le fichier
        exit(EXIT_FAILURE); // Sortie erreur
    }

    // Sinon création des boutons quitter
    else
    {
        _back = new GraphicElement(_backtext,340,500,150,50);
        _backmenu = new GraphicElement (_backtext,100,400,150,50);
        buttonpausequit = new GraphicElement (_backtext ,330,200,150,50);
    }


    if (!_crosstext.loadFromFile(CROIX)) { // Si le fichier image n'est pas chargé
        std::cerr << "ERROR when loading image file: " // Message d'erreur
                  << CROIX << std::endl;    // indiquant qu'il ne trouve pas le fichier
        exit(EXIT_FAILURE); // Sortie erreur
    }

    // Sinon création de la croix
    else {

        _cross = new GraphicElement(_crosstext,100,200,50,50);
    }


    if (!_upvtext.loadFromFile(PLUSVOLUME)) { // Si le fichier image n'est pas chargé
        std::cerr << "ERROR when loading image file: " // Message d'erreur
                  << PLUSVOLUME << std::endl;    // indiquant qu'il ne trouve pas le fichier
        exit(EXIT_FAILURE); // Sortie erreur
    }

    // Sinon création du plus
    else {

        _upvol = new GraphicElement(_upvtext,200,200,30,25);
    }


    if (!_downvtext.loadFromFile(MOINSVOLUME)) { // Si le fichier image n'est pas chargé
        std::cerr << "ERROR when loading image file: " // Message d'erreur
                  << MOINSVOLUME << std::endl;    // indiquant qu'il ne trouve pas le fichier
        exit(EXIT_FAILURE); // Sortie erreur
    }

    // Sinon création du moins
    else {

        _downvol = new GraphicElement(_downvtext,200,230,30,25);
    }

    if (!_cointext.loadFromFile(COIN))
    { // Si le fichier image n'est pas chargé
        std::cerr << "ERROR when loading image file: " // Message d'erreur
                  <<  COIN << std::endl;    // indiquant qu'il ne trouve pas le fichier
        exit(EXIT_FAILURE); // Sortie erreur
    }

    // création des pièces
    else
    {
        _coin = new GraphicElement(_cointext,700,400,25,25);
    }

    if (!_lifetext.loadFromFile(LIFE))
    { // Si le fichier image n'est pas chargé
        std::cerr << "ERROR when loading image file: " // Message d'erreur
                  <<  LIFE << std::endl;    // indiquant qu'il ne trouve pas le fichier
        exit(EXIT_FAILURE); // Sortie erreur
    }

    // création des vies
    else
    {
        _life = new GraphicElement(_lifetext,700,400,25,25);
    }


    if (!_mechanttext.loadFromFile(MECHANT1)) { // Si le fichier image n'est pas chargé
        std::cerr << "ERROR when loading image file: " // Message d'erreur
                  << MECHANT1 << std::endl;    // indiquant qu'il ne trouve pas le fichier
        exit(EXIT_FAILURE); // Sortie erreur
    }

    // création obstacles verts
    else {

        _mechant = new GraphicElement(_mechanttext,700,400,50,50);
        _mechantGO =  new GraphicElement(_mechanttext,650,75,100,100);
        _mechantpause = new GraphicElement ( _mechanttext , 355 , 300 , 100 , 100 );

    }


    if (!_barrevietexture.loadFromFile(BARRE_VIE)) { // Si le fichier image n'est pas chargé
        std::cerr << "ERROR when loading image file: " // Message d'erreur
                  << BARRE_VIE << std::endl;    // indiquant qu'il ne trouve pas le fichier
        exit(EXIT_FAILURE); // Sortie erreur
    }

    // création barre de vie
    else {

        _barrevie = new GraphicElement(_barrevietexture,10,495,415,60);

    }


    if (!_background2.loadFromFile(BACKGROUND_IMAGE2)) { // Si le fichier image n'est pas chargé
        std::cerr << "ERROR when loading image file: " // Message d'erreur
                  << BACKGROUND_IMAGE2 << std::endl;    // indiquant qu'il ne trouve pas le fichier
        exit(EXIT_FAILURE); // Sortie erreur
    }

    // création fond d'écran
    else {


        _backgroundSprite2 = new SlidingBackground (_background2 , _background2.getSize().x, _background2.getSize().y , 5);
    }

    if (!_pictext.loadFromFile(PICS)) { // Si le fichier image n'est pas chargé
        std::cerr << "ERROR when loading image file: " // Message d'erreur
                  << PICS << std::endl;    // indiquant qu'il ne trouve pas le fichier
        exit(EXIT_FAILURE); // Sortie erreur
    }

    // création obstacle en pics
    else {

        _pic = new GraphicElement(_pictext,700,400,50,50);


    }


    if (!_titlefont.loadFromFile(FONTBLOCKTITLE)) { // Si le fichier image n'_playtext.setPosition(370, 160);est pas chargé
        std::cerr << "ERROR when loading image file: " // Message d'erreur
                  << PICS << std::endl;    // indiquant qu'il ne trouve pas le fichier
        exit(EXIT_FAILURE); // Sortie erreur
    }

    // création du titre dans le menu
    else {

        _titletitle.setCharacterSize(100);
        _titletitle.setFont(_titlefont);
        _titletitle.setColor(sf::Color::Green);
        _titletitle.setPosition(100,25);
        _titletitle.setString("NEON CITY");


    }

    // gestion des langues
    if (!anglaistexture.loadFromFile(ANGLAISIMAGE)) { // Si le fichier image n'est pas chargé
        std::cerr << "ERROR when loading image file: " // Message d'erreur
                  << ANGLAISIMAGE << std::endl;    // indiquant qu'il ne trouve pas le fichier
        exit(EXIT_FAILURE); //
    }


    else
    {

        angl = new GraphicElement(anglaistexture,300,300,50,50);


    }


    if (!francaistexture.loadFromFile(FRANCAISIMAGE)) { // Si le fichier image n'est pas chargé
        std::cerr << "ERROR when loading image file: " // Message d'erreur
                  << FRANCAISIMAGE << std::endl;    // indiquant qu'il ne trouve pas le fichier
        exit(EXIT_FAILURE); // Sortie erreur
    }

    else
    {

        france = new GraphicElement(francaistexture,400,300,50,50);


    }

    // pause
    if (!_pausetexture.loadFromFile(PAUSEIMAGE))
    { // Si le fichier image n'est pas chargé
        std::cerr << "ERROR when loading image file: " // Message d'erreur
                  <<  PAUSEIMAGE << std::endl;    // indiquant qu'il ne trouve pas le fichier
        exit(EXIT_FAILURE); // Sortie erreur
    }


    else
    {
        _pause = new GraphicElement(_pausetexture,100,100,600,350);
    }

    // logo iut
    if (!_iuttext.loadFromFile(IUTBORD))
    { // Si le fichier image n'est pas chargé
        std::cerr << "ERROR when loading image file: " // Message d'erreur
                  <<  IUTBORD << std::endl;    // indiquant qu'il ne trouve pas le fichier
        exit(EXIT_FAILURE); // Sortie erreur
    }

    else
    {
        _iutbordeaux = new GraphicElement(_iuttext,75,200,200,200);
    }

    // logo sfml
    if (!_sfmltext.loadFromFile(SFML))
    { // Si le fichier image n'est pas chargé
        std::cerr << "ERROR when loading image file: " // Message d'erreur
                  <<  SFML << std::endl;    // indiquant qu'il ne trouve pas le fichier
        exit(EXIT_FAILURE); // Sortie erreur
    }

    else
    {
        _sfml = new GraphicElement(_sfmltext,375,225,400,150);
    }


    // initialisation des booléens
    francais = true;
    pause = false;

    //
    probl = 60;
    problb = 50;

    // création de la montre et son démarrage
    _timerintro = new StopWatch ;
    _timerintro->start();

    //=====================
    // Obstacles
    //=====================

    if (!_obstacletext.loadFromFile(OBSTACLEIMAGE))

    { // Si le fichier image des obstacle n'est pas chargé
        std::cerr << "ERROR when loading image file: " // Message d'erreur
                  << OBSTACLEIMAGE << std::endl;    // indiquant qu'il ne trouve pas le fichier
        exit(EXIT_FAILURE); // Sortie erreur
    }

    // Sinon création d'un obstacle
    else
    {
        _obstacle = new GraphicElement(_obstacletext,700,400,50,50);

    }
}

//==========================
// Suppression des éléments
//==========================

View::~View(){
    if (_timer != NULL)
    {
        delete _timer;
    }
    if (_timerintro != NULL)
    {
        delete _timerintro;
    }
    if (_balle != NULL)
    {
        delete _balle;
    }
    if (_buttonplaysprite != NULL)
    {
        delete _buttonplaysprite;
    }
    if (_buttonparasprite != NULL)
    {
        delete _buttonparasprite;
    }
    if (_buttonscoresprite != NULL)
    {
        delete _buttonscoresprite;
    }
    if (_buttonquitsprite != NULL)
    {
        delete _buttonquitsprite;
    }
    if (_back != NULL)
    {
        delete _back;
    }
    if (_Volspr != NULL)
    {
        delete _Volspr;
    }
    if (_cross != NULL)
    {
        delete _cross;
    }
    if (_menudeco != NULL)
    {
        delete _menudeco;
    }
    if (_downvol != NULL)
    {
        delete _downvol;
    }
    if (_upvol != NULL)
    {
        delete _upvol;
    }
    if (buttonpausequit != NULL)
    {
        delete buttonpausequit;
    }
    if (_restart != NULL)
    {
        delete _restart;
    }
    if (_backmenu != NULL)
    {
        delete _backmenu;
    }
    if (_pause != NULL)
    {
        delete _pause;
    }
    if (_mechant != NULL)
    {
        delete _mechant;
    }
    if (_mechantGO != NULL)
    {
        delete _mechantGO;
    }
    if (_mechantpause != NULL)
    {
        delete _mechantpause;
    }
    if (angl != NULL)
    {
        delete angl;
    }
    if (france != NULL)
    {
        delete france;
    }
    if (_obstacle != NULL)
    {
        delete _obstacle;
    }
    if (_pic != NULL)
    {
        delete _pic;
    }
    if (_coin != NULL)
    {
        delete _coin;
    }
    if (_life != NULL)
    {
        delete _life;
    }
    if (_barrevie != NULL)
    {
        delete _barrevie;
    }
    if (_sfml != NULL)
    {
        delete _sfml;
    }
    if (_iutbordeaux != NULL)
    {
        delete _iutbordeaux;
    }

    if(_window!= NULL) // Si la fenetre est presente
    {
        delete _window;// On la désalloue
    }
}

//=====================
// Accés à un modèle
//=====================

void View::setModel(Model * model)
{
    _model = model; // définit _model
}

//===========================
// Dessine tout les éléments
//===========================
void View::draw(){


    // Si l'on souhaite jouer en français : affectation de tout les paramêtres en langue française
    if (francais)
    {
       _playtext.setPosition(360, 160);
       _playtext.setString(Lireligne(1,FICHIERFRANCAIS));
       _paratext.setPosition(320, 265);
       _paratext.setString(Lireligne(2,FICHIERFRANCAIS));
       _paratextpara.setString(Lireligne(2,FICHIERFRANCAIS));
       _backecrit.setPosition(377, 507);
       _backecrit.setString(Lireligne(3,FICHIERFRANCAIS));
       _gameovertext.setString(Lireligne(4,FICHIERFRANCAIS));
       _restarttext.setPosition(355, 500);
       _restarttext.setString(Lireligne(5,FICHIERFRANCAIS));
       _Language.setString(Lireligne(6,FICHIERFRANCAIS));
       _quitpause.setPosition(347,202);
       _quitpause.setString(Lireligne(8,FICHIERFRANCAIS));
       _quittext.setPosition(355,460);
       _quittext.setString(Lireligne(8,FICHIERFRANCAIS));


    }

    // Si l'on souhaite jouer en Anglais : affectation de tout les paramêtres en langue anglaise ( mot en anglais)
    else
    {
        _playtext.setString(Lireligne(1,FICHIERANGLAIS));
        _playtext.setPosition(370, 160);
        _paratext.setString(Lireligne(2,FICHIERANGLAIS));
        _paratext.setPosition(340, 265);
        _paratextpara.setString(Lireligne(2,FICHIERANGLAIS));
        _backecrit.setPosition(387, 507);
        _backecrit.setString(Lireligne(3,FICHIERANGLAIS));
        _gameovertext.setString(Lireligne(4,FICHIERANGLAIS));
        _restarttext.setPosition(365, 500);
        _restarttext.setString(Lireligne(5,FICHIERANGLAIS));
        _Language.setString(Lireligne(6,FICHIERANGLAIS));
        _quitpause.setPosition(375,202);
        _quitpause.setString(Lireligne(8,FICHIERANGLAIS));
        _quittext.setPosition(375,460);
        _quittext.setString(Lireligne(8,FICHIERANGLAIS));

    }

    // affichage de la fenêtre du menu basique
    if (_menu == 0)
    {   _window->clear(sf::Color::Blue); // On "nettoie" la fenetre
        _window->draw(_titletitle);
        _buttonplaysprite->draw(_window);
        _buttonparasprite->draw(_window);
        _buttonscoresprite->draw(_window);
        _buttonquitsprite->draw(_window);
        _window->draw(_playtext);
        _window->draw(_paratext);
        _window->draw(_scoretext);
        _window->draw(_quittext);
    }

    // affichage de la fenêtre de jeu
    if (_menu == 1)
    {
        _window->clear();
        _backgroundSprite->draw(_window);
        _backgroundSprite2->draw(_window);

        // affichage des obstacles
        for(MovableElement*m : _model ->get_element())
        {
            if (m->getid() == 0)
            {
                _obstacle->draw(_window,sf::Vector2f(m->getx(),m->gety()));
            }
            if (m->getid() == 1)
            {
                _mechant->draw(_window,sf::Vector2f(m->getx(),m->gety()));

            }
            if (m->getid() == 2)
            {
                _pic->draw(_window,sf::Vector2f(m->getx(),m->gety()));
            }

        }

        // affichages des bonus
        for(Bonus*n : _model->get_elementbonus())
        {
            if ( n->getid() == 0)
            {
                _coin->draw(_window,sf::Vector2f(n->getx(),n->gety()));
            }
            if ( n->getid() == 1)
            {
                _life->draw(_window,sf::Vector2f(n->getx(),n->gety()));
            }

        }

        // tant que l'on est pas en pause
        if (!pause)
        {
            _balle->setNextcurrentcliprect();// avancement de la balle
        }

        // dessine la balle
        _balle->draw(_window);

        // dessine score et pièces
        _window->draw(_timetext);
        _window->draw(coinecrit);

        // initialisation de la position du premier rectangle de vie dans la barre de vie
        xbarredevie = 25;

        // dessin de tout les rectangles de vie
        for ( int i = 1; i <= (_model->getpointdevieballe()/10 ); i++)
        {

            _window->draw(rectangle);
            rectangle.setSize(sf::Vector2f(25, 50));
            rectangle.setFillColor(sf::Color (0,255,0));
            rectangle.setPosition(sf::Vector2f(xbarredevie, 500));

            xbarredevie += 30;// décalage de position


            // changement de couleur des rectangles de vie en fonction du nombre de vie perdu
            if ( (_model->getpointdevieballe()/10 ) <= 5 && (_model->getpointdevieballe()/10 ) > 2)
            {
                rectangle.setFillColor(sf::Color (237, 127, 16));
            }

            if ((_model->getpointdevieballe()/10 ) <= 2)
            {
               rectangle.setFillColor(sf::Color (255, 0, 0));
            }

       }

        // dessin barre de vie
        _barrevie->draw(_window);


        // affichage de la fenêtre de pause
        if(pause)
        {

            _pause->draw(_window);
            buttonpausequit->draw(_window);
            _window->draw(_quitpause);
            _mechantpause->draw(_window);
        }

    }

    // affichage de la fenêtre paramêtres
    if (_menu == 2)
    {

        _window->clear(sf::Color::Blue); // On "nettoie" la fenetre
        _menudeco->draw(_window);
        _window->draw(_paratextpara);
        _Volspr->draw(_window);
        _back->draw(_window);
        _window->draw(_backecrit);
        _upvol->draw(_window);
        _downvol->draw(_window);
        _window->draw(_voltext);
        angl->draw(_window);
        france->draw(_window);
        _window->draw(_Language);
        if (!volume)
        {
            _cross->draw(_window);

            sound.stop();
        }
    }

    // Affichage de la fenêtre lorque l'on perd une partie
    if ( _menu == 3)
    {
        _window->clear(sf::Color::Blue);
        _window->draw(_gameovertext);
        _back->draw(_window);
        _backmenu->draw(_window);
        _window->draw(_backmenuecrit);
        _window->draw(_restarttext);
        _window->draw(_scorego);
        _mechantGO->draw(_window);
    }

    // Affichage de la fenêtre scores
    if ( _menu == 4)
    {
        _window->clear(sf::Color::Blue);
        _menudeco->draw(_window);
        _window->draw(_scoretitle);
        _window->draw(_scorescorescore);
        _back->draw(_window);
        _window->draw(_backecrit);
    }

    // Affichage de la fenêtre d'introduction
    if ( _menu == 5)
    {
        _window->clear(sf::Color::Blue);
        _iutbordeaux->draw(_window);
        _sfml->draw(_window);

    }

    //affichage de la fenêtre
    _window->display();

}

//====================================================================================
// Appelle les fonction de de mise à jour des position des différents éléments du jeu
//====================================================================================

void View::syncronize()
{

    if (_menu == 1)
    {
        _model->getBallPostion(_x,_y);
        _model->Collision();
        _model->CollisionBonus();
        _balle->setPosition(sf::Vector2f(_x,_y));
        _model->Evolutionjump();
    }

}

//=====================================================================================================================
// On met le traitement des evenement et on renvoie un booleen qui indique si l'application est ouverte ou non
//=====================================================================================================================

bool View::treatEvents(){

    l = rand()%probl ;
    lb = rand()%problb;
    bool result = false;    // booleen result à false

    coinnbr = _model->getnbpiece();

    coinstring = to_string(coinnbr);
    if (francais)
    {
        coinecrit.setString(Lireligne(7,FICHIERFRANCAIS)+" "+coinstring);
    }
    else
    {
        coinecrit.setString(Lireligne(7,FICHIERANGLAIS)+" "+ coinstring);
    }

    if (_menu == 5)
    {
        int timeintro = _timerintro->getElapsedTime().asSeconds();
        if (timeintro == 2)
        {

            _menu = 0;
            _timerintro->stop();
        }

    }


    sf::Vector2i localPosition = sf::Mouse::getPosition(*_window); // window est un sf::Window

    if(_window->isOpen()){ // Si la fenetre est ouverte
        result = true;  // On passe le booleen a true

        if (_menu == 1)
        {

            // traitement des évènements en attente
            if (!pause)
            {
            _timer->start();
            int realsec = _timer->getElapsedTime().asSeconds();
            int sec = _timer->getElapsedTime().asMilliseconds();
            int milli = _timer->getElapsedTime().asMicroseconds();
            int score =  sec/600 ;// Récupération du temps en secondes
            tps = to_string(score);
            _timetext.setString("SCORE : " + tps);


            if (milli%probl == l)
            {

             _model->AjouterObstacle();

            }

            if (milli%problb == lb)
            {
                _model->AjouterBonus();
            }

            if ( realsec%30 == 0 && realsec != 0)
            {
            if (cpt < 1)
            {
            _model->changeinitspeed(_model->getinitspeed() - 1);


            for (MovableElement * m : _model->get_element())
            {
                _model->setspeedobstacle(m,m->getdx() - 1);
            }

            for (Bonus * b : _model->get_elementbonus())
            {
                _model->setspeedbonus(b,b->getdx() - 1);
            }
            _backgroundSprite->setSpeed(_backgroundSprite->getspeed() + 1);
            _backgroundSprite2->setSpeed(_backgroundSprite2->getspeed() + 1);
            probl-= 10;
            problb += 10;
            cpt++;
            }
            }
             if ( realsec%30 == 1 && realsec != 0)
             {
                 cpt = 0;
             }
            }


            cout << _model->getinitspeed() << endl;


        }


        // GAME OVER
        if (_model->getpointdevieballe() == 0 )
        {
            _menu = 3;
            _timer->stop();
            _scorego.setString("SCORE : " + tps);
            _model->resetsetelement();
            _model->resetsetelementbonus();
            if ( cptscore < 1)
            {
                ofstream fichier("score.txt", ios::out | ios::app);  // ouverture en écriture avec effacement du fichier ouvert

                if(fichier)
                {

                        fichier << tps << endl;
                        fichier.close();
                }
                else
                {
                        cerr << "Impossible d'ouvrir le fichier !" << endl;
                }
                _scorescorescore.setString(Lecturescore());
                cptscore++;
            }


        }

        sf::Event event;

        while (_window->pollEvent(event)) {   // Tant que l'on peut réaliser des évènements
            //cout << "Event detected" << endl; // On ecrit "Event detected"

            if ((event.type == sf::Event::Closed) || // Si on ferme le programme ( la croix en haut de la fenetre )
                    ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
            {
                // ou si on appuie sur Echap
                // Si dans le jeu
                if (_menu == 1)
                {
                    // on efface tous les _elements du jeu ( obstacle bonus )
                    _model->resetsetelement();
                    _model->resetsetelementbonus();
                }

                result = false;// et on met le booleen result à false
                 _window->close();// la fenetre se ferme




            }

            // PAGE MENU PRINCIPAL
            if (_menu == 0)
            {

                if (localPosition.x > 285 && localPosition.x < 535 && localPosition.y > 150 && localPosition.y < 225)
                {
                    _buttonplaysprite->setColor(sf::Color(126,126,126));
                }
                else
                {
                    _buttonplaysprite->setColor(sf::Color(255,255,255));
                }

                if (localPosition.x > 285 && localPosition.x < 535 && localPosition.y > 250 && localPosition.y < 325)
                {
                    _buttonparasprite->setColor(sf::Color(126,126,126));
                }
                else
                {
                    _buttonparasprite->setColor(sf::Color(255,255,255));
                }

                if (localPosition.x > 285 && localPosition.x < 535 && localPosition.y > 350 && localPosition.y < 425)
                {
                    _buttonscoresprite->setColor(sf::Color(126,126,126));
                }
                else
                {
                    _buttonscoresprite->setColor(sf::Color(255,255,255));
                }

                if (localPosition.x > 285 && localPosition.x < 535 && localPosition.y > 450 && localPosition.y < 525)
                {
                    _buttonquitsprite->setColor(sf::Color(126,126,126));
                }
                else
                {
                    _buttonquitsprite->setColor(sf::Color(255,255,255));
                }
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    switch(event.key.code)
                    {
                    case sf::Mouse::Button::Left:
                        if (localPosition.x > 285 && localPosition.x < 535 && localPosition.y > 150 && localPosition.y < 225)
                        {
                            _menu = 1;
                            _model->restart();
                            _timer->restart();
                            _model->changeinitspeed(-5);
                            _model->setspeedbackground(_backgroundSprite,3);
                            _model->setspeedbackground(_backgroundSprite2,5);
                            cptscore = 0;
                            probl = 60;
                            problb = 50;

                            _buttonplaysprite->setColor(sf::Color(255,255,255));
                        }

                        if (localPosition.x > 285 && localPosition.x < 535 && localPosition.y > 250 && localPosition.y < 325)
                        {
                            _menu = 2;
                            _buttonparasprite->setColor(sf::Color(255,255,255));
                        }
                        if (localPosition.x > 285 && localPosition.x < 535 && localPosition.y > 350 && localPosition.y < 425)
                        {
                            _menu = 4;
                            _buttonscoresprite->setColor(sf::Color(255,255,255));
                        }
                        if (localPosition.x > 285 && localPosition.x < 535 && localPosition.y > 450 && localPosition.y < 525)
                        {
                            result = false;// et on met le booleen result à false
                            _window->close();// la fenetre se ferme
                        }

                        break;
                    default:
                        break;
                    }
                }
            }
            // PAGE JEU
            else if (_menu == 1)
            {
                if  (pause)
                {
                    //330,200,150,50
                    if (localPosition.x > 330 && localPosition.x < 480 && localPosition.y > 200 && localPosition.y < 250)
                    {
                        buttonpausequit->setColor(sf::Color(126,126,126));
                    }
                    else
                    {
                        buttonpausequit->setColor(sf::Color(255,255,255));
                    }

                    if (event.type == sf::Event::KeyPressed)
                    {
                        switch(event.key.code)
                        {
                           case sf::Keyboard::Space:
                            Restart();
                            break;
                        default:
                            break;
                        }
                    }

                    if (event.type == sf::Event::MouseButtonPressed)

                    {
                        switch(event.key.code)
                        {

                        case sf::Mouse::Button::Left:
                            if (localPosition.x > 330 && localPosition.x < 480 && localPosition.y > 200 && localPosition.y < 250)
                            {
                                pause = false;
                                _model->setpointvieballe(100);
                                _model->stopballx();
                                _menu = 0;
                                buttonpausequit->setColor(sf::Color(255,255,255));
                                _model->resetsetelement();
                                _model->resetsetelementbonus();
                            }
                            break;
                        default:
                            break;
                        }
                }
                }
                else
                {
                    if (event.type == sf::Event::KeyPressed)
                    {
                        switch(event.key.code)
                        {
                        case sf::Keyboard::Left :
                            _model->moveBAll(true);
                            break;
                        case sf::Keyboard::Right:
                            _model->moveBAll(false);
                            break;
                        case sf::Keyboard::Up:
                            _model->startjump();
                            break;
                        case sf::Keyboard::Space:
                            if (!pause )
                            {
                                Pause();
                            }
                            break;
                        default:
                            break;
                        }

                    }
                    if (event.type == sf::Event::KeyReleased)

                    {//_menudeco->draw(_window);
                        switch(event.key.code)
                        {
                        case sf::Keyboard::Left :
                            _model->stopballx();
                            break;
                        case sf::Keyboard::Right:
                            _model->stopballx();
                            break;
                        default:
                            break;
                        }
                    }

                }

            }
            //PAGE PARAMETRE
            else if ( _menu == 2 )
            {
                if (localPosition.x > 300 && localPosition.x < 350 && localPosition.y > 300 && localPosition.y < 350)
                {
                    angl->setColor(sf::Color(126,126,126));
                }
                else
                {
                    angl->setColor(sf::Color(255,255,255));
                }
                if (localPosition.x > 400 && localPosition.x < 450 && localPosition.y > 300 && localPosition.y < 350)
                {
                    france->setColor(sf::Color(126,126,126));
                }
                else
                {
                    france->setColor(sf::Color(255,255,255));
                }

                if (localPosition.x > 340 && localPosition.x < 490 && localPosition.y > 500 && localPosition.y < 550)
                {
                    _back->setColor(sf::Color(126,126,126));
                }
                else
                {
                    _back->setColor(sf::Color(255,255,255));
                }

                if (localPosition.x > 200 && localPosition.x < 230 && localPosition.y > 200 && localPosition.y < 225)
                {
                    _upvol->setColor(sf::Color(126,126,126));
                }
                else
                {
                    _upvol->setColor(sf::Color(255,255,255));
                }


                if (localPosition.x > 200 && localPosition.x < 230 && localPosition.y > 230 && localPosition.y < 255)
                {
                    _downvol->setColor(sf::Color(126,126,126));
                }
                else
                {
                    _downvol->setColor(sf::Color(255,255,255));
                }


                if (event.type == sf::Event::MouseButtonPressed)

                {
                    switch(event.key.code)
                    {

                    case sf::Mouse::Button::Left:

                        if (localPosition.x > 340 && localPosition.x < 490 && localPosition.y > 500 && localPosition.y < 550)
                        {
                            _menu = 0;
                            _back->setColor(sf::Color(255,255,255));
                        }
                        if (localPosition.x > 100 && localPosition.x < 150 && localPosition.y > 200 && localPosition.y < 250)
                        {
                            if (volume == true)
                            {
                                volume = false;
                            }

                            else if (volume == false)
                            {
                                volume = true;
                                sound.play();
                            }

                        }
                        if (localPosition.x > 200 && localPosition.x < 230 && localPosition.y > 230 && localPosition.y < 255)
                        {
                            if (sound.getVolume() - 5.00 >= 0 )
                            {
                                sound.setVolume( sound.getVolume() - 5.00);
                                nivolume = sound.getVolume();
                            }
                            else
                            {
                                sound.setVolume(0);
                                nivolume = 0;
                            }


                        }
                        if (localPosition.x > 200 && localPosition.x < 230 && localPosition.y > 200 && localPosition.y < 225)
                        {
                            if (sound.getVolume() + 5.00 <= 100)
                            {
                                sound.setVolume( sound.getVolume() + 5.00 );
                                nivolume = sound.getVolume();
                            }
                            else
                            {

                                sound.setVolume(100);
                                nivolume = 100;
                            }

                        }
                        if (localPosition.x > 300 && localPosition.x < 350 && localPosition.y > 300 && localPosition.y < 350)
                        {
                            francais = false;
                        }

                        if (localPosition.x > 400 && localPosition.x < 450 && localPosition.y > 300 && localPosition.y < 350)
                        {
                            francais = true;
                        }
                        break;
                    default:
                        break;
                    }

                }
                textvolume = to_string(nivolume);
                _voltext.setString(textvolume);
            }

            // PAGE GAME OVER
            if ( _menu == 3 )
            {

                if (localPosition.x > 340 && localPosition.x < 490 && localPosition.y > 500 && localPosition.y < 550)
                {
                    _back->setColor(sf::Color(126,126,126));
                }
                else
                {
                    _back->setColor(sf::Color(255,255,255));
                }
                if (localPosition.x > 100 && localPosition.x < 250 && localPosition.y > 400 && localPosition.y < 450)
                {
                    _backmenu->setColor(sf::Color(126,126,126));
                }
                else
                {
                    _backmenu->setColor(sf::Color(255,255,255));
                }

                if (event.type == sf::Event::MouseButtonPressed)
                {
                    switch(event.key.code)
                    {
                    case sf::Mouse::Button::Left:
                        if (localPosition.x > 100 && localPosition.x < 250 && localPosition.y > 400 && localPosition.y < 450)
                        {

                            _model->setpointvieballe(100);
                            _model->stopballx();
                            _menu = 0;
                            _backmenu->setColor(sf::Color(255,255,255));

                        }
                        if (localPosition.x > 340 && localPosition.x < 490 && localPosition.y > 500 && localPosition.y < 550)
                        {

                            _model->setpointvieballe(100);
                            _model->stopballx();
                            _backmenu->setColor(sf::Color(255,255,255));
                            _model->changeinitspeed(-5);
                            _model->setspeedbackground(_backgroundSprite,3);
                            _model->setspeedbackground(_backgroundSprite2,5);
                            _model->restart();
                            _timer->restart();
                            cptscore = 0;
                            probl = 60;
                            problb = 50;
                            _menu = 1;


                        }
                        break;
                    default:
                        break;
                    }

                }


            }

            //PAGE SCORE
            if ( _menu == 4 )
            {
                if (localPosition.x > 340 && localPosition.x < 490 && localPosition.y > 500 && localPosition.y < 550)
                {
                    _back->setColor(sf::Color(126,126,126));
                }
                else
                {
                    _back->setColor(sf::Color(255,255,255));
                }

                if (event.type == sf::Event::MouseButtonPressed)
                {
                    switch(event.key.code)
                    {
                    case sf::Mouse::Button::Left:
                        if (localPosition.x > 340 && localPosition.x < 490 && localPosition.y > 500 && localPosition.y < 550)
                        {
                            _menu = 0;
                            _back->setColor(sf::Color(255,255,255));
                        }

                        break;
                    default:
                        break;
                    }

                }
            }
        }

    }
    return result;

}
