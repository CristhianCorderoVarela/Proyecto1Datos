#include <iostream>
#include "Tablero.h"

using namespace std;

int main()
{
	Tablero tablero;
	inicializarTablero(tablero);
	
	// Llenamos completamente la fila 5
	for (int columna = 0; columna < 10; columna++)
	{
		modificarCelda(tablero, 5, columna, 1);
	}
	
	cout << "TABLERO:" << endl;
	mostrarTablero(tablero);
	
	NodoFila *fila = tablero.inicio;
	
	for (int i = 0; i < 5; i++)
	{
		fila = fila->siguiente;
	}
	
	cout << endl;
	
	if (filaCompleta(fila))
	{
		cout << "La fila 5 esta completa." << endl;
	}
	else
	{
		cout << "La fila 5 NO esta completa." << endl;
	}
	
	liberarTablero(tablero);
	
	return 0;
}
