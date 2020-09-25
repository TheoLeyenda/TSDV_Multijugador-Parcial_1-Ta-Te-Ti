#include "Juego.h"
#include <stdio.h>
#include <windows.h>
Juego::Juego(float x, float y)
{
	int tipo = 0;
	cout << "Ingrese el tipo de tablero:" << endl;
	cout << "> 1.Numeros De Referencia." << endl;
	cout << "> 2.Sin Numeros" << endl;
	cout << "> Cualquier numero: TABLERO DEFAULT" << endl;
	cout << "Opcion:";
	cin >> tipo;
	
	_tablero = new Tablero(tipo, x, y);
	do {
		system("cls");
		cout << "Ingrese como quiere ver su ficha:";
		cin >> tuEquipo;
		cout << "Ingrese como quiere ver la ficha de su enemigo:";
		cin >> equipoEnemigo;
	} while (tuEquipo == equipoEnemigo);
	EnJuego = true;
	_cliente = NULL;
	CrearUsuario();
	if (_cliente != NULL) {
		std::string aux = "Input Console - " + _cliente->GetAlias();
		Raylib::InitWindow(screenWidth, screenHeight, aux.c_str());
	}
	else 
	{
		Raylib::InitWindow(screenWidth, screenHeight, "Input Console");
	}
	Raylib::SetTargetFPS(60);
	system("cls");
}


Juego::~Juego()
{
	if (_tablero != NULL) 
	{
		delete _tablero;
	}
}

void Juego::DibujarTablero()
{
	_tablero->mostrarTablero(_tablero->GetPosX(), _tablero->GetPosY());
}



void Juego::DibujarJugador(int input, int dibujo)
{
	switch (dibujo)
	{
	case Juego::contrincante:
		Dibujar(equipoEnemigo, input);
		break;
	case Juego::jugador:
		Dibujar(tuEquipo, input);
		break;
	}
}

void Juego::Dibujar(char jugador, int input)
{
	switch (input)
	{
	case 1:
		_tablero->colocarJugador(0, 0, jugador);
		break;
	case 2:
		_tablero->colocarJugador(1, 0, jugador);
		break;
	case 3:
		_tablero->colocarJugador(2, 0, jugador);
		break;
	case 4:
		_tablero->colocarJugador(0, 1, jugador);
		break;
	case 5:
		_tablero->colocarJugador(1, 1, jugador);
		break;
	case 6:
		_tablero->colocarJugador(2, 1, jugador);
		break;
	case 7:
		_tablero->colocarJugador(0, 2, jugador);
		break;
	case 8:
		_tablero->colocarJugador(1, 2, jugador);
		break;
	case 9:
		_tablero->colocarJugador(2, 2, jugador);
		break;
	}
}



void Juego::CrearUsuario()
{
	if (_cliente == NULL) {
		_cliente = new Client(8900);
		_cliente->Initialize();
	}
}

void Juego::DestruirUsuario()
{
	if (_cliente != NULL) 
	{
		_cliente->Shutdown();
		cout << "Cliente Destruido" << endl;
		cin.get();
		delete _cliente;
	}
}


