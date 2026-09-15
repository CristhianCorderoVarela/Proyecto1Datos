#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Tablero.h"
#include "Pieza.h"
#include "ColaPiezas.h"
#include "Interfaz.h"
#include "PilaEspera.h"

using namespace std;

bool fijarYCrearNuevaPieza(
						   Tablero &tablero,
						   ColaPiezas &cola,
						   Pieza &pieza)
{
	// Fijar la pieza que ya no puede bajar
	colocarPieza(tablero, pieza);
	
	// Revisar si se completaron filas
	int eliminadas = eliminarFilasCompletas(tablero);
	
	if (eliminadas > 0)
	{
		cout << "Filas eliminadas: "
			<< eliminadas << endl;
	}
	
	// Obtener la siguiente pieza
	pieza = obtenerSiguientePieza(cola);
	
	// Mantener al menos 3 piezas futuras
	asegurarProximasPiezas(cola);
	
	// Verificar si la nueva pieza puede aparecer
	if (!puedeColocarse(tablero, pieza))
	{
		return false;
	}
	
	return true;
}

int main()
{
	srand(time(nullptr));
	
	// ==========================================
	// TABLERO
	// ==========================================
	
	Tablero tablero;
	inicializarTablero(tablero);
	
	// ==========================================
	// COLA DE PIEZAS
	// ==========================================
	
	ColaPiezas cola;
	inicializarCola(cola);
	generarBolsa(cola);
	
	// ==========================================
	// PILA DE ESPERA
	// ==========================================
	
	PilaEspera pila;
	inicializarPila(pila);
	
	// ==========================================
	// PRIMERA PIEZA
	// ==========================================
	
	Pieza pieza;
	pieza = obtenerSiguientePieza(cola);
	
	asegurarProximasPiezas(cola);
	
	// ==========================================
	// VENTANA
	// ==========================================
	
	sf::RenderWindow ventana(
							 sf::VideoMode(450, 550),
							 "Tetris - Proyecto I"
							 );
	
	// ==========================================
	// CONTROL DEL TIEMPO DE CAIDA
	// ==========================================
	
	sf::Clock relojCaida;
	
	float tiempoCaida = 0.6f;
	
	bool juegoTerminado = false;
	
	// ==========================================
	// CICLO PRINCIPAL
	// ==========================================
	
	while (ventana.isOpen())
	{
		sf::Event evento;
		
		while (ventana.pollEvent(evento))
		{
			// CERRAR VENTANA
			if (evento.type == sf::Event::Closed)
			{
				ventana.close();
			}
			
			// CONTROLES DEL JUEGO
			if (evento.type == sf::Event::KeyPressed &&
				!juegoTerminado)
			{
				// ==================================
				// IZQUIERDA
				// ==================================
				
				if (evento.key.code == sf::Keyboard::A)
				{
					moverPiezaHorizontal(
										 tablero,
										 pieza,
										 -1
										 );
				}
				
				// ==================================
				// DERECHA
				// ==================================
				
				else if (evento.key.code == sf::Keyboard::D)
				{
					moverPiezaHorizontal(
										 tablero,
										 pieza,
										 1
										 );
				}
				
				// ==================================
				// BAJAR UNA FILA
				// ==================================
				
				else if (evento.key.code == sf::Keyboard::S)
				{
					if (!bajarPieza(tablero, pieza))
					{
						if (!fijarYCrearNuevaPieza(
												   tablero,
												   cola,
												   pieza))
						{
							juegoTerminado = true;
							
							ventana.setTitle(
											 "GAME OVER - Tetris"
											 );
						}
					}
					
					relojCaida.restart();
				}
				
				// ==================================
				// ROTAR
				// ==================================
				
				else if (evento.key.code == sf::Keyboard::W)
				{
					rotarPiezaValida(
									 tablero,
									 pieza
									 );
				}
				
				// ==================================
				// PIEZA EN ESPERA - HOLD
				// ==================================
				
				else if (evento.key.code == sf::Keyboard::H)
				{
					// Si no tenemos ninguna pieza guardada
					if (estaVaciaPila(pila))
					{
						Pieza guardar;
						
						inicializarPieza(
										 guardar,
										 pieza.tipo
										 );
						
						apilar(
							   pila,
							   guardar
							   );
						
						// Sacamos una nueva pieza
						pieza =
							obtenerSiguientePieza(cola);
						
						asegurarProximasPiezas(cola);
					}
					else
					{
						// Sacar la pieza que estaba guardada
						Pieza guardada =
							desapilar(pila);
						
						// Guardar la pieza actual
						Pieza guardar;
						
						inicializarPieza(
										 guardar,
										 pieza.tipo
										 );
						
						apilar(
							   pila,
							   guardar
							   );
						
						// La pieza guardada se convierte
						// en la nueva pieza actual
						inicializarPieza(
										 pieza,
										 guardada.tipo
										 );
					}
					
					// Verificar que la nueva pieza
					// pueda aparecer
					if (!puedeColocarse(
										tablero,
										pieza))
					{
						juegoTerminado = true;
						
						ventana.setTitle(
										 "GAME OVER - Tetris"
										 );
					}
										
										relojCaida.restart();
				}
				
				// ==================================
				// CAIDA COMPLETA
				// ==================================
				
				else if (evento.key.code == sf::Keyboard::X)
				{
					while (bajarPieza(
									  tablero,
									  pieza))
					{
					}
									  
									  if (!fijarYCrearNuevaPieza(
																 tablero,
																 cola,
																 pieza))
									  {
										  juegoTerminado = true;
										  
										  ventana.setTitle(
														   "GAME OVER - Tetris"
														   );
									  }
																 
																 relojCaida.restart();
				}
				
				// ==================================
				// CERRAR CON ESC
				// ==================================
				
				else if (evento.key.code ==
						 sf::Keyboard::Escape)
				{
					ventana.close();
				}
			}
		}
		
		// ==========================================
		// CAIDA AUTOMATICA
		// ==========================================
		
		if (!juegoTerminado &&
			relojCaida.getElapsedTime().asSeconds()
			>= tiempoCaida)
		{
			if (!bajarPieza(tablero, pieza))
			{
				if (!fijarYCrearNuevaPieza(
										   tablero,
										   cola,
										   pieza))
				{
					juegoTerminado = true;
					
					ventana.setTitle(
									 "GAME OVER - Tetris"
									 );
				}
			}
			
			relojCaida.restart();
		}
		
		// ==========================================
		// DIBUJAR
		// ==========================================
		
		ventana.clear(
					  sf::Color::Black
					  );
		
		// Tablero y pieza actual
		dibujarTablero(
					   ventana,
					   tablero,
					   pieza
					   );
		
		// Proximas 3 piezas
		dibujarProximas(
						ventana,
						cola
						);
		
		// Pieza en espera
		dibujarEspera(
					  ventana,
					  pila
					  );
		
		ventana.display();
	}
	
	// ==========================================
	// LIBERAR MEMORIA
	// ==========================================
	
	if (!estaVaciaPila(pila))
	{
		desapilar(pila);
	}
	
	liberarTablero(tablero);
	
	return 0;
}
