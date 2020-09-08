#include <iostream>
#include <WS2tcpip.h>
#include "../../TaTeTi_Libs/TA-TE-TI/Tablero.h"
#include "../../Librerias gentille/Libreria.h"
#pragma comment(lib, "ws2_32.lib")

#define TAM_MENSAJE 1500
using namespace std;

struct ClientMessage
{
public:
	byte cmd;
	char data[TAM_MENSAJE];
};
struct ServerRequest 
{
public:
	byte cmd;
	char messenge[TAM_MENSAJE];
	char tablero[TAM_MENSAJE];
};

struct ClientData
{
public:
	sockaddr_in client;
	ClientMessage clientMessage;
	int clientSize;
	int port;
	char ip[32];
	int bytesInClient;
	int idClient;
	void FindIp(int family, const void* ptr, char PTR[], int stringBufferSize)
	{
		inet_ntop(family, &ptr, PTR, stringBufferSize);
	}
};


void SettingTypeTable(int &tipoTablero)
{
	system("cls");

	cout << "> Tipo tablero Ta-Te-Ti:" << endl;
	cout << "> 1 - Numeros de Referencia" << endl;
	cout << "> 2 - Vacio" << endl;
	cout << "> Cualquier otro numero - Default" << endl;

	cin >> tipoTablero;
}
void InitData(int &countClientes, bool &mostrarBytesMensaje)
{
	int opcion = 0;
	cout << "Ingrese la cantidad de clientes: ";
	cin >> countClientes;
	cout << "Mostrar Informacion personal del cliente ?" << endl;
	cout << "1: Si." << endl;
	cout << "2: No." << endl;
	cout << "> ";
	cin >> opcion;
	while (opcion != 1 && opcion != 2)
	{
		system("cls");
		cout << "Error: Opcion Invalida!" << endl;
		cout << "Mostrar Informacion personal del cliente ?" << endl;
		cout << "1: Si." << endl;
		cout << "2: No." << endl;
		cout << "> ";
		cin >> opcion;
	}

	switch (opcion)
	{
	case 1:
		mostrarBytesMensaje = true;
		break;
	case 2:
		mostrarBytesMensaje = false;
		break;
	}
}
void ShowDataClient(ClientData client) 
{
	cout << "PESO del mensaje: " << client.bytesInClient << " bytes" << endl;
	cout << "IP del cliente: " << client.ip << endl;
	cout << "PUERTO del cliente: " << client.port << endl;
}
int main()
{

	int puerto = 8900;
	//const char* ipHaciaMiMismo = "127.0.0.1";
	int countClientes = 1;
	int tipoTablero = 0;
	int opcion = 0;
	bool mostrarBytesMensaje = true;

	InitData(countClientes, mostrarBytesMensaje);
	
	ClientData* clientes = new ClientData[countClientes];

	char ExitCharacter = '0';
	bool inGame = true;

	WSADATA data;
	WORD ver = MAKEWORD(2, 2);
	int wsOk = WSAStartup(ver, &data);
	if (wsOk != 0)
	{
		cerr << "No pudo iniciar winsock" << endl;
		cin.get();
		return -1;
	}

	SOCKET listening = socket(AF_INET, SOCK_DGRAM, 0);

	if (listening == INVALID_SOCKET)
	{
		cerr << "Invalid socket" << endl;
		cin.get();
		return -1;
	}

	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(puerto); 
	hint.sin_addr.S_un.S_addr = ADDR_ANY; 

	int bindResult = bind(listening, (sockaddr*)&hint, sizeof(hint));

	if (bindResult == SOCKET_ERROR)
	{
		cerr << "No pudo hacer el bind" << endl;
		cin.get();
		return -1;
	}

	

	for (int i = 0; i < countClientes; i++)
	{
		clientes[i].clientSize = sizeof(clientes[i].client);
		clientes[i].idClient = i;
	}
	
	SettingTypeTable(tipoTablero);

	Tablero* tablero = new Tablero(tipoTablero, 25, 10);
	system("cls");
	tablero->mostrarTablero(tablero->GetPosX(), tablero->GetPosY());

	while (inGame) {
		//funcion bloqueante.
		for (int i = 0; i < countClientes; i++)
		{
			cout << "Esperando Input..." << endl;
			clientes[i].bytesInClient = recvfrom(listening, (char*)&clientes[i].clientMessage, sizeof(clientes[i].clientMessage), 0, (sockaddr*)&clientes[i].client, &clientes[i].clientSize);
			if (clientes[i].bytesInClient == SOCKET_ERROR)
			{
				cerr << "Error al recibir data." << endl;
				return -1;
			}
			switch (clientes[i].clientMessage.cmd)
			{
			case 1:
				cout << "MENSAJE_JUGADA" << endl;
				break;
			case 2:
				cout << "MENSAJE_CHAT" << endl;
				break;
				
			}
			clientes[i].FindIp(AF_INET, &clientes[i].client.sin_addr, clientes[i].ip, 16);
			clientes[i].port = ntohs(clientes[i].client.sin_port);
			if (mostrarBytesMensaje)
			{
				ShowDataClient(clientes[i]);
			}
			if (clientes[i].clientMessage.data[0] == 'E' && clientes[i].clientMessage.data[1] == ':')
			{
				inGame = false;
			}
			//cout << buffer << endl;
			//sendto(listening, buffer, clientes[i].bytesInClient, 0, (sockaddr*)&clientes[i].client, sizeof(clientes[i].client));
		}
		
	}

	delete[] clientes;

	closesocket(listening);

	if (tablero != NULL) delete tablero;

	WSACleanup();

	return 0;
}