/*
private:
	char _tablero[3][3];
public:
	Tablero();
	void mostrarTablero(); //muestra como esta el tablero y a los jugadores que estan en el(O,X).
	void colocarJugador(int fila, int columna, char jugador); //recorre el arreglo y coloca una X o un O dependiendo del jugador.
	void reiniciarTablero(); //inicializa el arreglo a 'i' en un for.
	void verificarTaTeTi(); //se fija si un jugador hizo ta-te-ti, si hizo ta-te-ti retorna true, sino retorna false.
	char getCasilla(int fila, int columna);//retorna lo que hay en la casilla del tablero
	char getGanador();
	void setGanador(char ganador);

};
*/
#include "Tablero.h"
#include "../../Librerias gentille/Libreria.h"
Tablero::Tablero(int tipo, float x, float y){
	for(int i = 0; i<MAX_FIL; i++){
		for(int j = 0; j<MAX_COL; j++){
			_tablero[i][j] = '0';
		}
	}
	if(tipo == 1){
		_tablero[0][0] = '1';
		_tablero[1][0] = '2';
		_tablero[2][0] = '3';
		_tablero[0][1] = '4';
		_tablero[1][1] = '5';
		_tablero[2][1] = '6';
		_tablero[0][2] = '7';
		_tablero[1][2] = '8';
		_tablero[2][2] = '9';
	}
	else if(tipo == 2){
		_tablero[0][0] = ' ';
		_tablero[1][0] = ' ';
		_tablero[2][0] = ' ';
		_tablero[0][1] = ' ';
		_tablero[1][1] = ' ';
		_tablero[2][1] = ' ';
		_tablero[0][2] = ' ';
		_tablero[1][2] = ' ';
		_tablero[2][2] = ' ';
	}
	else if(tipo!= 2 && tipo!= 1){
		_tablero[0][0] = '0';
		_tablero[1][0] = '0';
		_tablero[2][0] = '0';
		_tablero[0][1] = '0';
		_tablero[1][1] = '0';
		_tablero[2][1] = '0';
		_tablero[0][2] = '0';
		_tablero[1][2] = '0';
		_tablero[2][2] = '0';
	}
	_ganador = '0';
	_repetirTurno = false;
	_posX = x;
	_posY = y;
	//Listo
}
void Tablero::mostrarTablero(float x,float y){
	gotoxy(x -5, y - 2);
	cout<<"--- TA TE TI ---"<<endl;
	gotoxy(x, y);
	cout<<_tablero[0][0]<<"|"<<_tablero[1][0]<<"|"<<_tablero[2][0]<<endl;
	gotoxy(x, y + 1);
	cout<<"-----"<<endl;
	gotoxy(x, y + 2);
	cout<<_tablero[0][1]<<"|"<<_tablero[1][1]<<"|"<<_tablero[2][1]<<endl;
	gotoxy(x, y + 3);
	cout<<"-----"<<endl;
	gotoxy(x, y + 4);
	cout<<_tablero[0][2]<<"|"<<_tablero[1][2]<<"|"<<_tablero[2][2]<<endl;
	gotoxy(x - 5, y + 6);
	cout << "----------------" << endl;
	//Listo
}
void Tablero::colocarJugador(int fila, int columna, char jugador){
	if(fila>=0 && fila<4 && columna>=0 && columna<4){
		if(_tablero[fila][columna] == '1' || _tablero[fila][columna] == '2' || _tablero[fila][columna] == '3'|| _tablero[fila][columna] == '4'|| _tablero[fila][columna] == '5'|| _tablero[fila][columna] == '6'|| _tablero[fila][columna] == '7'|| _tablero[fila][columna] == '8'|| _tablero[fila][columna] == '9' || _tablero[fila][columna] == ' '){
			_tablero[fila][columna] = jugador;
		}
		else{
			_repetirTurno = true;
		}
	}
	else{
		_repetirTurno = true;
	}
}
void Tablero::reiniciarTablero(int tipo){
	if(tipo == 1){
		_tablero[0][0] = '1';
		_tablero[1][0] = '2';
		_tablero[2][0] = '3';
		_tablero[0][1] = '4';
		_tablero[1][1] = '5';
		_tablero[2][1] = '6';
		_tablero[0][2] = '7';
		_tablero[1][2] = '8';
		_tablero[2][2] = '9';
	}
	else if(tipo == 2){
		_tablero[0][0] = ' ';
		_tablero[1][0] = ' ';
		_tablero[2][0] = ' ';
		_tablero[0][1] = ' ';
		_tablero[1][1] = ' ';
		_tablero[2][1] = ' ';
		_tablero[0][2] = ' ';
		_tablero[1][2] = ' ';
		_tablero[2][2] = ' ';
	}
	else if(tipo!= 2 && tipo!= 1){
		_tablero[0][0] = '0';
		_tablero[1][0] = '0';
		_tablero[2][0] = '0';
		_tablero[0][1] = '0';
		_tablero[1][1] = '0';
		_tablero[2][1] = '0';
		_tablero[0][2] = '0';
		_tablero[1][2] = '0';
		_tablero[2][2] = '0';
	}
}
void Tablero::verificarTaTeTi(){
	if(_tablero[0][0] == 'X' && _tablero[1][0] == 'X' && _tablero[2][0]== 'X'){
		setGanador('X');
	}
	if(_tablero[0][0] == 'O' && _tablero[1][0] == 'O' && _tablero[2][0]== 'O'){
		setGanador('O');
	}
	if(_tablero[0][0] == 'X' && _tablero[1][1] == 'X' && _tablero[2][2]== 'X'){
		setGanador('X');
	}
	if(_tablero[0][0] == 'O' && _tablero[1][1] == 'O' && _tablero[2][2]== 'O'){
		setGanador('O');
	}
	if(_tablero[2][0] == 'X' && _tablero[1][1] == 'X' && _tablero[0][2]== 'X'){
		setGanador('X');
	}
	if(_tablero[2][0] == 'O' && _tablero[1][1] == 'O' && _tablero[0][2]== 'O'){
		setGanador('O');
	}
	if(_tablero[0][0] == 'X' && _tablero[0][1] == 'X' && _tablero[0][2] == 'X'){
		setGanador('X');
	}
	if(_tablero[0][0] == 'O' && _tablero[0][1] == 'O' && _tablero[0][2] == 'O'){
		setGanador('O');
	}
	if(_tablero[0][1] == 'X' && _tablero[1][1] == 'X' && _tablero[2][1] == 'X'){
		setGanador('X');
	}
	if(_tablero[0][1] == 'O' && _tablero[1][1] == 'O' && _tablero[2][1] == 'O'){
		setGanador('O');
	}
	if(_tablero[0][2] == 'X' && _tablero[1][2] == 'X' && _tablero[2][2] == 'X'){
		setGanador('X');
	}
	if(_tablero[0][2] == 'O' && _tablero[1][2] == 'O' && _tablero[2][2] == 'O'){
		setGanador('O');
	}
	if(_tablero[1][0] == 'X' && _tablero[1][1] == 'X' && _tablero[1][2] == 'X'){
		setGanador('X');
	}
	if(_tablero[1][0] == 'O' && _tablero[1][1] == 'O' && _tablero[1][2] == 'O'){
		setGanador('O');
	}
	if(_tablero[2][0] == 'X' && _tablero[2][1] == 'X' && _tablero[2][2] == 'X'){
		setGanador('X');
	}
	if(_tablero[2][0] == 'O' && _tablero[2][1] == 'O' && _tablero[2][2] == 'O'){
		setGanador('O');
	}
}
char Tablero::getCasilla(int fila, int columna){
	return _tablero[fila][columna];
}
char Tablero::getGanador(){
	return _ganador;
}
void Tablero::setGanador(char ganador){
	_ganador = ganador;
}
void Tablero::verificarEmpate(){
	int contador = 0;
	for(int i = 0; i<MAX_FIL; i++){
		for(int j = 0; j<MAX_COL; j++){
			if(_tablero[i][j] == 'X' || _tablero[i][j] == 'O'){
				contador++;
			}
		}
	}
	if(contador == 9){
		_ganador = 'N';
	}
}
void Tablero::setRepetirTurno(bool repetirTurno){
	_repetirTurno = repetirTurno;
}
bool Tablero::getRepetirTurno(){
	return _repetirTurno;
}

float Tablero::GetPosX() 
{
	return _posX;
}
float Tablero::GetPosY() 
{
	return _posY;
}