void Juego::UpdateUsuario()
{
	_cliente->SendMSG();
	_cliente->ListenForMessages();
	_cliente->ShowLocationClient();
	DibujarTablero();
	_cliente->ShowAlias(0,12);
	//bool buscarPartida = false;
	while (EnJuego)
	{
		Raylib::BeginDrawing();

		Raylib::ClearBackground(Raylib::RAYWHITE);
		if (_cliente->GetGameState() == Client::ClientMenssage::GameState::None) 
		{
			if (_cliente->GetIsMenu()) {
				if (!firstOnceInGame)
				{
					_cliente->ShowLocationClient();
					if (Raylib::IsKeyPressed(Raylib::KEY_ONE) /*|| buscarPartida*/)
					{
						_cliente->SendMSG();
						_cliente->ListenForMessages();
						//buscarPartida = true;
					}
					if (Raylib::IsKeyPressed(Raylib::KEY_TWO))
					{
						EnJuego = false;
					}
				}
			}
			else 
			{
				_cliente->SendMSG();
				_cliente->ListenForMessages();
			}
		}
		if (_cliente->GetGameState() == Client::ClientMenssage::GameState::InLobby)
		{
			_cliente->SendMSG();
			_cliente->ListenForMessages();
		}
		else if (_cliente->GetGameState() == Client::ClientMenssage::GameState::WaitMyTurn)
		{
			//gotoxy(50, 30);
			//cout << "ME TRABE OWO" << endl;
			if (_cliente->GetIsFirstMove())
			{
				_cliente->SetIsFirstMove(false);
				//_cliente->ListenForMessages();
				DibujarTablero();
				_cliente->ShowAlias(0, 12);
			}
			_cliente->SetCMD(0);
			//_cliente->SendMSG();
			_cliente->ListenOtherMassages(false);

			//gotoxy(50, 30);
			//cout << "ME RESPONDIO UWU" << endl;
			switch (_cliente->GetCMD())
			{
			case 1:
				DibujarJugador(1, Juego::contrincante);
				DibujarTablero();
				_cliente->SetTurn(true);
				_cliente->SetGameState(Client::ClientMenssage::GameState::InGame);
				_cliente->SendMSG();
				_cliente->ListenForMessages();
				_cliente->SetCMD(0);
				break;
			case 2:
				DibujarJugador(2, Juego::contrincante);
				DibujarTablero();
				_cliente->SetTurn(true);
				_cliente->SetGameState(Client::ClientMenssage::GameState::InGame);
				_cliente->SendMSG();
				_cliente->ListenForMessages();
				_cliente->SetCMD(0);
				break;
			case 3:
				DibujarJugador(3, Juego::contrincante);
				DibujarTablero();
				_cliente->SetTurn(true);
				_cliente->SetGameState(Client::ClientMenssage::GameState::InGame);
				_cliente->SendMSG();
				_cliente->ListenForMessages();
				_cliente->SetCMD(0);
				break;
			case 4:
				DibujarJugador(4, Juego::contrincante);
				DibujarTablero();
				_cliente->SetTurn(true);
				_cliente->SetGameState(Client::ClientMenssage::GameState::InGame);
				_cliente->SendMSG();
				_cliente->ListenForMessages();
				_cliente->SetCMD(0);
				break;
			case 5:
				DibujarJugador(5, Juego::contrincante);
				DibujarTablero();
				_cliente->SetTurn(true);
				_cliente->SetGameState(Client::ClientMenssage::GameState::InGame);
				_cliente->SendMSG();
				_cliente->ListenForMessages();
				_cliente->SetCMD(0);
				break;
			case 6:
				DibujarJugador(6, Juego::contrincante);
				DibujarTablero();
				_cliente->SetTurn(true);
				_cliente->SetGameState(Client::ClientMenssage::GameState::InGame);
				_cliente->SendMSG();
				_cliente->ListenForMessages();
				_cliente->SetCMD(0);
				break;
			case 7:
				DibujarJugador(7, Juego::contrincante);
				DibujarTablero();
				_cliente->SetTurn(true);
				_cliente->SetGameState(Client::ClientMenssage::GameState::InGame);
				_cliente->SendMSG();
				_cliente->ListenForMessages();
				_cliente->SetCMD(0);
				break;
			case 8:
				DibujarJugador(8, Juego::contrincante);
				DibujarTablero();
				_cliente->SetTurn(true);
				_cliente->SetGameState(Client::ClientMenssage::GameState::InGame);
				_cliente->SendMSG();
				_cliente->ListenForMessages();
				_cliente->SetCMD(0);
				break;
			case 9:
				DibujarJugador(9, Juego::contrincante);
				DibujarTablero();
				_cliente->SetTurn(true);
				_cliente->SetGameState(Client::ClientMenssage::GameState::InGame);
				_cliente->SendMSG();
				_cliente->ListenForMessages();
				_cliente->SetCMD(0);
				break;
			}
		}
		else if (_cliente->GetGameState() == Client::ClientMenssage::GameState::InGame)
		{
			if (_cliente->GetIsFirstMove()) 
			{
				_cliente->SetIsFirstMove(false);
				//_cliente->ListenForMessages();
				DibujarTablero();
				_cliente->ShowAlias(0, 12);
			}
			//gotoxy(50, 22);
			//cout << "ENTRE AL IN_GAME" << endl;
			if (Raylib::IsKeyPressed(Raylib::KEY_ONE) && _cliente->GetTurn())
			{
				//gotoxy(50, 23);
				//cout << "ENTRE AL CLICK" << endl;
				_cliente->SetInput(1);
				_cliente->SendMSG();
				_cliente->ListenForMessages();
				
				if (_cliente->GetCMD() == 1)
				{
					//gotoxy(50, 24);
					//cout << "ENTRE AL CMD" << endl;
					DibujarJugador(1, Juego::jugador);
					DibujarTablero();
					_cliente->SetTurn(false);
					_cliente->SetGameState(Client::ClientMenssage::GameState::WaitMyTurn);
					_cliente->SendMSG();
					_cliente->ListenForMessages();
					_cliente->SetCMD(0);
				}
			}
			if (Raylib::IsKeyPressed(Raylib::KEY_TWO) && _cliente->GetTurn())
			{
				_cliente->SetInput(2);
				_cliente->SendMSG();
				_cliente->ListenForMessages();
				if (_cliente->GetCMD() == 2)
				{
					DibujarJugador(2, Juego::jugador);
					DibujarTablero();
					_cliente->SetTurn(false);
					_cliente->SetGameState(Client::ClientMenssage::GameState::WaitMyTurn);
					_cliente->SendMSG();
					_cliente->ListenForMessages();
					_cliente->SetCMD(0);
				}
			}
			if (Raylib::IsKeyPressed(Raylib::KEY_THREE) && _cliente->GetTurn())
			{
				_cliente->SetInput(3);
				_cliente->SendMSG();
				_cliente->ListenForMessages();
				if (_cliente->GetCMD() == 3)
				{
					DibujarJugador(3, Juego::jugador);
					DibujarTablero();
					_cliente->SetTurn(false);
					_cliente->SetGameState(Client::ClientMenssage::GameState::WaitMyTurn);
					_cliente->SendMSG();
					_cliente->ListenForMessages();
					_cliente->SetCMD(0);
				}
			}
			if (Raylib::IsKeyPressed(Raylib::KEY_FOUR) && _cliente->GetTurn())
			{
				_cliente->SetInput(4);
				_cliente->SendMSG();
				_cliente->ListenForMessages();
				if (_cliente->GetCMD() == 4)
				{
					DibujarJugador(4, Juego::jugador);
					DibujarTablero();
					_cliente->SetTurn(false);
					_cliente->SetGameState(Client::ClientMenssage::GameState::WaitMyTurn);
					_cliente->SendMSG();
					_cliente->ListenForMessages();
					_cliente->SetCMD(0);
				}
			}
			if (Raylib::IsKeyPressed(Raylib::KEY_FIVE) && _cliente->GetTurn())
			{
				_cliente->SetInput(5);
				_cliente->SendMSG();
				_cliente->ListenForMessages();
				if (_cliente->GetCMD() == 5)
				{
					DibujarJugador(5, Juego::jugador);
					DibujarTablero();
					_cliente->SetTurn(false);
					_cliente->SetGameState(Client::ClientMenssage::GameState::WaitMyTurn);
					_cliente->SendMSG();
					_cliente->ListenForMessages();
					_cliente->SetCMD(0);
				}
			}
			if (Raylib::IsKeyPressed(Raylib::KEY_SIX) && _cliente->GetTurn())
			{
				_cliente->SetInput(6);
				_cliente->SendMSG();
				_cliente->ListenForMessages();
				if (_cliente->GetCMD() == 6)
				{
					DibujarJugador(6, Juego::jugador);
					DibujarTablero();
					_cliente->SetTurn(false);
					_cliente->SetGameState(Client::ClientMenssage::GameState::WaitMyTurn);
					_cliente->SendMSG();
					_cliente->ListenForMessages();
					_cliente->SetCMD(0);
				}
			}
			if (Raylib::IsKeyPressed(Raylib::KEY_SEVEN) && _cliente->GetTurn())
			{
				_cliente->SetInput(7);
				_cliente->SendMSG();
				_cliente->ListenForMessages();
				if (_cliente->GetCMD() == 7)
				{
					DibujarJugador(7, Juego::jugador);
					DibujarTablero();
					_cliente->SetTurn(false);
					_cliente->SetGameState(Client::ClientMenssage::GameState::WaitMyTurn);
					_cliente->SendMSG();
					_cliente->ListenForMessages();
					_cliente->SetCMD(0);
				}
			}
			if (Raylib::IsKeyPressed(Raylib::KEY_EIGHT) && _cliente->GetTurn())
			{
				_cliente->SetInput(8);
				_cliente->SendMSG();
				_cliente->ListenForMessages();
				if (_cliente->GetCMD() == 8)
				{
					DibujarJugador(8, Juego::jugador);
					DibujarTablero();
					_cliente->SetTurn(false);
					_cliente->SetGameState(Client::ClientMenssage::GameState::WaitMyTurn);
					_cliente->SendMSG();
					_cliente->ListenForMessages();
					_cliente->SetCMD(0);
				}
			}
			if (Raylib::IsKeyPressed(Raylib::KEY_NINE) && _cliente->GetTurn())
			{
				_cliente->SetInput(9);
				_cliente->SendMSG();
				_cliente->ListenForMessages();
				if (_cliente->GetCMD() == 9)
				{
					DibujarJugador(9, Juego::jugador);
					DibujarTablero();
					_cliente->SetTurn(false);
					_cliente->SetGameState(Client::ClientMenssage::GameState::WaitMyTurn);
					_cliente->SendMSG();
					_cliente->ListenForMessages();
					_cliente->SetCMD(0);

				}
			}
		}
		else if (_cliente->GetGameState() == Client::ClientMenssage::GameState::Win) 
		{
			ResultGame(Raylib::IsKeyPressed(Raylib::KEY_ONE), Raylib::IsKeyPressed(Raylib::KEY_TWO), _cliente->GetGameState());
		}
		else if (_cliente->GetGameState() == Client::ClientMenssage::GameState::Lose)
		{
			ResultGame(Raylib::IsKeyPressed(Raylib::KEY_ONE), Raylib::IsKeyPressed(Raylib::KEY_TWO), _cliente->GetGameState());
		}
		else if (_cliente->GetGameState() == Client::ClientMenssage::GameState::Tie)
		{
			ResultGame(Raylib::IsKeyPressed(Raylib::KEY_ONE), Raylib::IsKeyPressed(Raylib::KEY_TWO), _cliente->GetGameState());
		}
		VerificarTablero();
		Raylib::EndDrawing();

	}
	Raylib::CloseWindow();
}

