#include "PruebasOrdenamiento.h"
#include "Puntajes.h"

#include <iostream>
#include <fstream>
#include <chrono>
#include <cstdlib>
#include <iomanip>

using namespace std;
using namespace chrono;

void generarDatosPrueba(
						RegistroPuntaje datos[],
						int cantidad)
{
	for (int i = 0;
	i < cantidad;
	i++)
	{
		datos[i].nombre =
			"Jugador";
		
		datos[i].puntaje =
			rand() % 100000;
	}
}

void copiarDatosPrueba(
					   RegistroPuntaje origen[],
					   RegistroPuntaje destino[],
					   int cantidad)
{
	for (int i = 0;
	i < cantidad;
	i++)
	{
		destino[i] =
			origen[i];
	}
}

double medirBubbleSort(
					   RegistroPuntaje datos[],
					   int cantidad)
{
	high_resolution_clock::time_point inicio =
		high_resolution_clock::now();
	
	bubbleSortPuntajes(
					   datos,
					   cantidad
					   );
	
	high_resolution_clock::time_point fin =
		high_resolution_clock::now();
	
	duration<double, milli> tiempo =
		fin - inicio;
	
	return tiempo.count();
}

double medirMergeSort(
					  RegistroPuntaje datos[],
					  int cantidad)
{
	high_resolution_clock::time_point inicio =
		high_resolution_clock::now();
	
	mergeSortPuntajes(
					  datos,
					  0,
					  cantidad - 1
					  );
	
	high_resolution_clock::time_point fin =
		high_resolution_clock::now();
	
	duration<double, milli> tiempo =
		fin - inicio;
	
	return tiempo.count();
}

void probarCantidad(
					int cantidad,
					ofstream &archivo)
{
	const int REPETICIONES =
		3;
	
	double totalBubble =
		0.0;
	
	double totalMerge =
		0.0;
	
	for (int prueba = 0;
	prueba < REPETICIONES;
	prueba++)
	{
		RegistroPuntaje *original =
			new RegistroPuntaje[cantidad];
		
		RegistroPuntaje *datosBubble =
			new RegistroPuntaje[cantidad];
		
		RegistroPuntaje *datosMerge =
			new RegistroPuntaje[cantidad];
		
		generarDatosPrueba(
						   original,
						   cantidad
						   );
		
		copiarDatosPrueba(
						  original,
						  datosBubble,
						  cantidad
						  );
		
		copiarDatosPrueba(
						  original,
						  datosMerge,
						  cantidad
						  );
		
		totalBubble +=
			medirBubbleSort(
							datosBubble,
							cantidad
							);
		
		totalMerge +=
			medirMergeSort(
						   datosMerge,
						   cantidad
						   );
		
		delete[] original;
		delete[] datosBubble;
		delete[] datosMerge;
	}
	
	double promedioBubble =
		totalBubble /
		REPETICIONES;
	
	double promedioMerge =
		totalMerge /
		REPETICIONES;
	
	cout
		<< fixed
		<< setprecision(9);
	
	cout
		<< cantidad
		<< " registros"
		<< endl;
	
	cout
		<< "Bubble Sort: "
		<< promedioBubble
		<< " ms"
		<< endl;
	
	cout
		<< "Merge Sort:  "
		<< promedioMerge
		<< " ms"
		<< endl;
	
	cout
		<< "------------------------------"
		<< endl;
	
	archivo
		<< "Cantidad de registros: "
		<< cantidad
		<< endl;
	
	archivo
		<< "Bubble Sort: "
		<< promedioBubble
		<< " ms"
		<< endl;
	
	archivo
		<< "Merge Sort: "
		<< promedioMerge
		<< " ms"
		<< endl;
	
	archivo
		<< "------------------------------"
		<< endl;
}

void ejecutarPruebasOrdenamiento()
{
	cout
		<< endl
		<< "================================"
		<< endl;
	
	cout
		<< "PRUEBAS DE ORDENAMIENTO"
		<< endl;
	
	cout
		<< "================================"
		<< endl;
	
	ofstream archivo(
					 "resultados_ordenamiento.txt"
					 );
	
	if (!archivo.is_open())
	{
		cout
			<< "No se pudo crear "
			<< "resultados_ordenamiento.txt"
			<< endl;
		
		return;
	}
	
	archivo
						 << "RESULTADOS DE PRUEBAS DE ORDENAMIENTO"
						 << endl;
	
	archivo
		<< "====================================="
		<< endl
		<< endl;
	
	probarCantidad(
				   10,
				   archivo
				   );
	
	probarCantidad(
				   100,
				   archivo
				   );
	
	probarCantidad(
				   1000,
				   archivo
				   );
	
	probarCantidad(
				   10000,
				   archivo
				   );
	
	probarCantidad(
				   30000,
				   archivo
				   );
	
	archivo.close();
	
	cout
		<< "PRUEBAS FINALIZADAS"
		<< endl;
	
	cout
		<< "Archivo generado: "
		<< "resultados_ordenamiento.txt"
		<< endl;
	
	cout
		<< "================================"
		<< endl;
}
