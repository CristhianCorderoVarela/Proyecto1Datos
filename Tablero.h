#ifndef TABLERO_H
#define TABLERO_H

struct NodoFila
{
	int celdas[10];
	NodoFila *siguiente;
};

struct Tablero
{
	NodoFila *inicio;
};

void inicializarTablero(Tablero &tablero);
void mostrarTablero(Tablero tablero);
void liberarTablero(Tablero &tablero);

#endif
