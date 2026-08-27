#include "PilaEspera.h"

void inicializarPila(PilaEspera &pila)
{
	pila.cima = nullptr;
}

bool estaVaciaPila(PilaEspera pila)
{
	return pila.cima == nullptr;
}

bool apilar(PilaEspera &pila, Pieza pieza)
{
	if (pila.cima != nullptr)
	{
		return false;
	}
	
	NodoEspera *nuevo = new NodoEspera();
	
	nuevo->pieza = pieza;
	nuevo->siguiente = nullptr;
	
	pila.cima = nuevo;
	
	return true;
}

Pieza desapilar(PilaEspera &pila)
{
	Pieza pieza;
	pieza.tipo = '?';
	
	if (pila.cima == nullptr)
	{
		return pieza;
	}
	
	NodoEspera *aux = pila.cima;
	
	pieza = aux->pieza;
	
	pila.cima = pila.cima->siguiente;
	
	delete aux;
	
	return pieza;
}

Pieza verPiezaEspera(PilaEspera pila)
{
	Pieza pieza;
	pieza.tipo = '?';
	
	if (pila.cima != nullptr)
	{
		pieza = pila.cima->pieza;
	}
	
	return pieza;
}
