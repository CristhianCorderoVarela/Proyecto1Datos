#include "Eventos.h"
#include <iostream>

using namespace std;

void inicializarColaEventos(
							ColaEventos &cola)
{
	cola.frente = nullptr;
}

bool estaVaciaEventos(
					  ColaEventos cola)
{
	return cola.frente == nullptr;
}

void insertarEvento(
					ColaEventos &cola,
					Evento evento)
{
	NodoEvento *nuevo =
		new NodoEvento;
	
	nuevo->evento = evento;
	nuevo->siguiente = nullptr;
	
	
	if (cola.frente == nullptr)
	{
		cola.frente = nuevo;
		return;
	}
	
	
	if (evento.momento <
		cola.frente->evento.momento)
	{
		nuevo->siguiente =
			cola.frente;
		
		cola.frente = nuevo;
		
		return;
	}
	
	
	NodoEvento *actual =
		cola.frente;
	
	while (
		   actual->siguiente != nullptr &&
		   actual->siguiente->evento.momento
		   <= evento.momento)
	{
		actual =
			actual->siguiente;
	}
		   
		   nuevo->siguiente =
		   actual->siguiente;
		   
		   actual->siguiente =
			   nuevo;
}

bool extraerEvento(
				   ColaEventos &cola,
				   Evento &evento)
{
	if (cola.frente == nullptr)
	{
		return false;
	}
	
	NodoEvento *eliminar =
		cola.frente;
	
	evento =
		eliminar->evento;
	
	cola.frente =
		cola.frente->siguiente;
	
	delete eliminar;
	
	return true;
}

bool verProximoEvento(
					  ColaEventos cola,
					  Evento &evento)
{
	if (cola.frente == nullptr)
	{
		return false;
	}
	
	evento =
		cola.frente->evento;
	
	return true;
}

void mostrarEventos(
					ColaEventos cola)
{
	NodoEvento *actual =
		cola.frente;
	
	while (actual != nullptr)
	{
		cout << "Momento: "
			<< actual->evento.momento
			<< " - Tipo: "
			<< actual->evento.tipo
			<< endl;
		
		actual =
			actual->siguiente;
	}
}

void liberarColaEventos(
						ColaEventos &cola)
{
	while (cola.frente != nullptr)
	{
		NodoEvento *eliminar =
			cola.frente;
		
		cola.frente =
			cola.frente->siguiente;
		
		delete eliminar;
	}
}
