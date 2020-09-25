#ifndef JUEGO_H
#define JUEGO_H
#define _WINSOCKAPI_
#include "../../Librerias gentille/Libreria.h"
#include "Tablero.h"
#include "../../Client/Client/Client.h"
#include "raylib.h"

class Juego
{
public:
enum Dibujar 
{
	jugador,
	contrincante,
};
private:
	//Networking
	Client* _cliente;

	//Juego
	Tablero* _tablero;
	Dibujar _dibujo;
	//bool _gane;
	char tuEquipo;
	char equipoEnemigo;
	bool EnJuego;
	bool firstOnceInGame = true;
	//rayLib
	const int screenWidth = 400;
	const int screenHeight = 400;
	Raylib::Vector2 ballPosition = { (float)screenWidth / 2, (float)screenHeight / 2 };


	//data del cliente
	int _id;
	std::string alias;

public:
	Juego(float x, float y);
	~Juego();
	void CrearUsuario();
	void DestruirUsuario();
	void UpdateUsuario();
	//void SetDibujo(bool miTurno, int posicion);
	void SetID(int _id);
private:
	void DibujarTablero();
	void DibujarJugador(int input, int dibujo);
	void Dibujar(char jugador, int input);
	void VerificarTablero();
	void ResultGame(bool inputPositivo, bool inputNegativo, Client::ClientMenssage::GameState gameState);

};
#endif

