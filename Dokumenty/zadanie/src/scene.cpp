#include "scene.hh"
#include <iostream>
#include <string.h>
#include <sstream>



using namespace std;

bool string2double(const char * sNum, double &rVal){
  istringstream iStrm(sNum);
  if(!(iStrm >> rVal))
    return false;
  char ch;
  return !(iStrm >> ch);
}

bool Scene::checkCollision(const Wektor3D& pos){
  for(const auto& x : obstacles){
    if(x.intersects(pos)){
      cerr << "Nastapila kolizja z przeszkoda: " << x.getName() << endl;
      return true;
    }
  }
  return false;
}

