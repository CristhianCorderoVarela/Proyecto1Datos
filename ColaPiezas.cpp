#include "ColaPiezas.h"

void inicializarCola(ColaPiezas &cola)
{
	cola.frente = nullptr;
	cola.final = nullptr;
}

bool estaVacia(ColaPiezas cola)
{
	return cola.frente == nullptr;
}

void encolar(ColaPiezas &cola, Pieza pieza)
{
	NodoPieza *nuevo = new NodoPieza();
	
	nuevo->pieza = pieza;
	nuevo->siguiente = nullptr;
	
	if (cola.frente == nullptr)
	{
		cola.frente = nuevo;
		cola.final = nuevo;
	}
	else
	{
		cola.final->siguiente = nuevo;
		cola.final = nuevo;
	}
}

Pieza desencolar(ColaPiezas &cola)
{
	Pieza pieza;
	pieza.tipo = '?';
	
	if (cola.frente == nullptr)
	{
		return pieza;
	}
	
	NodoPieza *aux = cola.frente;
	
	pieza = aux->pieza;
	
	cola.frente = cola.frente->siguiente;
	
	if (cola.frente == nullptr)
	{
		cola.final = nullptr;
	}
	
	delete aux;
	
	return pieza;
}
