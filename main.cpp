#include <iostream>
#include "Tablero.h"

using namespace std;

int main()
{
	Tablero tablero;
	
	inicializarTablero(tablero);
	
	cout << "TABLERO:" << endl;
	cout << endl;
	
	mostrarTablero(tablero);
	
	liberarTablero(tablero);
	
	return 0;
}
