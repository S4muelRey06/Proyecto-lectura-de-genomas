#ifndef __COORDENADA_H__
#define __COORDENADA_H__

#include <iostream>
#include <vector>

using namespace std;

class Coordenada
{
protected:
   int x;
   int y;

public:
    Coordenada(int x, int y);
    int getX();
    int getY();
    void setX(int x);
    void setY(int y);
};
#include "coordenada.hxx"
#endif