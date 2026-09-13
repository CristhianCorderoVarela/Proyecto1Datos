#include <iostream>
#include <cstdlib>
#include <ctime>

#include "ColaPiezas.h"
#include "PilaEspera.h"
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
	
	PilaEspera pila;
	inicializarPila(pila);
	
	bool juegoTerminado = false;
	
	while (!juegoTerminado)
	{
		Pieza actual = obtenerSiguientePieza(cola);
		
		// Si una nueva pieza no puede aparecer, termina el juego
		if (!puedeColocarse(tablero, actual))
		{
			cout << "GAME OVER" << endl;
			break;
		}
		
		bool piezaFijada = false;
		
		while (!piezaFijada && !juegoTerminado)
		{
			cout << endl;
			cout << "TABLERO:" << endl;
			mostrarTableroConPieza(tablero, actual);
			
			cout << endl;
			cout << "Pieza actual: " << actual.tipo << endl;
			
			cout << "Proximas piezas: ";
			mostrarProximas(cola, 3);
			
			if (estaVaciaPila(pila))
			{
				cout << "Pieza en espera: vacia" << endl;
			}
			else
			{
				Pieza espera = verPiezaEspera(pila);
				cout << "Pieza en espera: "
					<< espera.tipo << endl;
			}
			
			cout << endl;
			cout << "A = izquierda" << endl;
			cout << "D = derecha" << endl;
			cout << "S = bajar" << endl;
			cout << "W = rotar" << endl;
			cout << "H = espera" << endl;
			cout << "X = dejar caer" << endl;
			cout << "Q = salir" << endl;
			
			cout << endl;
			cout << "Movimiento: ";
			
			char comando;
			cin >> comando;
			
			// IZQUIERDA
			if (comando == 'a' || comando == 'A')
			{
				moverPiezaHorizontal(tablero, actual, -1);
			}
			
			// DERECHA
			else if (comando == 'd' || comando == 'D')
			{
				moverPiezaHorizontal(tablero, actual, 1);
			}
			
			// ROTAR
			else if (comando == 'w' || comando == 'W')
			{
				rotarPiezaValida(tablero, actual);
			}
			
			// BAJAR UNA FILA
			else if (comando == 's' || comando == 'S')
			{
				if (!bajarPieza(tablero, actual))
				{
					colocarPieza(tablero, actual);
					
					int eliminadas =
						eliminarFilasCompletas(tablero);
					
					if (eliminadas > 0)
					{
						cout << "Filas eliminadas: "
							<< eliminadas << endl;
					}
					
					piezaFijada = true;
				}
			}
			
			// CAIDA COMPLETA
			else if (comando == 'x' || comando == 'X')
			{
				while (bajarPieza(tablero, actual))
				{
				}
				
				colocarPieza(tablero, actual);
				
				int eliminadas =
					eliminarFilasCompletas(tablero);
				
				if (eliminadas > 0)
				{
					cout << "Filas eliminadas: "
						<< eliminadas << endl;
				}
				
				piezaFijada = true;
			}
			
			// PIEZA EN ESPERA
			else if (comando == 'h' || comando == 'H')
			{
				if (estaVaciaPila(pila))
				{
					Pieza guardar;
					inicializarPieza(
									 guardar,
									 actual.tipo
									 );
					
					apilar(pila, guardar);
					
					actual =
						obtenerSiguientePieza(cola);
				}
				else
				{
					Pieza guardada =
						desapilar(pila);
					
					Pieza guardar;
					inicializarPieza(
									 guardar,
									 actual.tipo
									 );
					
					apilar(pila, guardar);
					
					inicializarPieza(
									 actual,
									 guardada.tipo
									 );
				}
				
				if (!puedeColocarse(tablero, actual))
				{
					cout << "GAME OVER" << endl;
					juegoTerminado = true;
				}
			}
			
			// SALIR
			else if (comando == 'q' || comando == 'Q')
			{
				juegoTerminado = true;
			}
		}
	}
	
	liberarTablero(tablero);
	
	return 0;
}
