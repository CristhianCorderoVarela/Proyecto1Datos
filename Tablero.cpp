#include "Tablero.h"
#include <iostream>

using namespace std;

void inicializarTablero(Tablero &tablero)
{
	tablero.inicio = nullptr;
	
	NodoFila *final = nullptr;
	
	for (int i = 0; i < 20; i++)
	{
		NodoFila *nuevo = new NodoFila();
		
		for (int j = 0; j < 10; j++)
		{
			nuevo->celdas[j] = 0;
		}
		
		nuevo->siguiente = nullptr;
		
		if (tablero.inicio == nullptr)
		{
			tablero.inicio = nuevo;
			final = nuevo;
		}
		else
		{
			final->siguiente = nuevo;
			final = nuevo;
		}
	}
}

void mostrarTablero(Tablero tablero)
{
	NodoFila *actual = tablero.inicio;
	
	while (actual != nullptr)
	{
		for (int j = 0; j < 10; j++)
		{
			cout << actual->celdas[j] << " ";
		}
		
		cout << endl;
		
		actual = actual->siguiente;
	}
}

void liberarTablero(Tablero &tablero)
{
	NodoFila *actual = tablero.inicio;
	
	while (actual != nullptr)
	{
		NodoFila *aux = actual;
		
		actual = actual->siguiente;
		
		delete aux;
	}
	
	tablero.inicio = nullptr;
}


bool filaCompleta(NodoFila *fila)
{
	if (fila == nullptr)
	{
		return false;
	}
	
	for (int i = 0; i < 10; i++)
	{
		if (fila->celdas[i] == 0)
		{
			return false;
		}
	}
	
	return true;
}

void modificarCelda(Tablero &tablero, int fila, int columna, int valor)
{
	if (fila < 0 || fila >= 20 || columna < 0 || columna >= 10)
	{
		return;
	}
	
	NodoFila *actual = tablero.inicio;
	
	for (int i = 0; i < fila; i++)
	{
		actual = actual->siguiente;
	}
	
	actual->celdas[columna] = valor;
}
