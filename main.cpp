#include <iostream>
#include <cstdlib>
#include <ctime>
#include "ColaPiezas.h"

using namespace std;

int main()
{
	srand(time(nullptr));
	
	ColaPiezas cola;
	inicializarCola(cola);
	
	generarBolsa(cola);
	
	cout << "Sacando 10 piezas:" << endl;
	
	for (int i = 0; i < 10; i++)
	{
		Pieza pieza = obtenerSiguientePieza(cola);
		
		cout << pieza.tipo << " ";
	}
	
	cout << endl;
	
	return 0;
}
