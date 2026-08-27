#include <iostream>
#include <cstdlib>
#include <ctime>

#include "ColaPiezas.h"
#include "PilaEspera.h"

using namespace std;

int main()
{
	srand(time(nullptr));
	
	ColaPiezas cola;
	inicializarCola(cola);
	generarBolsa(cola);
	
	PilaEspera pila;
	inicializarPila(pila);
	
	Pieza actual = obtenerSiguientePieza(cola);
	
	cout << "Pieza actual: " << actual.tipo << endl;
	
	// Primera vez que usamos la espera
	if (estaVaciaPila(pila))
	{
		apilar(pila, actual);
		
		actual = obtenerSiguientePieza(cola);
		
		cout << "Se guardo la pieza en espera." << endl;
		cout << "Nueva pieza actual: " << actual.tipo << endl;
	}
	
	// Mostrar la pieza que quedo guardada
	if (!estaVaciaPila(pila))
	{
		Pieza espera = verPiezaEspera(pila);
		
		cout << "Pieza guardada en espera: "
			<< espera.tipo << endl;
	}
	
	cout << endl;
	cout << "Ahora intercambiamos las piezas..." << endl;
	
	Pieza guardada = desapilar(pila);
	
	apilar(pila, actual);
	
	actual = guardada;
	
	cout << "Pieza actual despues del intercambio: "
		<< actual.tipo << endl;
	
	Pieza espera = verPiezaEspera(pila);
	
	cout << "Pieza que queda en espera: "
		<< espera.tipo << endl;
	
	return 0;
}
