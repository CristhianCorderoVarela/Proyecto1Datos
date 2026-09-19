#ifndef EVENTOS_H
#define EVENTOS_H

enum TipoEvento
{
	AUMENTAR_VELOCIDAD,
	BONO_PUNTOS,
	PIEZA_ESPECIAL
};

struct Evento
{
	TipoEvento tipo;
	int momento;
};

struct NodoEvento
{
	Evento evento;
	NodoEvento *siguiente;
};

struct ColaEventos
{
	NodoEvento *frente;
};

void inicializarColaEventos(
							ColaEventos &cola
							);

bool estaVaciaEventos(
					  ColaEventos cola
					  );

void insertarEvento(
					ColaEventos &cola,
					Evento evento
					);

bool extraerEvento(
				   ColaEventos &cola,
				   Evento &evento
				   );

bool verProximoEvento(
					  ColaEventos cola,
					  Evento &evento
					  );

void mostrarEventos(
					ColaEventos cola
					);

void liberarColaEventos(
						ColaEventos &cola
						);

#endif
