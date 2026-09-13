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


void insertarFilaVaciaAlInicio(Tablero &tablero)
{
	NodoFila *nuevo = new NodoFila();
	
	for (int i = 0; i < 10; i++)
	{
		nuevo->celdas[i] = 0;
	}
	
	nuevo->siguiente = tablero.inicio;
	tablero.inicio = nuevo;
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


int eliminarFilasCompletas(Tablero &tablero)
{
	NodoFila *actual = tablero.inicio;
	NodoFila *anterior = nullptr;
	
	int eliminadas = 0;
	
	while (actual != nullptr)
	{
		if (filaCompleta(actual))
		{
			NodoFila *borrar = actual;
			
			if (anterior == nullptr)
			{
				tablero.inicio = actual->siguiente;
				actual = tablero.inicio;
			}
			else
			{
				anterior->siguiente = actual->siguiente;
				actual = actual->siguiente;
			}
			
			delete borrar;
			eliminadas++;
		}
		else
		{
			anterior = actual;
			actual = actual->siguiente;
		}
	}
	
	for (int i = 0; i < eliminadas; i++)
	{
		insertarFilaVaciaAlInicio(tablero);
	}
	
	return eliminadas;
}

bool puedeColocarse(Tablero tablero, Pieza pieza)
{
	int bloques[4][2];
	
	obtenerBloques(pieza, bloques);
	
	for (int i = 0; i < 4; i++)
	{
		int fila = bloques[i][0];
		int columna = bloques[i][1];
		
		// Verificar limites del tablero
		if (fila < 0 || fila >= 20 ||
			columna < 0 || columna >= 10)
		{
			return false;
		}
		
		// Buscar la fila correspondiente
		NodoFila *actual = tablero.inicio;
		
		for (int f = 0; f < fila; f++)
		{
			actual = actual->siguiente;
		}
		
		// Verificar si la celda ya esta ocupada
		if (actual->celdas[columna] != 0)
		{
			return false;
		}
	}
	
	return true;
}


bool colocarPieza(Tablero &tablero, Pieza pieza)
{
	if (!puedeColocarse(tablero, pieza))
	{
		return false;
	}
	
	int bloques[4][2];
	
	obtenerBloques(pieza, bloques);
	
	for (int i = 0; i < 4; i++)
	{
		int fila = bloques[i][0];
		int columna = bloques[i][1];
		
		modificarCelda(tablero, fila, columna, 1);
	}
	
	return true;
}

bool bajarPieza(Tablero tablero, Pieza &pieza)
{
	Pieza prueba = pieza;
	
	prueba.fila++;
	
	if (puedeColocarse(tablero, prueba))
	{
		pieza.fila++;
		return true;
	}
	
	return false;
}

bool moverPiezaHorizontal(Tablero tablero, Pieza &pieza, int direccion)
{
	Pieza prueba = pieza;
	
	prueba.columna += direccion;
	
	if (puedeColocarse(tablero, prueba))
	{
		pieza.columna = prueba.columna;
		return true;
	}
	
	return false;
}

bool rotarPiezaValida(Tablero tablero, Pieza &pieza)
{
	
	Pieza prueba = pieza;
	
	rotarPieza(prueba);
	
	if (puedeColocarse(tablero, prueba))
	{
		pieza.orientacion = prueba.orientacion;
		return true;
	}
	
	return false;
}


void mostrarTableroConPieza(Tablero tablero, Pieza pieza)
{
	int bloques[4][2];
	
	obtenerBloques(pieza, bloques);
	
	NodoFila *actual = tablero.inicio;
	
	for (int fila = 0; fila < 20; fila++)
	{
		for (int columna = 0; columna < 10; columna++)
		{
			bool esPiezaActual = false;
			
			for (int i = 0; i < 4; i++)
			{
				if (bloques[i][0] == fila &&
					bloques[i][1] == columna)
				{
					esPiezaActual = true;
				}
			}
			
			if (esPiezaActual)
			{
				cout << pieza.tipo << " ";
			}
			else
			{
				cout << actual->celdas[columna] << " ";
			}
		}
		
		cout << endl;
		
		actual = actual->siguiente;
	}
}
