#ifndef HISTORIAL_H
#define HISTORIAL_H

#include "Tablero.h"
#include "Pieza.h"

struct NodoHistorial
{
	int celdas[20][10];
	
	Pieza pieza;
	
	char accion;
	
	NodoHistorial *anterior;
	NodoHistorial *siguiente;
};

struct Historial
{
	NodoHistorial *primero;
	NodoHistorial *actual;
	NodoHistorial *ultimo;
};

void inicializarHistorial(Historial &historial);

void registrarEstado(
					 Historial &historial,
					 Tablero tablero,
					 Pieza pieza,
					 char accion
					 );

bool deshacer(
			  Historial &historial,
			  Tablero &tablero,
			  Pieza &pieza
			  );

bool rehacer(
			 Historial &historial,
			 Tablero &tablero,
			 Pieza &pieza
			 );

void liberarHistorial(Historial &historial);

#endif
