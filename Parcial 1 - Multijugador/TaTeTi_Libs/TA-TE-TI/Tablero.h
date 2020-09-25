#ifndef TABLERO_H
#define TABLERO_H
#define MAX_FIL 3
#define MAX_COL 3
#include <iostream>
using namespace std;
class Tablero
{
private:
	char _tablero[MAX_FIL][MAX_COL];
	char _ganador;
	int _tipo;
	bool _repetirTurno;
	float _posX;
	float _posY;
public:
	Tablero(int tipo, float x, float y);
	void mostrarTablero(float x, float y); //muestra como esta el tablero y a los jugadores que estan en el(O,X).
	void colocarJugador(int fila, int columna, char jugador); //recorre el arreglo y coloca una X o un O dependiendo del jugador.
	void reiniciarTablero(int tipo); //inicializa el arreglo a 'i' en un for.
	void verificarTaTeTi(char jugador1, char jugador2); //se fija si un jugador hizo ta-te-ti, si hizo ta-te-ti retorna true, sino retorna false.
	char getCasilla(int fila, int columna);//retorna lo que hay en la casilla del tablero
	char getGanador();
	void setGanador(char ganador);
	void verificarEmpate(char jugador1, char jugador2);// verifica si hay empate y en caso que lo haya _ganador = 'N';
	bool getRepetirTurno();
	void setRepetirTurno(bool repetirTurno);
	float GetPosX();
	float GetPosY();
	int GetTipoTablero();

};
#endif
