#include <iostream>
#include <WS2tcpip.h>
#include "../../TaTeTi_Libs/TA-TE-TI/Tablero.h"
#include "../../Librerias gentille/Libreria.h"
#include <stdlib.h>
#include <time.h>
#pragma comment(lib, "ws2_32.lib")

#define TAM_MENSAJE 1500
#define LIMITE_INFERIOR  1
#define LIMITE_SUPERIOR  2
using namespace std;

struct ClientMessage
{
public:
	char jugada;
	byte cmd;
	char data[TAM_MENSAJE];
	bool inWait;
};
struct ServerRequest 
{
public:
	byte cmd;
	Tablero *tablero;
	char messenge[TAM_MENSAJE] = { "Turno del oponente, por favor espere..." };
};

struct ClientData
{
public:
	char player;
	int numberPlayer;
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
	do {
		system("cls");
		cout << "Ingrese la cantidad de clientes: ";
		cin >> countClientes;
		if (countClientes % 2 != 0) 
		{
			cout << "cantidad invalida, ingrese una cantidad par..." << endl;
			cin.get();
			cin.get();
		}
	} while (countClientes % 2 != 0);
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
bool CheckMove(ClientData &client, int &turno, Tablero* tablero)
{
	if (tablero == NULL) return false;
	cout << "Entre al CheckMove" << endl;
	bool enableMove = false;
	if (client.numberPlayer == turno)
	{
		cout << "Es mi turno" << endl;
		enableMove = true;
		if (turno == 1) 
		{
			turno = 2;
		}
		else if(turno == 2)
		{
			turno = 1;
		}
		switch (client.clientMessage.jugada)
		{
		case '1':
			cout << "1" << endl;
			tablero->colocarJugador(0, 0, client.player);
			break;
		case '2':
			cout << "2" << endl;
			tablero->colocarJugador(1, 0, client.player);
			break;
		case '3':
			cout << "3" << endl;
			tablero->colocarJugador(2, 0, client.player);
			break;
		case '4':
			cout << "4" << endl;
			tablero->colocarJugador(0, 1, client.player);
			break;
		case '5':
			cout << "5" << endl;
			tablero->colocarJugador(1, 1, client.player);
			break;
		case '6':
			cout << "6" << endl;
			tablero->colocarJugador(2, 1, client.player);
			break;
		case '7':
			cout << "7" << endl;
			tablero->colocarJugador(0, 2, client.player);
			break;
		case '8':
			cout << "8" << endl;
			tablero->colocarJugador(1, 2, client.player);
			break;
		case '9':
			cout << "9" << endl;
			tablero->colocarJugador(2, 2, client.player);
			break;
		}
	}
	tablero->mostrarTablero(tablero->GetPosX(), tablero->GetPosY());
	return enableMove;
}
void InitPlayers(ClientData &client_1, ClientData &client_2) 
{
	// limite_inferior + rand() % (limite_superior +1 - limite_inferior) ;
	
	int randomPlayer = LIMITE_INFERIOR + rand() % (LIMITE_SUPERIOR + 1 - LIMITE_INFERIOR);
	client_1.numberPlayer = 1;
	client_2.numberPlayer = 2;
	switch (randomPlayer)
	{
	case 1:
		client_1.player = 'O';
		client_2.player = 'X';
		break;
	case 2:
		client_1.player = 'X';
		client_2.player = 'O';
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
	int turno = LIMITE_INFERIOR + rand() % (LIMITE_SUPERIOR + 1 - LIMITE_INFERIOR);
	srand(time(NULL));
	int puerto = 8900;
	//const char* ipHaciaMiMismo = "127.0.0.1";
	int countClientes = 1;
	int tipoTablero = 0;
	int opcion = 0;
	bool mostrarBytesMensaje = true;
	bool enableMove = true;
	InitData(countClientes, mostrarBytesMensaje);
	
	ServerRequest serverRequest;
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
		cin.get();
		return -1;
	}

	SOCKET listening = socket(AF_INET, SOCK_DGRAM, 0);

	if (listening == INVALID_SOCKET)
	{
		cerr << "Invalid socket" << endl;
		cin.get();
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
		cin.get();
		return -1;
	}

	
	//CREO ESPACIO PARA QUE ENTREN CLIENTES//
	for (int i = 0; i < countClientes; i++)
	{
		clientes[i].clientSize = sizeof(clientes[i].client);
		clientes[i].idClient = i;

	}
	//INICIALIZO LA ENTRADA DE LOS CLIENTES//
	for (int i = 0; i < countClientes - 1; i = i + 2) 
	{
		InitPlayers(clientes[i], clientes[i + 1]);
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
				cin.get();
				cin.get();
				return -1;
			}
			//RESPONDO AL CLIENTE
			cout << clientes[i].clientMessage.cmd << endl;
			switch (clientes[i].clientMessage.cmd)
			{
			case 1:
				cout << "MENSAJE_JUGADA" << endl;
				cout << "Jugada:"<<clientes[i].clientMessage.jugada << endl;
				cout << "Numero jugador:" << clientes[i].numberPlayer << endl;
				cout << "turno: " << turno << endl;
				enableMove = CheckMove(clientes[i], turno, tablero);
				if (!enableMove) 
				{
					serverRequest.cmd = 1;
					//cout << "INFORME AL JUGADOR QUE NO ES SU TURNO" << endl;
					
				}
				else 
				{
					serverRequest.cmd = 2;
					serverRequest.tablero = tablero;
					//ENVIAR EL TA TE TI;
				}
				break;
			case 2:
				cout << "MENSAJE_CHAT" << endl;
				serverRequest.cmd = 3;
				break;
				
			}
			sendto(listening, (char*)&serverRequest, sizeof(serverRequest), 0, (sockaddr*)&clientes[i].client, sizeof(clientes[i].client));
			//----------------------//

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