#include <iostream>
#include <cstdlib>
#include <ctime>

#include "ColaPiezas.h"
#include "Tablero.h"
#include "Pieza.h"

using namespace std;

int main()
{
	srand(time(nullptr));
	
	Tablero tablero;
	inicializarTablero(tablero);
	
	ColaPiezas cola;
	inicializarCola(cola);
	generarBolsa(cola);
	
	for (int turno = 1; turno <= 10; turno++)
	{
		Pieza actual = obtenerSiguientePieza(cola);
		
		cout << endl;
		cout << "Turno " << turno << endl;
		cout << "Pieza: " << actual.tipo << endl;
		
		// Verificar si la nueva pieza puede aparecer
		if (!puedeColocarse(tablero, actual))
		{
			cout << "GAME OVER" << endl;
			break;
		}
		
		// Dejar caer la pieza hasta que ya no pueda bajar
		while (bajarPieza(tablero, actual))
		{
		}
		
		// Fijar la pieza en el tablero
		colocarPieza(tablero, actual);
		
		// Revisar filas completas
		int eliminadas = eliminarFilasCompletas(tablero);
		
		if (eliminadas > 0)
		{
			cout << "Filas eliminadas: "
				<< eliminadas << endl;
		}
		
		mostrarTablero(tablero);
	}
	
	liberarTablero(tablero);
	
	return 0;
}
