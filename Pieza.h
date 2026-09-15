#ifndef PIEZA_H
#define PIEZA_H

struct Pieza
{
	char tipo;
	int fila;
	int columna;
	int orientacion;
	int numeroBolsa;
};

void inicializarPieza(Pieza &pieza, char tipo);
void obtenerBloques(Pieza pieza, int bloques[4][2]);
void rotarPieza(Pieza &pieza);


#endif
