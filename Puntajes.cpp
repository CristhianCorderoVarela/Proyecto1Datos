#include "Puntajes.h"

#include <fstream>
#include <iostream>
#include <cstdlib>

using namespace std;

int cargarPuntajes(
				   RegistroPuntaje registros[],
				   int maximo)
{
	ifstream archivo(
					 "puntajes.txt"
					 );
	
	if (!archivo.is_open())
	{
		return 0;
	}
	
	int cantidad = 0;
	string linea;
	
	while (
		   cantidad < maximo
		   &&
		   getline(
				   archivo,
				   linea
				   ))
	{
		size_t posicion =
			linea.find('|');
		
		if (
			posicion ==
			string::npos)
		{
			continue;
		}
			
			registros[cantidad].nombre =
			linea.substr(
						 0,
						 posicion
						 );
			
			string textoPuntaje =
				linea.substr(
							 posicion + 1
							 );
			
			registros[cantidad].puntaje =
				atoi(
					 textoPuntaje.c_str()
					 );
			
			cantidad++;
	}
				   
				   archivo.close();
				   
				   return cantidad;
}

void guardarArchivoTop10(
						 RegistroPuntaje registros[],
						 int cantidad)
{
	ofstream archivo(
					 "puntajes.txt"
					 );
	
	if (!archivo.is_open())
	{
		cout
			<< "Error al guardar puntajes.txt"
			<< endl;
		
		return;
	}
	
	int limite =
						 cantidad;
	
	if (limite > 10)
	{
		limite = 10;
	}
	
	for (int i = 0;
	i < limite;
	i++)
	{
		archivo
			<< registros[i].nombre
			<< "|"
			<< registros[i].puntaje
			<< endl;
	}
	
	archivo.close();
}

void bubbleSortPuntajes(
						RegistroPuntaje registros[],
						int cantidad)
{
	bool intercambio;
	
	do
	{
		intercambio =
			false;
		
		for (int i = 0;
		i < cantidad - 1;
		i++)
		{
			if (
				registros[i].puntaje <
				registros[i + 1].puntaje)
			{
				RegistroPuntaje auxiliar =
					registros[i];
				
				registros[i] =
					registros[i + 1];
				
				registros[i + 1] =
					auxiliar;
				
				intercambio =
					true;
			}
		}
		
		cantidad--;
		
	}
	while (
		   intercambio
		   &&
		   cantidad > 1
		   );
}

void mezclarPuntajes(
					 RegistroPuntaje registros[],
					 int inicio,
					 int medio,
					 int fin)
{
	int cantidadIzquierda =
		medio - inicio + 1;
	
	int cantidadDerecha =
		fin - medio;
	
	RegistroPuntaje *izquierda =
		new RegistroPuntaje[
	cantidadIzquierda
		];
	
	RegistroPuntaje *derecha =
		new RegistroPuntaje[
	cantidadDerecha
		];
	
	for (int i = 0;
	i < cantidadIzquierda;
	i++)
	{
		izquierda[i] =
			registros[
	inicio + i
		];
	}
	
	for (int j = 0;
	j < cantidadDerecha;
	j++)
	{
		derecha[j] =
			registros[
	medio + 1 + j
		];
	}
	
	int i = 0;
	int j = 0;
	int k = inicio;
	
	while (
		   i < cantidadIzquierda
		   &&
		   j < cantidadDerecha)
	{
		if (
			izquierda[i].puntaje >=
			derecha[j].puntaje)
		{
			registros[k] =
				izquierda[i];
			
			i++;
		}
		else
			{
				registros[k] =
					derecha[j];
				
				j++;
			}
			
			k++;
	}
		   
		   while (
				  i < cantidadIzquierda)
		   {
			   registros[k] =
				   izquierda[i];
			   
			   i++;
			   k++;
		   }
				  
				  while (
						 j < cantidadDerecha)
				  {
					  registros[k] =
						  derecha[j];
					  
					  j++;
					  k++;
				  }
						 
						 delete[] izquierda;
						 delete[] derecha;
}

void mergeSortPuntajes(
					   RegistroPuntaje registros[],
					   int inicio,
					   int fin)
{
	if (inicio >= fin)
	{
		return;
	}
	
	int medio =
		inicio +
		(fin - inicio) / 2;
	
	mergeSortPuntajes(
					  registros,
					  inicio,
					  medio
					  );
	
	mergeSortPuntajes(
					  registros,
					  medio + 1,
					  fin
					  );
	
	mezclarPuntajes(
					registros,
					inicio,
					medio,
					fin
					);
}

void ordenarPuntajes(
					 RegistroPuntaje registros[],
					 int cantidad,
					 int algoritmo)
{
	if (cantidad <= 1)
	{
		return;
	}
	
	if (algoritmo == 1)
	{
		bubbleSortPuntajes(
						   registros,
						   cantidad
						   );
	}
	else
	{
		mergeSortPuntajes(
						  registros,
						  0,
						  cantidad - 1
						  );
	}
}

bool calificaTop10(
				   RegistroPuntaje registros[],
				   int cantidad,
				   int nuevoPuntaje,
				   int algoritmo)
{
	if (cantidad < 10)
	{
		return true;
	}
	
	ordenarPuntajes(
					registros,
					cantidad,
					algoritmo
					);
	
	if (
		nuevoPuntaje >
		registros[9].puntaje)
	{
		return true;
	}
		
		return false;
}

bool registrarPuntajeTop10(
						   const string &nombre,
						   int puntaje,
						   int algoritmo)
{
	RegistroPuntaje registros[11];
	
	int cantidad =
		cargarPuntajes(
					   registros,
					   10
					   );
	
	if (!calificaTop10(
					   registros,
					   cantidad,
					   puntaje,
					   algoritmo))
	{
		return false;
	}
					   
					   registros[cantidad].nombre =
					   nombre;
					   
					   registros[cantidad].puntaje =
						   puntaje;
					   
					   cantidad++;
					   
					   ordenarPuntajes(
									   registros,
									   cantidad,
									   algoritmo
									   );
					   
					   if (cantidad > 10)
					   {
						   cantidad =
							   10;
					   }
					   
					   guardarArchivoTop10(
										   registros,
										   cantidad
										   );
					   
					   return true;
}

void mostrarTop10(
				  RegistroPuntaje registros[],
				  int cantidad)
{
	int limite =
		cantidad;
	
	if (limite > 10)
	{
		limite = 10;
	}
	
	cout
		<< endl
		<< "===== TOP 10 ====="
		<< endl;
	
	for (int i = 0;
	i < limite;
	i++)
	{
		cout
			<< i + 1
			<< ". "
			<< registros[i].nombre
			<< " - "
			<< registros[i].puntaje
			<< endl;
	}
}