void Juego::VerificarTablero()
{
	_tablero->verificarTaTeTi(tuEquipo, equipoEnemigo);
	if (_tablero->getGanador() != tuEquipo && _tablero->getGanador() != equipoEnemigo)
	{
		_tablero->verificarEmpate(tuEquipo, equipoEnemigo);
		if (_tablero->getGanador() == 'N') 
		{
			_cliente->SetGameState(Client::ClientMenssage::GameState::Tie);
		}
	}
	else if (_tablero->getGanador() == tuEquipo)
	{
		_cliente->SetGameState(Client::ClientMenssage::GameState::Win);
	}
	else if (_tablero->getGanador() == equipoEnemigo) 
	{
		_cliente->SetGameState(Client::ClientMenssage::GameState::Lose);
	}
}

void Juego::ResultGame(bool inputPositivo, bool inputNegativo, Client::ClientMenssage::GameState gameState)
{
	//FUNCION QUE FALTA TERMINAR
	if (_cliente != NULL)
	{
		_cliente->ShowLocationClient();
		_cliente->ResetAuxMSG();
		int x = 25;
		int y = 20;

		gotoxy(x,y);
		cout << "Desea volver a jugar?" << endl;
		gotoxy(x, y+1);
		cout << "> 1 - Si" << endl;
		gotoxy(x, y + 2);
		cout << "> 2 - No" << endl;
		if (inputPositivo) 
		{
			_cliente->ResetCMD();
			_cliente->ResetPosicionesTablero();
			_cliente->ResetInput();
			_tablero->reiniciarTablero(_tablero->GetTipoTablero());
			DibujarTablero();
			_tablero->setGanador('-');
			_cliente->SetInput(10);
			_cliente->SendMSG();
			//_cliente->ListenForMessages();

			gotoxy(x, y);
			cout << "                         " << endl;
			gotoxy(x, y+1);
			cout << "                         " << endl;
			gotoxy(x, y+2);
			cout << "                         " << endl;
			gotoxy(x, y);
			cout << "Esperando respuesta del otro jugador..." << endl;
			_cliente->ListenOtherMassages(true);
			//cout << "                         " << endl;
			//cout << "GameState: " << _cliente->GetGameState() << endl;
			gotoxy(x, y);
			if (_cliente->GetCMD() == 15) 
			{
				cout << "Esperando respuesta del otro jugador..." << endl;
				_cliente->ListenOtherMassages(true);
			}
			gotoxy(x, y);
			cout << "                                                        " << endl;
			if (_cliente->GetCMD() == 13) 
			{
				//gotoxy(x, y);
				cout << "IN LOBBY" << endl;
				_cliente->ResetMSG();
				_cliente->SetGameState(Client::ClientMenssage::GameState::None);
				_cliente->SetIsMenu(false);
				_cliente->ShowLocationClient();
			}
			//gotoxy(x, y+2);
			//cout << "                         " << endl;
			//cout << "GameState: "<<_cliente->GetGameState() << endl;
			//cin.get();
			//gotoxy(x, y + 5);
			//cout << "                                           " << endl;

		}
		if (inputNegativo) 
		{

			gotoxy(x, y);
			cout << "                         " << endl;
			gotoxy(x, y + 1);
			cout << "                         " << endl;
			gotoxy(x, y + 2);
			cout << "                         " << endl;
			gotoxy(x, y);

			_cliente->SetInput(11);
			_cliente->SendMSG();
			_cliente->ListenForMessages();

			gotoxy(x, y);
			cout << "                                                        " << endl;
			gotoxy(x, y);
			cout << "Volviendo al loby..." << endl;
			miliSleep(3000);
			_cliente->ResetMSG();
			_cliente->SetIsMenu(true);
			_tablero->reiniciarTablero(_tablero->GetTipoTablero());
			DibujarTablero();
			_tablero->setGanador('-');
			_cliente->SetGameState(Client::ClientMenssage::GameState::None);
			gotoxy(x, y);
			cout << "                     " << endl;
		}
		firstOnceInGame = false;
	}

}

void Juego::SetID(int id)
{
	_id = id;
}
