#ifndef JUEGO_H
#define JUEGO_H
#include "../../Librerias gentille/Libreria.h"
#include "Tablero.h"

class Juego
{
private:
	Tablero* _tablero;
	bool _gameOver;
	char _jugador1;
	char _jugador2;
	int _turno;
	char _ganador;
	int _gano;
	int _puntajeJ1;
	int _puntajeJ2;
	int _opcion;
	bool _primerTurno;
public:
	Juego(float x, float y);
	~Juego();
	void init();
	void input();
	void update();
	void draw();
	void result();
	bool gameOver();
	void setGanador(int ganador);
	void play();

};
#endif

