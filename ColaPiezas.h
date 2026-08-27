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
};

void inicializarCola(ColaPiezas &cola);
bool estaVacia(ColaPiezas cola);
void encolar(ColaPiezas &cola, Pieza pieza);
Pieza desencolar(ColaPiezas &cola);

#endif
