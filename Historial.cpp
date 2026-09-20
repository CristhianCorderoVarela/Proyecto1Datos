#include "Historial.h"
#include <iostream>

using namespace std;

void copiarTablero(
				   Tablero tablero,
				   NodoHistorial *nodo)
{
	NodoFila *filaActual =
		tablero.inicio;
	
	for (int fila = 0;
	fila < 20;
	fila++)
	{
		for (int columna = 0;
		columna < 10;
		columna++)
		{
			nodo->celdas[fila][columna] =
				filaActual->celdas[columna];
		}
		
		filaActual =
			filaActual->siguiente;
	}
}

void restaurarTablero(
					  Tablero &tablero,
					  NodoHistorial *nodo)
{
	NodoFila *filaActual =
		tablero.inicio;
	
	for (int fila = 0;
	fila < 20;
	fila++)
	{
		for (int columna = 0;
		columna < 10;
		columna++)
		{
			filaActual->celdas[columna] =
				nodo->celdas[fila][columna];
		}
		
		filaActual =
			filaActual->siguiente;
	}
}

void copiarPilaEspera(
					  PilaEspera pila,
					  NodoHistorial *nodo)
{
	nodo->hayPiezaEspera =
		!estaVaciaPila(pila);
	
	if (nodo->hayPiezaEspera)
	{
		nodo->piezaEspera =
			verPiezaEspera(pila);
	}
	else
	{
		inicializarPieza(
						 nodo->piezaEspera,
						 '?'
						 );
	}
}

void restaurarPilaEspera(
						 PilaEspera &pila,
						 NodoHistorial *nodo)
{
	while (!estaVaciaPila(pila))
	{
		desapilar(pila);
	}
	
	inicializarPila(pila);
	
	if (nodo->hayPiezaEspera)
	{
		apilar(
			   pila,
			   nodo->piezaEspera
			   );
	}
}

void copiarColaPiezas(
					  ColaPiezas cola,
					  NodoHistorial *nodo)
{
	nodo->cantidadPiezasCola = 0;
	
	NodoPieza *actual =
		cola.frente;
	
	while (
		   actual != nullptr &&
		   nodo->cantidadPiezasCola < 20)
	{
		nodo->piezasCola[
	nodo->cantidadPiezasCola
		] = actual->pieza;
		
		nodo->cantidadPiezasCola++;
		
		actual =
			actual->siguiente;
	}
		   
		   nodo->ultimaBolsaGenerada =
		   cola.ultimaBolsaGenerada;
}

void restaurarColaPiezas(
						 ColaPiezas &cola,
						 NodoHistorial *nodo)
{
	while (!estaVacia(cola))
	{
		desencolar(cola);
	}
	
	inicializarCola(cola);
	
	for (int i = 0;
	i < nodo->cantidadPiezasCola;
	i++)
	{
		encolar(
				cola,
				nodo->piezasCola[i]
				);
	}
	
	cola.ultimaBolsaGenerada =
		nodo->ultimaBolsaGenerada;
}

void copiarEventos(
				   ColaEventos colaEventos,
				   NodoHistorial *nodo)
{
	nodo->cantidadEventos = 0;
	
	NodoEvento *actual =
		colaEventos.frente;
	
	while (
		   actual != nullptr &&
		   nodo->cantidadEventos < 10)
	{
		nodo->eventos[
	nodo->cantidadEventos
		] = actual->evento;
		
		nodo->cantidadEventos++;
		
		actual =
			actual->siguiente;
	}
}

void restaurarEventos(
					  ColaEventos &colaEventos,
					  NodoHistorial *nodo)
{
	liberarColaEventos(
					   colaEventos
					   );
	
	inicializarColaEventos(
						   colaEventos
						   );
	
	for (int i = 0;
	i < nodo->cantidadEventos;
	i++)
	{
		insertarEvento(
					   colaEventos,
					   nodo->eventos[i]
					   );
	}
}

void restaurarEstadoCompleto(
							 NodoHistorial *nodo,
							 Tablero &tablero,
							 Pieza &pieza,
							 int &puntaje,
							 int &lineasTotales,
							 float &tiempoCaida,
							 bool &especialPendiente,
							 PilaEspera &pila,
							 ColaPiezas &cola,
							 ColaEventos &colaEventos)
{
	restaurarTablero(
					 tablero,
					 nodo
					 );
	
	pieza =
		nodo->pieza;
	
	puntaje =
		nodo->puntaje;
	
	lineasTotales =
		nodo->lineasTotales;
	
	tiempoCaida =
		nodo->tiempoCaida;
	
	especialPendiente =
		nodo->especialPendiente;
	
	restaurarPilaEspera(
						pila,
						nodo
						);
	
	restaurarColaPiezas(
						cola,
						nodo
						);
	
	restaurarEventos(
					 colaEventos,
					 nodo
					 );
}

void inicializarHistorial(
						  Historial &historial)
{
	historial.primero =
		nullptr;
	
	historial.actual =
		nullptr;
	
	historial.ultimo =
		nullptr;
}

