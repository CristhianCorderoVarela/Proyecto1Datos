#include <iostream>
#include "Tablero.h"

using namespace std;

int main()
{
	Tablero tablero;
	inicializarTablero(tablero);
	
	// Algunas piezas en la fila 17
	modificarCelda(tablero, 17, 3, 1);
	modificarCelda(tablero, 17, 4, 1);
	modificarCelda(tablero, 17, 5, 1);
	
	// Llenamos completamente las filas 18 y 19
	for (int columna = 0; columna < 10; columna++)
	{
		modificarCelda(tablero, 18, columna, 1);
		modificarCelda(tablero, 19, columna, 1);
	}
	
	cout << "ANTES DE LIMPIAR:" << endl;
	mostrarTablero(tablero);
	
	int eliminadas = eliminarFilasCompletas(tablero);
	
	cout << endl;
	cout << "Filas eliminadas: " << eliminadas << endl;
	
	cout << endl;
	cout << "DESPUES DE LIMPIAR:" << endl;
	mostrarTablero(tablero);
	
	liberarTablero(tablero);
	
	return 0;
}
