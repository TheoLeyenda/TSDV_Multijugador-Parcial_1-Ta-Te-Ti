#include "Server.h"

int main() 
{
	Server* server = new Server(9000);

	server->Initialize();
	server->BindSocket();
	server->ListenForMessages();
	server->Shutdown();

	delete server;

	return 0;
}