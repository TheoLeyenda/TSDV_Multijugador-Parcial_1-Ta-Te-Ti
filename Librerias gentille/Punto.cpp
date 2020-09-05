#include "Punto.h"


Punto::Punto(){
}
Punto::Punto(int x,int y){
	_x = x;
	_y = y;
}
void Punto::setX(int x){
	if(x<80 && x>0){
		_x = x;
	}
}
void Punto::setY(int y){
	if(y<25 && y>0){
		_y = y;
	}
}
int Punto::getX(){
	return _x;
}
int Punto::getY(){
	return  _y;
}
void Punto::mostrar(){
	cout<<"[x,y]=(",_x,",",_y,")";
}
void Punto::dibujar(){
	gotoxy(_x,_y);
	cout<<"*";
}
void Punto::borrar(){
	gotoxy(_x,_y);
	cout<<" ";
}
void Punto::mover(int x,int y){
	if((y<25 && y>0)&&(x<80 && x>0)){
		_y = y;
		_x = x;
		gotoxy(_x,_y);
	}
	else{
		cout<<"ERROR: las cordenadas ingresadas superan el limite de la pantalla";
	}
}