#ifndef TABLERO_H
#define TABLERO_H

#include "Pieza.h"

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
void modificarCelda(Tablero &tablero, int fila, int columna, int valor);
bool filaCompleta(NodoFila *fila);
void insertarFilaVaciaAlInicio(Tablero &tablero);
int eliminarFilasCompletas(Tablero &tablero);
bool puedeColocarse(Tablero tablero, Pieza pieza);
bool colocarPieza(Tablero &tablero, Pieza pieza);
bool bajarPieza(Tablero tablero, Pieza &pieza);

bool moverPiezaHorizontal(Tablero tablero, Pieza &pieza, int direccion);
bool rotarPiezaValida(Tablero tablero, Pieza &pieza);

#endif
