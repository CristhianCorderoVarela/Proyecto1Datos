#ifndef PILAESPERA_H
#define PILAESPERA_H

#include "Pieza.h"

struct NodoEspera
{
	Pieza pieza;
	NodoEspera *siguiente;
};

struct PilaEspera
{
	NodoEspera *cima;
};

void inicializarPila(PilaEspera &pila);
bool estaVaciaPila(PilaEspera pila);
bool apilar(PilaEspera &pila, Pieza pieza);
Pieza desapilar(PilaEspera &pila);
Pieza verPiezaEspera(PilaEspera pila);

#endif
