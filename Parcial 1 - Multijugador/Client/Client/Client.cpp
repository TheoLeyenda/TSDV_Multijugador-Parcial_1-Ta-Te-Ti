#include "Client.h"
#include <string>



Client::Client(int _port) :port(_port) 
{
	for (int i = 0; i < 9; i++) 
	{
		msg.posicionesTablero[i] = false;
	}
}

void Client::ShowUsuarioName(int x, int y)
{
	gotoxy(x, y);
	cout << "Usuario: " << msg.alias.c_str() << endl;
}

void Client::Initialize()
{
	version = MAKEWORD(2, 2);
	int wsOk = WSAStartup(version, &data);
	if (wsOk != 0)
	{
		std::cout << "CLIENT: Error, no se pudo iniciar winsock! " << wsOk;
		std::cin.get();
		return;
	}
	std::cout << "CLIENT: El Cliente se ha iniciado correctamente!" << std::endl;

	sock = socket(AF_INET, SOCK_DGRAM, 0);
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);
	std::cout << "Ingrese su alias: ";
	std::cin.get();
	getline(std::cin, msg.alias);
	
}

void Client::SendMSG()
{
	// Write out to that socket
	int sendOk = sendto(sock, (char*)&msg, sizeof(msg), 0, (sockaddr*)&server, sizeof(server));
	if (sendOk == SOCKET_ERROR)
	{
		std::cout << " CLIENT: Error, no se pudo enviar el mensaje " << WSAGetLastError << std::endl;
		std::cin.get();
		//return;
	}
}

void Client::ListenForMessages()
{
	dataLenght = sizeof(from);
	ZeroMemory(&from, dataLenght);
	ZeroMemory(dataBuffer, 1024);
	int bytesIn = recvfrom(sock, (char*)&msg, sizeof(msg), 0, (sockaddr*)&from, &dataLenght);
	if (bytesIn == SOCKET_ERROR)
	{
		cout << "Error al resivir el mensaje del servidor " << WSAGetLastError() << endl;
		cin.get();
	}
	else {
		ZeroMemory(serverIp, 256);
		ShowReceivedMessage();
	}
}

void Client::ListenOtherMassages(bool takeGameState)
{
	dataLenght = sizeof(from);
	ZeroMemory(&from, dataLenght);
	ZeroMemory(dataBuffer, 1024);
	int bytesIn = recvfrom(sock, (char*)&auxMsg, sizeof(auxMsg), 0, (sockaddr*)&from, &dataLenght);

	msg.input = auxMsg.input;
	msg.cmd = auxMsg.cmd;
	for (int i = 0; i < 9; i++) 
	{
		msg.posicionesTablero[i] = auxMsg.posicionesTablero[i];
	}
	if (takeGameState) 
	{
		msg.gameState = auxMsg.gameState;
		//int x = 25;
		//int y = 20;
		//gotoxy(x, y + 4);
	}
	if (bytesIn == SOCKET_ERROR)
	{
		cout << "Error al resivir el mensaje del servidor " << WSAGetLastError() << endl;
		cin.get();
	}
	else {
		ZeroMemory(serverIp, 256);
		ShowReceivedMessage();
	}
}

void Client::ShowReceivedMessage()
{
	inet_ntop(AF_INET, &from.sin_addr, serverIp, 256);
	bool showMessageData = false;
	if (showMessageData) 
	{
		gotoxy(messagePosX, 4);
		cout << "RESPUESTAS DEL SERVIDOR" << endl;
		messagePosY++;
		gotoxy(messagePosX, messagePosY);
		cout << "Mensaje recibido desde " << serverIp << " : " << msg.ID << endl;
	}
	ShowLocationClient();
}

