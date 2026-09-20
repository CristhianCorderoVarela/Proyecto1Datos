#ifndef PUNTAJES_H
#define PUNTAJES_H

#include <string>

struct RegistroPuntaje
{
	std::string nombre;
	int puntaje;
};

int cargarPuntajes(
				   RegistroPuntaje registros[],
				   int maximo
				   );

void guardarArchivoTop10(
						 RegistroPuntaje registros[],
						 int cantidad
						 );

void bubbleSortPuntajes(
						RegistroPuntaje registros[],
						int cantidad
						);

void mergeSortPuntajes(
					   RegistroPuntaje registros[],
					   int inicio,
					   int fin
					   );

void ordenarPuntajes(
					 RegistroPuntaje registros[],
					 int cantidad,
					 int algoritmo
					 );

bool calificaTop10(
				   RegistroPuntaje registros[],
				   int cantidad,
				   int nuevoPuntaje,
				   int algoritmo
				   );

bool registrarPuntajeTop10(
						   const std::string &nombre,
						   int puntaje,
						   int algoritmo
						   );

void mostrarTop10(
				  RegistroPuntaje registros[],
				  int cantidad
				  );

#endif
