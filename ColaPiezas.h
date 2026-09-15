#ifndef COLAPIEZAS_H
#define COLAPIEZAS_H

#include "Pieza.h"

struct NodoPieza
{
	Pieza pieza;
	NodoPieza *siguiente;
};

struct ColaPiezas
{
	NodoPieza *frente;
	NodoPieza *final;
	int ultimaBolsaGenerada;
};

void inicializarCola(ColaPiezas &cola);
bool estaVacia(ColaPiezas cola);
void encolar(ColaPiezas &cola, Pieza pieza);
Pieza desencolar(ColaPiezas &cola);
void generarBolsa(ColaPiezas &cola);
void mostrarProximas(ColaPiezas cola, int cantidad);
Pieza obtenerSiguientePieza(ColaPiezas &cola);
int contarPiezas(ColaPiezas cola);
void asegurarProximasPiezas(ColaPiezas &cola);

#endif
