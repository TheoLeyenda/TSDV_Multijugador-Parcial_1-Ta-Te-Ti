#ifndef CLIENT_H
#define CLIENT_H
#include <iostream>
#include <WS2tcpip.h>
#include "../../Librerias gentille/Libreria.h"

#pragma comment (lib,"ws2_32.lib")

class Client
{
public:
	struct ClientMenssage
	{
		enum GameState
		{
			None, //NADA
			InLobby,// EN EL LOBY
			InGame, // EN PARTIDA
			WaitMyTurn, //ESPERANDO TURNO
			Win, // GANE
			Lose, // PERDI
			Tie, // EMPATE
		};
		bool turn = false;
		int input = 0;
		std::string alias = "";
		GameState gameState = GameState::None;
		int ID = -1;
		int ID_Enemy = -1;
		bool posicionesTablero[9];
		int cmd = -1;
		bool isMenu = false;
		sockaddr_in from;
		void Restart()
		{
			turn = false;
			input = 0;
			gameState = GameState::None;
			ID = -1;
			ID_Enemy = -1;
			for (int i = 0; i < 9; i++)
			{
				posicionesTablero[i] = false;
			}
			cmd = -1;
			isMenu = false;
		}
	};
private:
	int messagePosX = 70;
	int messagePosY = 5;
	
	// Client Data
	WSADATA data;
	WORD version;
	int port;
	SOCKET sock = INVALID_SOCKET;
	sockaddr_in server;
	ClientMenssage msg;
	ClientMenssage auxMsg;

	// Server Data
	sockaddr_in from;
	char dataBuffer[1024];
	int dataLenght;
	char serverIp[256];
	
private:
	void ShowReceivedMessage();

public:
	Client(int _port);

	void ShowUsuarioName(int x, int y);
	// Startup Winsock
	void Initialize();

	void SendMSG();

	// Enter a loop
	// Wait for message
	// Display message and client info
	void ListenForMessages();
	void ListenOtherMassages(bool takeGameState);

	// Close socket
	// Shutdown winsock
	void ShowLocationClient();
	void Shutdown();
	void SetInput(int _input);
	
	std::string GetAlias();
	ClientMenssage::GameState GetGameState();
	void SetGameState(int _gameState);
	int GetCMD();
	void SetCMD(int _cmd);
	bool GetTurn();
	void SetTurn(bool _turn);
	sockaddr_in GetFrom();
	void ResetMSG();
	void ResetAuxMSG();
	void ResetTurn();
	void ResetInput();
	void ResetID();
	void ResetID_Ememy();
	void ResetPosicionesTablero();
	void ResetCMD();
	void SetIsMenu(bool _isMenu);
	bool GetIsMenu();

};

#endif // CLIENT_H

