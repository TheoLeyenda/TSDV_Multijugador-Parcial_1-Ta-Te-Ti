/*
private:
	Tablero* _tablero;
	bool _gameOver;
	char _jugador1;
	char _jugador2;
public:
	Juego();
	~Juego();
	void init();
	void input();
	void update();
	void draw();
	void result();
	bool gameOver();
	void setGanador(int ganador);
	void play();

};
*/
#include "Juego.h"
Juego::Juego(){
	cout<<"Desea jugar con numeros de referencia o sin numeros de referencia ?"<<endl;
	cout<<"1.Con numeros de referencia"<<endl;
	cout<<"2.Sin numeros de referencia"<<endl;
	cout<<"opcion:";
	cin>>_opcion;
	_tablero = new Tablero(_opcion);
	system("cls");
}
Juego::~Juego(){
	if(_tablero!= NULL){
		delete _tablero;
	}
}
void Juego::setGanador(int ganador){
	_ganador = ganador;
}
void Juego::init(){
	_gameOver = false;
	_jugador1 = 'X';
	_jugador2 = 'O';
	_turno = 1;
	_ganador = '0';
	_gano = 0;
	_puntajeJ1 = 0;
	_puntajeJ2 = 0;
	_opcion = -1;
	_primerTurno = true;
}
void Juego::input(){
	int i;
	draw();
	cout<<endl<<endl;
	//cout<<"Turno de Jugador "<<_turno<<endl;
	if(_turno == 1){
		cout<<"Turno de "<<_jugador1<<endl;
	}
	if(_turno == 2){
		cout<<"Turno de "<<_jugador2<<endl;
	}
	cout<<"Coloque su figura:";
	cin>>i;
	if(_turno == 1){
		switch(i){
			case 1:
				_tablero->colocarJugador(0,0,_jugador1);
				break;
			case 2:
				_tablero->colocarJugador(1,0,_jugador1);
				break;
			case 3:
				_tablero->colocarJugador(2,0,_jugador1);
				break;
			case 4:
				_tablero->colocarJugador(0,1,_jugador1);
				break;
			case 5:
				_tablero->colocarJugador(1,1,_jugador1);
				break;
			case 6:
				_tablero->colocarJugador(2,1,_jugador1);
				break;
			case 7:
				_tablero->colocarJugador(0,2,_jugador1);
				break;
			case 8:
				_tablero->colocarJugador(1,2,_jugador1);
				break;
			case 9:
				_tablero->colocarJugador(2,2,_jugador1);
				break;
			default:
				_tablero->setRepetirTurno(true);
		}
	}
	if(_turno == 2){
		switch(i){
			case 1:
				_tablero->colocarJugador(0,0,_jugador2);
				break;
			case 2:
				_tablero->colocarJugador(1,0,_jugador2);
				break;
			case 3:
				_tablero->colocarJugador(2,0,_jugador2);
				break;
			case 4:
				_tablero->colocarJugador(0,1,_jugador2);
				break;
			case 5:
				_tablero->colocarJugador(1,1,_jugador2);
				break;
			case 6:
				_tablero->colocarJugador(2,1,_jugador2);
				break;
			case 7:
				_tablero->colocarJugador(0,2,_jugador2);
				break;
			case 8:
				_tablero->colocarJugador(1,2,_jugador2);
				break;
			case 9:
				_tablero->colocarJugador(2,2,_jugador2);
				break;
			default:
				_tablero->setRepetirTurno(true);
		}
	}
}
void Juego::update(){
	if(_tablero->getRepetirTurno()){
		if(_turno == 1){
			_turno = 1;
		}
		else{
			_turno = 2;
		}
		
	}
	else if(_primerTurno){
		if(_turno == 1 ){
			_turno = 2;
		}
		else{
			_turno = 1;
		}
		_primerTurno = false;
	}
	else if(!_tablero->getRepetirTurno()){
		if(_turno == 1 ){
			_turno = 2;
		}
		else{
			_turno = 1;
		}
	}
	_tablero->setRepetirTurno(false);
	_tablero->verificarEmpate();
	_tablero->verificarTaTeTi();
	_ganador = _tablero->getGanador();
	if(_ganador == 'X'){
		_gameOver = true;
		_gano = 1;
		_puntajeJ1++;
	}
	if(_ganador == 'O'){
		_gameOver = true;
		_gano = 2;
		_puntajeJ2++;
	}
	if(_ganador == 'N'){
		_gameOver = true;
	}
}
void Juego::draw(){
	gotoxy(15,1);
	cout<<"Jugador X: "<<_puntajeJ1;
	gotoxy(30,1);
	cout<<"Jugador O: "<<_puntajeJ2<<endl;
	_tablero->mostrarTablero();
}
void Juego::result(){
	system("cls");
	if(gameOver()){
		gotoxy(12,12);
		if(_ganador!= 'N'){
			cout<<"esta ronda la ha ganado el/la "<<_tablero->getGanador()<<endl<<endl<<endl;
		}
		if(_ganador == 'N'){
			gotoxy(22,12);
			cout<<"            Empate"<<endl<<endl<<endl;
		}
		cout<<"terminar Juego? si:1/no:0"<<endl;
		cout<<"opcion:";
		cin>>_opcion;
		if(_opcion == 0){
			system("cls");
			_gameOver = false;
			cout<<"Desea jugar con numeros de referencia o sin numeros de referencia ?"<<endl;
			cout<<"1.Con numeros de referencia"<<endl;
			cout<<"2.Sin numeros de referencia"<<endl;
			cout<<"opcion:";
			cin>>_opcion;
			_primerTurno = true;
			_tablero->reiniciarTablero(_opcion);
			_tablero->setGanador('0');
			_opcion = 0;
		}
		if(_opcion == 1){
			system("cls");
			gotoxy(20,8);
			cout<<"Jugador X: "<<_puntajeJ1;
			gotoxy(35,8);
			cout<<"Jugador O: "<<_puntajeJ2;
			if(_puntajeJ1>_puntajeJ2){
				gotoxy(15,12);
				cout<<"El Jugador X ha ganado con "<<_puntajeJ1<<" puntos";
			}
			if(_puntajeJ2>_puntajeJ1){
				gotoxy(15,12);
				cout<<"El Jugador O ha ganado con "<<_puntajeJ2<<" puntos";
			}
			if(_puntajeJ1 == _puntajeJ2){
				gotoxy(17,12);
				cout<<"Los dos jugadores han empatado con "<<_puntajeJ1<<" puntos";
			}
			cout<<endl<<endl<<"Gracias por usar el programa....";
			cin.get();
			cin.get();
		}
	}
}
bool Juego::gameOver(){
	return _gameOver;
}
void Juego::play(){
	//completar.(hacer el gameloop).
	init();
	while(!gameOver()){
		input();
		update();
		draw();
		result();
		system("cls");
	}
}