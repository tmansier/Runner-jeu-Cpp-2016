#ifndef _MODEL_
#define _MODEL_
#include <SFML/Graphics.hpp>
#include <set>
#include "SlidingBackground.h"
#include "Movableelement.h"
#include "Obstacle.h"
#include "Bonus.h"


class Ball;
class Model {
 private:
  int _w, _h; // largeur et hauteur
  Ball * _b; // la balle

  int piece; // nombre de pièces
  int initspeed; // valeur de la vitesse d'un obstacle

  std::set<MovableElement *> _elements; // stockage des obstacles
  std::set<Bonus *> _elementsbonus; // stockage des bonus

  bool superpose; // booléen permettant de savoir si des obstacles se supperposent à des bonus ou autres obstacles
  bool superposebonus; // booléen permettant de savoir si des obstacles ou des bonus se supperposent avec d'autres bonus


 public:

  Model(int w, int h);
  ~Model();
  // Methodes du modele
  void getBallPostion(int & x ,int & y);
  void getObstPostion(int & x ,int & y);
  void nextStep();
  void getballDimension(int & w,int & h);
  void getobstDimension(int & w, int & h);
  void moveBAll(bool left);
  void Evolutionjump();
  void startjump();
  void stopballx();
  sf::Vector2f SetBallPostion();
  void retirerpointvieballe (int ptsperdu);
  void ajouterpointdevieballe(int ptsajout);
  //Methodes pour les tests
  int geth();
  int getw();
  int getpointdevieballe();
  void setpointvieballe(int nb);
  void AjouterObstacle();
  void Collision();
  const std::set<MovableElement *> & get_element() const ;
  void SupprimerObstacle(MovableElement * m);

  void AjouterBonus();
  void CollisionBonus();
  void SupprimerBonus(Bonus *m);
  const std::set<Bonus *> &get_elementbonus() const ;

  int getnbpiece();

  void restart();

  void setspeedobstacle(MovableElement *m, int dx);
  void setspeedbonus(Bonus * b , int dx);
  void setspeedbackground(SlidingBackground *sb, int dx);
  int getinitspeed();
  void changeinitspeed(int dx);
  void resetsetelement();
  void resetsetelementbonus();
};
#endif
