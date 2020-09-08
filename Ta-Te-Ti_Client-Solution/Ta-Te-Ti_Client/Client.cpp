#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <string.h>

#pragma comment (lib, "ws2_32.lib")

#define MENSAJE_JUGADA 1
#define MENSAJE_CHAT 2
#define TAM_MENSAJE 1500
#define TAM_BUFFER_1KB 1024

struct ClientMessage 
{
public:
	byte cmd;
	char data[TAM_MENSAJE];
};

struct ClientMessage_Move 
{
public:
	byte pos_move;
};

int SendMessege(const char* buf, sockaddr_in server, SOCKET out, int isOk)
{
	std::string msg = std::string(buf);
	int sendOk = sendto(out, buf, sizeof(buf), 0, (sockaddr*)&server, sizeof(server));
	if (sendOk == SOCKET_ERROR)
	{
		std::cout << "Hubo un error al enviar" << isOk << std::endl;
		std::cin.get();
		return -1;
	}
	return 0;
}


int CheckCommand(char mensaje[TAM_MENSAJE])
{
	if (mensaje[0] == 'C' && mensaje[1] == ':') 
	{
		return MENSAJE_CHAT;
	}
	else if(mensaje[0] == 'P' && mensaje[1] == ':')
	{
		return MENSAJE_JUGADA;
	}
	return 0;
}

int main() 
{
	char jugador = 'O';
	int typeMensaje = 0;
	std::string ip = "127.0.0.1";
	sockaddr_in server;
	WSADATA data;
	ClientMessage msg;
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

	char buffer[TAM_BUFFER_1KB];
	memset(buffer, 0, sizeof(buffer));
	int serverSize = sizeof(server);

	//std::cin.get();	
	while (!ExitChat)
	{

		do 
		{
			system("cls");
			std::cout << "Comandos:" << std::endl;
			std::cout << "\"C:\" -> indica que lo que se envia es un mensaje al chat del servidor." << std::endl;
			std::cout << "\"P:\" -> indica que lo que se envia es la jugada del cliente." << std::endl;
			std::cout << buffer << std::endl;
			std::cout << "> ";
			std::cin.getline(msg.data, TAM_MENSAJE);
			typeMensaje = CheckCommand(msg.data);
			msg.cmd = typeMensaje;
			//std::cout << typeMensaje << std::endl;
		}
		while (typeMensaje == 0);
		
		SendMessege((char*)&msg, server, out, isOk);

		if (msg.data[0] == ExitCharacter)
		{
			ExitChat = true;
		}

		int bytesIn = recvfrom(out, buffer, sizeof(buffer), 0, (sockaddr*)&server, &serverSize);
		if (bytesIn == SOCKET_ERROR)
		{
			std::cerr << "error al recibir data." << std::endl;
			std::cin.get();
			return -1;
		}
		std::cout << buffer << std::endl;
		std::cin.get();
	}

	closesocket(out);

	WSACleanup();

	return 0;
}
