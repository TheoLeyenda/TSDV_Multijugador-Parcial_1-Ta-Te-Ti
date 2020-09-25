#include <iostream>
using namespace std;
#include "Tablero.h"
#include "Juego.h"
void main(){
	gotoxy(35,1);
	cout<<"TA-TE-TI"<<endl;
	cout<<"ingrese Enter para jugar....";
	cin.get();
	system("cls");
	Juego* j = new Juego();
	j->play();
	delete j;
}