void registrarEstado(
					 Historial &historial,
					 Tablero tablero,
					 Pieza pieza,
					 int puntaje,
					 int lineasTotales,
					 float tiempoCaida,
					 bool especialPendiente,
					 PilaEspera pila,
					 ColaPiezas cola,
					 ColaEventos colaEventos,
					 char accion)
{
	if (
		historial.actual != nullptr &&
		historial.actual->siguiente != nullptr)
	{
		NodoHistorial *borrar =
			historial.actual->siguiente;
		
		while (borrar != nullptr)
		{
			NodoHistorial *siguiente =
				borrar->siguiente;
			
			delete borrar;
			
			borrar =
				siguiente;
		}
		
		historial.actual->siguiente =
			   nullptr;
		
		historial.ultimo =
			historial.actual;
	}
		
		NodoHistorial *nuevo =
		new NodoHistorial;
		
		copiarTablero(
					  tablero,
					  nuevo
					  );
		
		copiarPilaEspera(
						 pila,
						 nuevo
						 );
		
		copiarColaPiezas(
						 cola,
						 nuevo
						 );
		
		copiarEventos(
					  colaEventos,
					  nuevo
					  );
		
		nuevo->pieza =
			pieza;
		
		nuevo->puntaje =
			puntaje;
		
		nuevo->lineasTotales =
			lineasTotales;
		
		nuevo->tiempoCaida =
			tiempoCaida;
		
		nuevo->especialPendiente =
			especialPendiente;
		
		nuevo->accion =
			accion;
		
		nuevo->anterior =
			nullptr;
		
		nuevo->siguiente =
			nullptr;
		
		if (historial.primero == nullptr)
		{
			historial.primero =
				nuevo;
			
			historial.actual =
				nuevo;
			
			historial.ultimo =
				nuevo;
		}
		else
		{
			nuevo->anterior =
				historial.ultimo;
			
			historial.ultimo->siguiente =
				nuevo;
			
			historial.ultimo =
				nuevo;
			
			historial.actual =
				nuevo;
		}
}

bool deshacer(
			  Historial &historial,
			  Tablero &tablero,
			  Pieza &pieza,
			  int &puntaje,
			  int &lineasTotales,
			  float &tiempoCaida,
			  bool &especialPendiente,
			  PilaEspera &pila,
			  ColaPiezas &cola,
			  ColaEventos &colaEventos)
{
	if (
		historial.actual == nullptr ||
		historial.actual->anterior == nullptr)
	{
		return false;
	}
		
		historial.actual =
		historial.actual->anterior;
		
		restaurarEstadoCompleto(
								historial.actual,
								tablero,
								pieza,
								puntaje,
								lineasTotales,
								tiempoCaida,
								especialPendiente,
								pila,
								cola,
								colaEventos
								);
		
		return true;
}

bool rehacer(
			 Historial &historial,
			 Tablero &tablero,
			 Pieza &pieza,
			 int &puntaje,
			 int &lineasTotales,
			 float &tiempoCaida,
			 bool &especialPendiente,
			 PilaEspera &pila,
			 ColaPiezas &cola,
			 ColaEventos &colaEventos)
{
	if (
		historial.actual == nullptr ||
		historial.actual->siguiente == nullptr)
	{
		return false;
	}
		
		historial.actual =
		historial.actual->siguiente;
		
		restaurarEstadoCompleto(
								historial.actual,
								tablero,
								pieza,
								puntaje,
								lineasTotales,
								tiempoCaida,
								especialPendiente,
								pila,
								cola,
								colaEventos
								);
		
		return true;
}

void liberarHistorial(
					  Historial &historial)
{
	NodoHistorial *actual =
		historial.primero;
	
	while (actual != nullptr)
	{
		NodoHistorial *borrar =
			actual;
		
		actual =
			actual->siguiente;
		
		delete borrar;
	}
	
	historial.primero =
		   nullptr;
	
	historial.actual =
		nullptr;
	
	historial.ultimo =
		nullptr;
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
		
		pieza =
			recorrido->pieza;
		
		cout << endl;
		
		cout
			<< "===================="
			<< endl;
		
		cout
			<< "PASO "
			<< paso
			<< endl;
		
		cout
			<< "Accion: "
			<< recorrido->accion
			<< endl;
		
		cout
			<< "===================="
			<< endl;
		
		mostrarTableroConPieza(
							   tablero,
							   pieza
							   );
		
		recorrido =
			recorrido->siguiente;
		
		paso++;
	}
}

bool irInicioHistorial(
					   Historial &historial,
					   Tablero &tablero,
					   Pieza &pieza,
					   int &puntaje,
					   int &lineasTotales,
					   float &tiempoCaida,
					   bool &especialPendiente,
					   PilaEspera &pila,
					   ColaPiezas &cola,
					   ColaEventos &colaEventos)
{
	if (historial.primero == nullptr)
	{
		return false;
	}
	
	historial.actual =
		historial.primero;
	
	restaurarEstadoCompleto(
							historial.actual,
							tablero,
							pieza,
							puntaje,
							lineasTotales,
							tiempoCaida,
							especialPendiente,
							pila,
							cola,
							colaEventos
							);
	
	return true;
}
