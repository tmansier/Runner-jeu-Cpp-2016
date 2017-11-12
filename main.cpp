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

/*    Copyright (C) 2016 Thibault Mansier et Valentine Renaud

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT= 600;

int main(){
  srand(time(NULL));

  Model model(SCREEN_WIDTH, SCREEN_HEIGHT);
  View view(SCREEN_WIDTH, SCREEN_HEIGHT);
  view.setModel(&model);

  while(view.treatEvents()){
    model.nextStep();
    view.draw();
    view.syncronize();
  }



  return EXIT_SUCCESS;
}
