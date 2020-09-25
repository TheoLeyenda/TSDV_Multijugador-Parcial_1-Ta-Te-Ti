#ifndef PUNTO_H
#define PUNTO_H
using namespace std;
#include <iostream>
#include "../../Librerias gentille/Libreria.h"

class Punto
{
private:
	int _x;
	int _y;
public:
	Punto();
	Punto(int x, int y);
	void setX(int x);
	void setY(int y);
	int getX();
	int getY();
	void mostrar();
	void dibujar();
	void mover(int x, int y);
	void borrar();
};
#endif
