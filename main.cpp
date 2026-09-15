#include <iostream>

#include "Tablero.h"
#include "Pieza.h"
#include "Historial.h"

using namespace std;

int main()
{
	Tablero tablero;
	inicializarTablero(tablero);
	
	Pieza pieza;
	inicializarPieza(pieza, 'T');
	
	Historial historial;
	inicializarHistorial(historial);
	
	// Estado inicial
	registrarEstado(
					historial,
					tablero,
					pieza,
					'I'
					);
	
	// Mover derecha
	moverPiezaHorizontal(
						 tablero,
						 pieza,
						 1
						 );
	
	registrarEstado(
					historial,
					tablero,
					pieza,
					'D'
					);
	
	// Bajar
	bajarPieza(
			   tablero,
			   pieza
			   );
	
	registrarEstado(
					historial,
					tablero,
					pieza,
					'S'
					);
	
	// Rotar
	rotarPiezaValida(
					 tablero,
					 pieza
					 );
	
	registrarEstado(
					historial,
					tablero,
					pieza,
					'W'
					);
	
	cout << "ESTADO ACTUAL:" << endl;
	mostrarTableroConPieza(
						   tablero,
						   pieza
						   );
	
	cout << endl;
	cout << "DESHACER:" << endl;
	
	deshacer(
			 historial,
			 tablero,
			 pieza
			 );
	
	mostrarTableroConPieza(
						   tablero,
						   pieza
						   );
	
	cout << endl;
	cout << "DESHACER OTRA VEZ:" << endl;
	
	deshacer(
			 historial,
			 tablero,
			 pieza
			 );
	
	mostrarTableroConPieza(
						   tablero,
						   pieza
						   );
	
	cout << endl;
	cout << "REHACER:" << endl;
	
	rehacer(
			historial,
			tablero,
			pieza
			);
	
	mostrarTableroConPieza(
						   tablero,
						   pieza
						   );
	
	liberarHistorial(historial);
	liberarTablero(tablero);
	
	return 0;
}
