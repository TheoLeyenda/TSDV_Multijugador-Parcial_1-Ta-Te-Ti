#include "Server.h"
#include <string>
#include <stdlib.h>
#include <time.h>

Server::Server(int _port):port(_port)
{
	srand(time(NULL));
	for (int i = 0; i < 9; i++)
	{
		msg.posicionesTablero[i] = false;
	}
}

void Server::Initialize()
{
	version = MAKEWORD(2, 2);
	int wsOk = WSAStartup(version, &data);
	if (wsOk != 0)
	{
		std::cout << "SERVER: Error, no se pudo iniciar winsock! " << wsOk;
		return;
	}
	std::cout << "SERVER: El Servidor se inicio correctamente!" << std::endl;
	sock = socket(AF_INET, SOCK_DGRAM, 0);

	if (sock < 0)
	{
		std::cout << "SERVER: Error al abrir el socket" << std::endl;
	}
	server.sin_family = AF_INET;
	server.sin_addr.S_un.S_addr = ADDR_ANY;
	server.sin_port = htons(port);
	//192.168.0.15
	inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);
}

void Server::BindSocket()
{
	if (bind(sock, (sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
	{
		std::cout << "SERVER: Error, no se pudo bindear el socket! " << WSAGetLastError() << std::endl;
		return;
	}
	std::cout << "SERVER: El Socket fue bindeado correctamente!" << std::endl;

	dataLenght = sizeof(from);
	ZeroMemory(&from, dataLenght);
}

void Server::ListenForMessages()
{
	bool inGameEvent = false;
	int countResetInGameEvent = 0;
	int countElementsPartys = 0;
	while (!shutdown)
	{
		int bytesIn = recvfrom(sock, (char*)&msg, sizeof(msg), 0, (sockaddr*)&from, &dataLenght);
		if (bytesIn == SOCKET_ERROR)
		{
			std::cout << "SERVER: Error al resivir el mensaje del cliente " << WSAGetLastError() << std::endl;
			continue;
		}

		switch (msg.input)
		{
		case 0:
			if (msg.gameState == msg.None)
			{
				//mapPartys[indexPartys].GenerateTurn();
				//mapPartys[indexPartys].GenerateTurn(); 
				//mapPartys[indexPartys].GenerateTurn();

				indexClientes++;
				msg.ID = indexClientes; // 2
				msg.gameState = msg.InLobby;
				std::cout << "Entre al lobby" << std::endl;
				msg.from = from;
				mapClients[indexClientes] = msg;
				msg.firstMove = true;
				if (indexClientes % 2 == 0)
				{
					inGameEvent = true;
					std::cout << "ENTRE" << std::endl;
					mapClients[indexClientes - 1].gameState = msg.InGame;
					mapClients[indexClientes].gameState = msg.InGame;

					mapPartys[indexPartys].player1 = mapClients[indexClientes - 1];
					mapPartys[indexPartys].player2 = mapClients[indexClientes];

					mapPartys[indexPartys].player1.aliasContrincante = mapPartys[indexPartys].player2.alias;
					mapPartys[indexPartys].player2.aliasContrincante = mapPartys[indexPartys].player1.alias;

					//std::cout << "CONTRINCANTE PLAYER 1: " << mapPartys[indexPartys].player1.aliasContrincante.c_str() << std::endl;
					//std::cout << "CONTRINCANTE PLAYER 2: " << mapPartys[indexPartys].player2.aliasContrincante.c_str() << std::endl;

					mapPartys[indexPartys].GenerateTurn();

					indexPartys++;
					countElementsPartys++;
				}
			}
			else if ((mapPartys[indexPartys-1].player1.ID == msg.ID && msg.gameState == msg.InLobby)
			|| (mapPartys[indexPartys-1].player2.ID == msg.ID && msg.gameState == msg.InLobby)
				&& inGameEvent)
			{
				
				std::cout << "ENTRE AL REGISTRO DE USUARIOS" << std::endl;
				if (mapPartys[indexPartys - 1].player1.ID == msg.ID && msg.gameState == msg.InLobby)
				{
					countResetInGameEvent++;
					mapPartys[indexPartys - 1].player1.ID_Enemy = mapPartys[indexPartys - 1].player2.ID;
					msg.ID_Enemy = mapPartys[indexPartys - 1].player2.ID;

					msg.aliasContrincante = mapPartys[indexPartys - 1].player2.alias;
					msg.turn = mapPartys[indexPartys - 1].player1.turn;
					msg.gameState = mapPartys[indexPartys - 1].player1.gameState;

				}
				else if (mapPartys[indexPartys - 1].player2.ID == msg.ID && msg.gameState == msg.InLobby)
				{
					countResetInGameEvent++;
					mapPartys[indexPartys - 1].player2.ID_Enemy = mapPartys[indexPartys - 1].player1.ID;
					msg.ID_Enemy = mapPartys[indexPartys - 1].player1.ID;

					msg.aliasContrincante = mapPartys[indexPartys - 1].player1.alias;
					msg.turn = mapPartys[indexPartys - 1].player2.turn;
					msg.gameState = mapPartys[indexPartys - 1].player2.gameState;
				}
				//msg.gameState = msg.WaitMyTurn;
				if (countResetInGameEvent >= 2)
				{
					std::cout << "LOS DOS USUARIOS ESTAN EN JUEGO" << std::endl;
					//msg.turn = true;
					inGameEvent = false;
					countResetInGameEvent = 0;
					//msg.gameState = msg.InGame;
				}
			}
			std::cout << "Player1 - ID: " << mapPartys[indexPartys - 1].player1.ID << " = " << msg.ID << std::endl;
			std::cout << "Player2 - ID: " << mapPartys[indexPartys - 1].player2.ID << " = " << msg.ID << std::endl;
			break;
		case 1:
			CheckTurnPlayer(1, !msg.posicionesTablero[0], countElementsPartys);
			break;
		case 2:
			CheckTurnPlayer(2, !msg.posicionesTablero[1], countElementsPartys);
			break;
		case 3:
			CheckTurnPlayer(3, !msg.posicionesTablero[2], countElementsPartys);
			break;
		case 4:
			CheckTurnPlayer(4, !msg.posicionesTablero[3], countElementsPartys);
			break;
		case 5:
			CheckTurnPlayer(5, !msg.posicionesTablero[4], countElementsPartys);
			break;
		case 6:
			CheckTurnPlayer(6, !msg.posicionesTablero[5], countElementsPartys);
			break;
		case 7:
			CheckTurnPlayer(7, !msg.posicionesTablero[6], countElementsPartys);
			break;
		case 8:
			CheckTurnPlayer(8, !msg.posicionesTablero[7], countElementsPartys);
			break;
		case 9:
			CheckTurnPlayer(9, !msg.posicionesTablero[8], countElementsPartys);
			break;
		case 10:
			CheckPlayAgain(countElementsPartys, true);
			break;
		case 11:
			CheckPlayAgain(countElementsPartys, false);
			break;
		}
		ZeroMemory(clientIp, 256);
		ShowReceivedMessage();

		//if(!sendSpecificClient)
			SendMSG();
		//else 
			//sendSpecificClient = false;
	}
}

void Server::CheckPlayAgain(int size, bool playAgain)
{
	ClientMenssage msg_enemy;
	int assignedTurn = rand() % 100 + 1;
	bool exitLoop = false;
	std::cout << "ENTRE AL PLAY AGAIN" << std::endl;
	std::cout << "Size: "<<size << std::endl;
	for (int i = 0; i < size; i++) 
	{
		
		if (mapPartys[i].player1.ID == msg.ID) 
		{
			//std::cout << "ENTRE AL PLAYER 1" << std::endl;
			mapPartys[i].countVotos++;
			mapPartys[i].PlayAgain_Player1 = playAgain;
			msg_enemy = mapPartys[i].player2;
			msg.cmd = 15;
			if (!playAgain) 
			{
				//std::cout << "ADIOH PLAYER 1" << std::endl;
				msg.cmd = 13;
				msg_enemy.cmd = 13;
			}
			exitLoop = true;
		}
		else if (mapPartys[i].player2.ID == msg.ID) 
		{
			//std::cout << "ENTRE AL PLAYER 2" << std::endl;
			mapPartys[i].countVotos++;
			mapPartys[i].PlayAgain_Player2 = playAgain;
			msg_enemy = mapPartys[i].player1;
			msg.cmd = 15;
			if (!playAgain)
			{
				//std::cout << "ADIOH PLAYER 1" << std::endl;
				msg.cmd = 13;
				msg_enemy.cmd = 13;
			}
			exitLoop = true;
		}
		std::cout << mapPartys[i].countVotos<<"/"<< mapPartys[i].maxVotos << std::endl;
		if (mapPartys[i].countVotos >= mapPartys[i].maxVotos) 
		{
			//std::cout << mapPartys[i].PlayAgain_Player2 << "/" << mapPartys[i].PlayAgain_Player1 << std::endl;
			if (mapPartys[i].PlayAgain_Player1 && mapPartys[i].PlayAgain_Player2)
			{
				msg.cmd = 12;
				msg_enemy.cmd = 12;
				if (assignedTurn > 50 && assignedTurn <= 100) 
				{
					msg.turn = true;
					msg.gameState = msg.InGame;
					msg_enemy.turn = false;
					msg_enemy.gameState = msg_enemy.WaitMyTurn;
				}
				else
				{
					msg.turn = false;
					msg.gameState = msg.WaitMyTurn;
					msg_enemy.turn = true;
					msg_enemy.gameState = msg_enemy.InGame;
				}
				mapPartys[i].PlayAgain_Player1 = false;
				mapPartys[i].PlayAgain_Player2 = false;

				//std::cout << "ENVIE EL COCHINO MENSAJE" << std::endl;
				//SendMSG(msg.from);
				//SendMSG(msg.from);
				std::cout << msg_enemy.gameState << " = " << msg.gameState << std::endl;
				SendMSG(msg_enemy.from, msg_enemy);
				//SendMSG(msg_enemy.from);
				
				//SendMSG(msg.from);
				
				//sendSpecificClient = true;
				exitLoop = true;
				mapPartys[i].countVotos = 0;
			}
			else 
			{
				std::cout << "CMD 13" << std::endl;
				msg.cmd = 13;
				mapPartys[i].player1.Restart();
				mapPartys[i].player2.Restart();
				mapPartys[i].PlayAgain_Player1 = false;
				mapPartys[i].PlayAgain_Player2 = false;

			}
			if (exitLoop)
			{
				i = mapPartys.size();
			}
		}

	}
	exitLoop = false;
}

void Server::CheckTurnPlayer(int input, bool playEnabled, int size)
{
	if (playEnabled) 
	{
		ClientMenssage msg_enemy;
		for (int i = 0; i < size; i++)
		{
			if (msg.turn && mapPartys[i].player1.ID == msg.ID && msg.gameState == msg.InGame)
			{
				msg.cmd = input;
				msg.posicionesTablero[input - 1] = true;
				msg_enemy = mapPartys[i].player2;
				msg_enemy.cmd = input;
				SendMSG(msg_enemy.from);
				i = mapPartys.size();
			}
			else if (msg.turn && mapPartys[i].player2.ID == msg.ID && msg.gameState == msg.InGame)
			{
				msg.cmd = input;
				msg.posicionesTablero[input - 1] = true;
				msg_enemy = mapPartys[i].player1;
				msg_enemy.cmd = input;
				SendMSG(msg_enemy.from);
				i = mapPartys.size();
			}
		}
	}
	else 
	{
		msg.cmd = 0;
	}
}


void Server::SendMSG()
{
	//msg.ID = 777;
	// Write out to that socket
	int sendOk = sendto(sock, (char*)&msg, sizeof(msg), 0, (sockaddr*)&from, sizeof(from));
	if (sendOk == SOCKET_ERROR)
	{
		std::cout << " SERVER: No se pudo enviar el mensaje " << WSAGetLastError() << std::endl;
		std::cin.get();
	}
}

void Server::SendMSG(sockaddr_in &socketClient)
{
	int sendOk = sendto(sock, (char*)&msg, sizeof(msg), 0, (sockaddr*)&socketClient, sizeof(socketClient));
	if (sendOk == SOCKET_ERROR)
	{
		std::cout << " SERVER: No se pudo enviar el mensaje " << WSAGetLastError() << std::endl;
		std::cin.get();
	}
}

void Server::SendMSG(sockaddr_in & socketClient, ClientMenssage _msg)
{
	int sendOk = sendto(sock, (char*)&_msg, sizeof(_msg), 0, (sockaddr*)&socketClient, sizeof(socketClient));
	if (sendOk == SOCKET_ERROR)
	{
		std::cout << " SERVER: No se pudo enviar el mensaje " << WSAGetLastError() << std::endl;
		std::cin.get();
	}
}

void Server::ShowReceivedMessage()
{
	inet_ntop(AF_INET, &from.sin_addr, clientIp, 256);
	std::cout << "Mensaje recibido desde " << clientIp << ": " << msg.alias.c_str() << std::endl;
}

void Server::Shutdown()
{
	closesocket(sock);
	WSACleanup();
}