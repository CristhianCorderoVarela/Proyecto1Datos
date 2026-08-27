#include "ColaPiezas.h"
#include <iostream>
#include <cstdlib>

using namespace std;


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


void generarBolsa(ColaPiezas &cola)
{
	char tipos[7] = {'I', 'O', 'T', 'S', 'Z', 'J', 'L'};
	
	for (int i = 6; i > 0; i--)
	{
		int j = rand() % (i + 1);
		
		char aux = tipos[i];
		tipos[i] = tipos[j];
		tipos[j] = aux;
	}
	
	for (int i = 0; i < 7; i++)
	{
		Pieza pieza;
		pieza.tipo = tipos[i];
		
		encolar(cola, pieza);
	}
}


void mostrarProximas(ColaPiezas cola, int cantidad)
{
	NodoPieza *aux = cola.frente;
	int contador = 0;
	
	while (aux != nullptr && contador < cantidad)
	{
		cout << aux->pieza.tipo << " ";
		aux = aux->siguiente;
		contador++;
	}
	
	cout << endl;
}


Pieza obtenerSiguientePieza(ColaPiezas &cola)
{
	if (estaVacia(cola))
	{
		generarBolsa(cola);
	}
	
	return desencolar(cola);
}