void Client::ShowLocationClient()
{

	switch (msg.gameState)
	{
	case ClientMenssage::GameState::None:
		if (msg.isMenu) 
		{
			gotoxy(30, 2);
			cout << "                                    " << endl;
			gotoxy(25, 3);
			cout << "                                    " << endl;
			gotoxy(30, 2);
			cout << "|MENU|" << endl;
			gotoxy(25, 3);
			cout << "> 1. Buscar partida." << endl;
			gotoxy(25, 4);
			cout << "> 2. Salir." << endl;
		}
		break;
	case ClientMenssage::GameState::InLobby:
		gotoxy(30, 2);
		cout << "                                    " << endl;
		gotoxy(30, 2);
		cout << "|SALA DE ESPERA|" << endl;
		break;
	case ClientMenssage::GameState::InGame:
		gotoxy(30, 2);
		cout << "                                    " << endl;
		gotoxy(30, 2);
		cout << "|PARTIDA EN CURSO|" << endl;
		gotoxy(30, 4);
		cout << "                                    " << endl;
		gotoxy(30, 4);
		cout << "   Tu Turno" << endl;
		break;
	case ClientMenssage::GameState::WaitMyTurn:
		gotoxy(30, 2);
		cout << "                                    " << endl;
		gotoxy(30, 2);
		cout << "|PARTIDA EN CURSO|" << endl;
		gotoxy(30, 4);
		cout << "                                    " << endl;
		gotoxy(30, 4);
		cout << "Turno Del Oponente" << endl;
		break;
	case ClientMenssage::GameState::Win:
		gotoxy(30, 2);
		cout << "                                    " << endl;
		gotoxy(30, 2);
		cout << "|GANASTE! :D|" << endl;
		gotoxy(30, 4);
		cout << "                                    " << endl;
		break;
	case ClientMenssage::GameState::Lose:
		gotoxy(30, 2);
		cout << "                                    " << endl;
		gotoxy(30, 2);
		cout << "|PERDISTE! D:|" << endl;
		gotoxy(30, 4);
		cout << "                                    " << endl;
		break;
	case ClientMenssage::GameState::Tie:
		gotoxy(30, 2);
		cout << "                                    " << endl;
		gotoxy(30, 2);
		cout << "|EMPATE! :/|" << endl;
		gotoxy(30, 4);
		cout << "                                    " << endl;
		break;
	}
}

void Client::Shutdown()
{
	closesocket(sock);
	WSACleanup();
}

void Client::SetInput(int _input)
{
	msg.input = _input;
}

std::string Client::GetAlias()
{
	return msg.alias;
}

Client::ClientMenssage::GameState Client::GetGameState()
{
	return msg.gameState;
}

void Client::SetGameState(int _gameState)
{
	switch (_gameState)
	{
	case 0:
		msg.gameState = Client::ClientMenssage::GameState::None;
		break;
	case 1:
		msg.gameState = Client::ClientMenssage::GameState::InLobby;
		break;
	case 2:
		msg.gameState = Client::ClientMenssage::GameState::InGame;
		break;
	case 3:
		msg.gameState = Client::ClientMenssage::GameState::WaitMyTurn;
		break;
	case 4:
		msg.gameState = Client::ClientMenssage::GameState::Win;
		break;
	case 5:
		msg.gameState = Client::ClientMenssage::GameState::Lose;
		break;
	case 6:
		msg.gameState = Client::ClientMenssage::GameState::Tie;
		break;
	}
}

int Client::GetCMD()
{
	return msg.cmd;
}

void Client::SetCMD(int _cmd)
{
	msg.cmd = _cmd;
}

bool Client::GetTurn()
{
	return msg.turn;
}

void Client::SetTurn(bool _turn)
{
	msg.turn = _turn;
}

sockaddr_in Client::GetFrom()
{
	return msg.from;
}

void Client::ResetMSG()
{
	msg.Restart();
}

void Client::ResetAuxMSG()
{
	auxMsg.Restart();
}

void Client::ResetTurn()
{
	msg.turn = false;
}

void Client::ResetInput()
{
	msg.input = 0;
}

void Client::ResetID()
{
	msg.ID = 0;
}
void Client::ResetID_Ememy() 
{
	msg.ID_Enemy = 0;
}

void Client::ResetPosicionesTablero()
{
	for (int i = 0; i < 9; i++)
	{
		msg.posicionesTablero[i] = false;
	}
}

void Client::ResetCMD()
{
	msg.cmd = 0;
}

void Client::SetIsMenu(bool _isMenu)
{
	msg.isMenu = _isMenu;
}

bool Client::GetIsMenu()
{
	return msg.isMenu;
}



