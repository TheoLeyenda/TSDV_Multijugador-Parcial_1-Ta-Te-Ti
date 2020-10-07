#ifndef SERVER_H
#define SERVER_H
#include<iostream>
#include <map>
#include <stdlib.h>
#include <time.h>

//INICIALIZAMOS MULTIPLATAFORMA
#ifdef _WIN32
#include <WS2tcpip.h>
/* See http://stackoverflow.com/questions/12765743/getaddrinfo-on-win32 */
	#ifndef _WIN32_WINNT
		#define _WIN32_WINNT 0x0501  /* Windows XP. */
	#endif

#include <winsock2.h>
#include <Ws2tcpip.h>
#else
/* Assume that any non-Windows platform uses POSIX-style sockets instead. */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>  /* Needed for getaddrinfo() and freeaddrinfo() */
#include <unistd.h> /* Needed for close() */
#endif

#pragma comment (lib,"ws2_32.lib")
class Server
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
		std::string aliasContrincante = " ";
		GameState gameState = GameState::None;
		int ID = -1;
		int ID_Enemy = -1;
		bool posicionesTablero[9];
		int cmd = -1;
		bool isMenu = false;
		bool firstMove = false;
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
			aliasContrincante = " ";
			firstMove = false;
			isMenu = false;
		}
	};
private:
	struct Party 
	{
		ClientMenssage player1;
		ClientMenssage player2;
		bool PlayAgain_Player1 = false;
		bool PlayAgain_Player2 = false;
		int countVotos = 0;
		const int maxVotos = 2;
		int assignedTurn = 0;
		void GenerateTurn()
		{
			assignedTurn = rand() % 100 + 1;

			std::cout << assignedTurn << std::endl;

			if (assignedTurn > 50)
			{
				player1.turn = true;
				player1.gameState = Server::ClientMenssage::GameState::InGame;
				player2.turn = false;
				player2.gameState = Server::ClientMenssage::GameState::WaitMyTurn;
			}
			else
			{
				player1.turn = false;
				player1.gameState = Server::ClientMenssage::GameState::WaitMyTurn;
				player2.turn = true;
				player2.gameState = Server::ClientMenssage::GameState::InGame;
			}
		}
	};
	// Server Data
	WSADATA data;
	WORD version;
	sockaddr_in server;
	
	fd_set master;
	SOCKET listener;
	int nbytes;
	struct timeval tv;

	int port;
	//bool sendSpecificClient = false;

	// Client Data
	sockaddr_in from;
	int dataLenght;
	char clientIp[256];
	ClientMenssage msg;

	//Client Register
	std::map<int, ClientMenssage> mapClients;
	std::map<int, Party> mapPartys;
	int indexClientes = 0;
	int indexPartys = 0;
	
private:
	void ShowReceivedMessage();

public:
	Server(int _port);

	//Inicializa al servidor
	void Initialize();

	int SockInit();
	//Bindea los sockets del servidor
	void BindSocket();

	//Escucha a ver que mensaje recibe y devuelve la info en base al mensaje recibido.
	void ListenForMessages();

	//Envia un mensaje al cliente que le hablo al servidor
	void SendMSG();
	
	//Envia un mensaje a un cliente en especifico.
	void SendMSG(sockaddr_in &socketClient);

	//Envia un el mensaje por parametro a un cliente en especifico.
	void SendMSG(sockaddr_in &socketClient, ClientMenssage _msg);
	
	//cierro el servidor
	int Shutdown();
	//Logica del juego
	void CheckTurnPlayer(int input, bool playEnabled, int size); // Recorre los dicionarios de partidas y chekea que la jugada sea valida segun el turno del jugador

	void CheckPlayAgain(int size, bool playAgain);

};
#endif

