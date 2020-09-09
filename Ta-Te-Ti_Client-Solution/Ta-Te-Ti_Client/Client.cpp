#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <string.h>
#include "../../TaTeTi_Libs/TA-TE-TI/Tablero.h"
#include "../../Librerias gentille/Libreria.h"

#pragma comment (lib, "ws2_32.lib")

#define MENSAJE_JUGADA 1
#define MENSAJE_CHAT 2
#define TAM_MENSAJE 1500
#define TAM_BUFFER_1KB 1024

struct ClientMessage 
{
public:
	char jugada;
	byte cmd;
	char data[TAM_MENSAJE];
	//bool inWait;
};
struct ServerRequest
{
public:
	byte cmd;
	Tablero *tablero;
	char messenge[TAM_MENSAJE];
};


int SendMessege(const char* buf, sockaddr_in &server, SOCKET &out, int isOk)
{
	int sendOk = sendto(out, buf, sizeof(buf), 0, (sockaddr*)&server, sizeof(server));
	if (sendOk == SOCKET_ERROR)
	{
		std::cout << "Hubo un error al enviar" << isOk << std::endl;
		cin.get();
		cin.get();
		return -1;
	}
	return 0;
}


int CheckCommand(ClientMessage &msg)
{
	if (msg.data[0] == 'C' && msg.data[1] == ':')
	{
		return MENSAJE_CHAT;
	}
	else if(msg.data[0] == 'P' && msg.data[1] == ':')
	{
		for (int i = 2; i < TAM_MENSAJE; i++)
		{
			if (msg.data[i] != ' ')
			{
				if (msg.data[i] != '9' && msg.data[i] != '8'
					&& msg.data[i] != '7' && msg.data[i] != '6'
					&& msg.data[i] != '5' && msg.data[i] != '4'
					&& msg.data[i] != '3' && msg.data[i] != '2'
					&& msg.data[i] != '1')
				{
					std::cout << "Ingreso Invalido" << std::endl;
					cin.get();
					//cin.get();
					return 0;
				}
				else 
				{
					msg.jugada = msg.data[i];
					return MENSAJE_JUGADA;
				}
			}
		}
		return MENSAJE_JUGADA;
	}
	return 0;
}

int main() 
{
	int typeMensaje = 0;
	std::string ip = "127.0.0.1";
	sockaddr_in server;
	WSADATA data;
	ClientMessage msg;
	ServerRequest serverRequest;
	WORD version = MAKEWORD(2, 2);
	int puerto = 8900;
	bool ExitChat = false;
	char ExitCharacter = '0';
	int isOk = WSAStartup(version, &data);
	//inicializar winsock
	if (isOk != 0)
	{
		std::cout << "Cant start!" << isOk << std::endl;
		return -1;
	}

	//std::cout << "Ingrese el numero de puerto: ";
	//std::cin >> puerto;
	//std::cout << "Ingrese el IP del servidor: ";
	//std::cin >> ip;
	server.sin_family = AF_INET;
	server.sin_port = htons(puerto);
	inet_pton(AF_INET, ip.c_str(), &server.sin_addr);
	SOCKET out = socket(AF_INET, SOCK_DGRAM, 0);


	int serverSize = sizeof(server);

	msg.cmd = -1;
	SendMessege((char*)&msg, server, out, isOk);

	//std::cin.get();	
	while (!ExitChat)
	{
		//ZONA DE ENVIO DE MENSAJE AL SERVIDOR
		do 
		{
			system("cls");
			std::cout << "Comandos:" << std::endl;
			std::cout << "\"C:\" -> indica que lo que se envia es un mensaje al chat del servidor." << std::endl;
			std::cout << "\"P:\" -> indica que lo que se envia es la jugada del cliente." << std::endl;
			std::cout << "\"E:\" -> indica que desea salir del servidor" << std::endl;
			//std::cout << buffer << std::endl;
			std::cout << "> ";
			std::cin.getline(msg.data, TAM_MENSAJE);
			typeMensaje = CheckCommand(msg);
			msg.cmd = typeMensaje;
			std::cout << msg.jugada << std::endl;
			std::cin.get();
			//std::cout << typeMensaje << std::endl;
		}
		while (typeMensaje == 0);
		
		SendMessege((char*)&msg, server, out, isOk);

		//------------------------------------------//

		if (msg.data[0] == ExitCharacter)
		{
			ExitChat = true;
		}
		
		//ZONA DE RESPUESTA DEL SERVIDOR
		int bytesIn = recvfrom(out, (char*)&serverRequest, sizeof(serverRequest), 0, (sockaddr*)&server, &serverSize);
		
		switch (serverRequest.cmd)
		{
		case 1:
			cout << serverRequest.messenge << endl;
			cin.get();
			//cin.get();
			break;
		case 2:
			if (serverRequest.tablero != nullptr) 
			{
				//serverRequest.tablero->mostrarTablero(25, 10);
			}
			else 
			{
				cout << "TABLERO NULO" << endl;
				cin.get();
				//cin.get();
			}
			break;
		case 3:

			break;
		}
		if (bytesIn == SOCKET_ERROR)
		{
			std::cerr << "error al recibir data." << std::endl;
			cin.get();
			cin.get();
			return -1;
		}
		//-----------------------------------------------//
		//std::cout << buffer << std::endl;
		//std::cin.get();
	}

	closesocket(out);

	WSACleanup();

	return 0;
}
