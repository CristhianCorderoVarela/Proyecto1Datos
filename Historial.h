#ifndef HISTORIAL_H
#define HISTORIAL_H

#include "Tablero.h"
#include "Pieza.h"
#include "ColaPiezas.h"
#include "PilaEspera.h"
#include "Eventos.h"

struct NodoHistorial
{
	int celdas[20][10];
	
	Pieza pieza;
	
	int puntaje;
	int lineasTotales;
	
	float tiempoCaida;
	
	bool especialPendiente;
	
	bool hayPiezaEspera;
	Pieza piezaEspera;
	
	Pieza piezasCola[20];
	int cantidadPiezasCola;
	int ultimaBolsaGenerada;
	
	Evento eventos[10];
	int cantidadEventos;
	
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

void inicializarHistorial(
						  Historial &historial
						  );

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
					 char accion
					 );

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
			  ColaEventos &colaEventos
			  );

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
			 ColaEventos &colaEventos
			 );

void liberarHistorial(
					  Historial &historial
					  );

void reproducirHistorial(
						 Historial &historial,
						 Tablero &tablero,
						 Pieza &pieza
						 );

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
					   ColaEventos &colaEventos
					   );

#endif
