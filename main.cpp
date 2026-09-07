#include <iostream>
#include "Pieza.h"

using namespace std;

void mostrarForma(Pieza pieza)
{
	int bloques[4][2];
	
	obtenerBloques(pieza, bloques);
	
	char forma[4][4];
	
	// Llenamos el espacio con puntos
	for (int fila = 0; fila < 4; fila++)
	{
		for (int columna = 0; columna < 4; columna++)
		{
			forma[fila][columna] = '.';
		}
	}
	
	// Colocamos los 4 bloques de la pieza
	for (int i = 0; i < 4; i++)
	{
		int filaRelativa = bloques[i][0] - pieza.fila;
		int columnaRelativa = bloques[i][1] - pieza.columna;
		
		if (filaRelativa >= 0 && filaRelativa < 4 &&
			columnaRelativa >= 0 && columnaRelativa < 4)
		{
			forma[filaRelativa][columnaRelativa] = pieza.tipo;
		}
	}
	
	// Mostrar la forma
	for (int fila = 0; fila < 4; fila++)
	{
		for (int columna = 0; columna < 4; columna++)
		{
			cout << forma[fila][columna] << " ";
		}
		
		cout << endl;
	}
}

int main()
{
	char tipos[7] = {'I', 'O', 'T', 'S', 'Z', 'J', 'L'};
	
	for (int p = 0; p < 7; p++)
	{
		Pieza pieza;
		
		inicializarPieza(pieza, tipos[p]);
		
		cout << "====================" << endl;
		cout << "PIEZA " << pieza.tipo << endl;
		cout << "====================" << endl;
		
		for (int orientacion = 0; orientacion < 4; orientacion++)
		{
			pieza.orientacion = orientacion;
			
			cout << endl;
			cout << "Orientacion " << orientacion << ":" << endl;
			
			mostrarForma(pieza);
		}
		
		cout << endl;
	}
	
	return 0;
}
