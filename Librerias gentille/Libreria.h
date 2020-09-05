#ifndef LIBRERIA_H
#define LIBRERIA_H

#include <iostream>
#include <conio.h>
#include <string>
#include <sstream>
#include <windows.h>
using namespace std;

#define COLOR_T int
#define COLOR_BLACK	0
#define COLOR_BLUE	1
#define COLOR_GREEN	2
#define COLOR_CYAN	3
#define COLOR_RED	4
#define COLOR_MAGENTA 5
#define COLOR_BROWN	6
#define COLOR_WHITE	7
#define COLOR_GRAY	8
#define COLOR_LBLUE	9
#define COLOR_LGREEN 10
#define COLOR_LCYAN	11
#define COLOR_LRED	12
#define COLOR_LMAGENTA 13
#define COLOR_YELLOW 14
#define COLOR_BWHITE 15   

#define LEFT_UP 201
#define LEFT_DW 200
#define RIGHT_UP 187
#define RIGHT_DW 188
#define LINE_HOR 205
#define LINE_VER 186

#define KEY_ESC		27
#define KEY_UP		256+72
#define KEY_DOWN	256+80
#define KEY_LEFT	256+75
#define KEY_RIGHT	256+77
#define KEY_DELETE	256+83
#define KEY_INSERT	256+82
#define KEY_ENTER	13
#define KEY_BEG		256+71
#define KEY_END		256+79

void cartel();//cabecera o prototipo de funciones
void setBackColor(COLOR_T color); // cambia el color del fondo
void setForeColor(COLOR_T color); // cambia el color del texto
void clrscr(); // borra la pantalla
void gotoxy(int x, int y); // mueve el cursor de texto a las coordenadas x,y (base 1)
int getKey(bool wait=true); // false=espera una tecla, true=pregunta si se presiono una tecla pero no espera
void hideCursor(); // oculta el cursor de texto
void showCursor(); // muestra el cursor de texto
void setTitle(const char* title); // cambia el titulo de la ventana
void miliSleep(int n); // espera un tiempo dado (en milisengundos)
int getScreenWidth(); // retorna el ancho de la consola
int getScreenHeight(); // retorna el alto de la consola
void marco(int x1, int y1,int x2, int y2); 
void cuadro(int x1 , int y1, int x2, int y2);// dibuja un marco doble
#endif