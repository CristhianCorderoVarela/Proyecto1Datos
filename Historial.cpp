#include "Historial.h"

#include <iostream>

using namespace std;

void copiarTablero(Tablero tablero, NodoHistorial *nodo)
{
	NodoFila *filaActual = tablero.inicio;
	
	for (int fila = 0; fila < 20; fila++)
	{
		for (int columna = 0; columna < 10; columna++)
		{
			nodo->celdas[fila][columna] =
				filaActual->celdas[columna];
		}
		
		filaActual = filaActual->siguiente;
	}
}

void restaurarTablero(Tablero &tablero, NodoHistorial *nodo)
{
	NodoFila *filaActual = tablero.inicio;
	
	for (int fila = 0; fila < 20; fila++)
	{
		for (int columna = 0; columna < 10; columna++)
		{
			filaActual->celdas[columna] =
				nodo->celdas[fila][columna];
		}
		
		filaActual = filaActual->siguiente;
	}
}

void inicializarHistorial(Historial &historial)
{
	historial.primero = nullptr;
	historial.actual = nullptr;
	historial.ultimo = nullptr;
}

void registrarEstado(
					 Historial &historial,
					 Tablero tablero,
					 Pieza pieza,
					 char accion)
{
	if (historial.actual != nullptr &&
		historial.actual->siguiente != nullptr)
	{
		NodoHistorial *borrar =
			historial.actual->siguiente;
		
		while (borrar != nullptr)
		{
			NodoHistorial *siguiente =
				borrar->siguiente;
			
			delete borrar;
			
			borrar = siguiente;
		}
		
		historial.actual->siguiente = nullptr;
		historial.ultimo = historial.actual;
	}
	
	NodoHistorial *nuevo =
		new NodoHistorial();
	
	copiarTablero(tablero, nuevo);
	
	nuevo->pieza = pieza;
	nuevo->accion = accion;
	
	nuevo->anterior = nullptr;
	nuevo->siguiente = nullptr;
	
	if (historial.primero == nullptr)
	{
		historial.primero = nuevo;
		historial.actual = nuevo;
		historial.ultimo = nuevo;
	}
	else
	{
		nuevo->anterior = historial.ultimo;
		
		historial.ultimo->siguiente = nuevo;
		
		historial.ultimo = nuevo;
		historial.actual = nuevo;
	}
}

bool deshacer(
			  Historial &historial,
			  Tablero &tablero,
			  Pieza &pieza)
{
	if (historial.actual == nullptr ||
		historial.actual->anterior == nullptr)
	{
		return false;
	}
	
	historial.actual =
		historial.actual->anterior;
	
	restaurarTablero(
					 tablero,
					 historial.actual
					 );
	
	pieza = historial.actual->pieza;
	
	return true;
}

bool rehacer(
			 Historial &historial,
			 Tablero &tablero,
			 Pieza &pieza)
{
	if (historial.actual == nullptr ||
		historial.actual->siguiente == nullptr)
	{
		return false;
	}
	
	historial.actual =
		historial.actual->siguiente;
	
	restaurarTablero(
					 tablero,
					 historial.actual
					 );
	
	pieza = historial.actual->pieza;
	
	return true;
}

void liberarHistorial(Historial &historial)
{
	
	NodoHistorial *actual =
		historial.primero;
	
	while (actual != nullptr)
	{
		NodoHistorial *borrar = actual;
		
		actual = actual->siguiente;
		
		delete borrar;
	}
	
	historial.primero = nullptr;
	historial.actual = nullptr;
	historial.ultimo = nullptr;
}


void reproducirHistorial(
						 Historial &historial,
						 Tablero &tablero,
						 Pieza &pieza)
{
	NodoHistorial *recorrido =
		historial.primero;
	
	int paso = 0;
	
	while (recorrido != nullptr)
	{
		restaurarTablero(
						 tablero,
						 recorrido
						 );
		
		pieza = recorrido->pieza;
		
		cout << endl;
		cout << "====================" << endl;
		cout << "PASO " << paso << endl;
		cout << "Accion: "
			<< recorrido->accion << endl;
		cout << "====================" << endl;
		
		mostrarTableroConPieza(
							   tablero,
							   pieza
							   );
		
		recorrido =
			recorrido->siguiente;
		
		paso++;
	}
}
