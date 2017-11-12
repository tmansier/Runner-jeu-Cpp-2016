/*#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Balle

#include <boost/test/unit_test.hpp>

#include "Balle.h"

#include"Obstacle.h"
#include"Model.h"

#include <iostream>
#include <SFML/Graphics.hpp>

BOOST_AUTO_TEST_CASE(test_Balle)
{
// Constructeur
Ball b1 {100,400,50,50,0,0,100};
BOOST_CHECK (b1.getx() == 100 );
BOOST_CHECK (b1.gety() == 400 );
BOOST_CHECK (b1.getw() == 50 );
BOOST_CHECK (b1.geth() == 50 );
BOOST_CHECK (b1.getdx() == 0 );
BOOST_CHECK (b1.getdy() == 0 );
BOOST_CHECK (b1.getpointvie() == 100);

// Ajouter / Retirer point de vie
b1.ajouterpointvie(100);
BOOST_CHECK (b1.getpointvie() == 200);
b1.enleverpointvie(100);
BOOST_CHECK (b1.getpointvie() == 100);

// Deplacement
b1.setdx(10);
b1.move();
BOOST_CHECK (b1.getx() == 110);

//Booleen saut
BOOST_CHECK (b1.Isjumping() == false);
b1.setJump(true);
BOOST_CHECK (b1.Isjumping() == true);

}

BOOST_AUTO_TEST_CASE(test_Obstacle)
{
// Constructeur
Obstacle o1{100,400,50,50,0,0};
BOOST_CHECK (o1.getx() == 100 );
BOOST_CHECK (o1.gety() == 400 );
BOOST_CHECK (o1.getw() == 50 );
BOOST_CHECK (o1.geth() == 50 );
BOOST_CHECK (o1.getdx() == 0 );
BOOST_CHECK (o1.getdy() == 0 );

// Deplacement
o1.setdx(10);
o1.move();
BOOST_CHECK (o1.getx() == 110);

o1.setdx(-1000);
o1.move();
bool test2 = o1.out();
BOOST_CHECK (test2 == true);

}

BOOST_AUTO_TEST_CASE(test_Model)
{
   //Constructeur
  Model model1{800,500};
  BOOST_CHECK (model1.getw() == 800 );
  BOOST_CHECK (model1.geth() == 500 );

  //position balle
 int x;
 int y;
 model1.getBallPostion(x,y);
 BOOST_CHECK (x == 100);
 BOOST_CHECK (y == 400);
 //Dimension balle
 int w , h ;
 model1.getballDimension(w , h);
 BOOST_CHECK (w == 50);
 BOOST_CHECK (h== 50);

 //Points de vie
 int pv;
 pv = model1.getpointdevieballe();
 int pvafter;
 model1.retirerpointvieballe(10);
 pvafter = model1.getpointdevieballe();
 int pvheal;
 model1.ajouterpointdevieballe(10);
 pvheal = model1.getpointdevieballe();
 BOOST_CHECK (pv == 100);
 BOOST_CHECK (pvafter = 90);
 BOOST_CHECK (pvheal = 100);

 // Mouvement
 int xavance , yavance , xrecule , yrecule , xsaut, ysaut;
 //Gauche
 model1.moveBAll(true);
 model1.stopballx();
 model1.getBallPostion(xrecule,yrecule);
 BOOST_CHECK (xrecule== 85);
 BOOST_CHECK (yrecule == 400);
 //Droite
 model1.moveBAll(false);
 model1.stopballx();
 model1.getBallPostion(xavance,yavance);
 BOOST_CHECK (xavance == 100);
 BOOST_CHECK (yavance == 400);
 // Saut
 model1.startjump(); // saut
 model1.Evolutionjump();// retombe
 model1.getBallPostion(xsaut,ysaut);
 BOOST_CHECK (xsaut == 100);
 BOOST_CHECK (ysaut == 400);









}
*/
