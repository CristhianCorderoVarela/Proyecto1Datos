#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Tablero.h"
#include "Pieza.h"
#include "ColaPiezas.h"
#include "Interfaz.h"

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
	asegurarProximasPiezas(cola);
	
	// Verificar si puede aparecer
	if (!puedeColocarse(tablero, pieza))
	{
		return false;
	}
	
	return true;
}

int main()
{
	srand(time(nullptr));
	
	// TABLERO
	Tablero tablero;
	inicializarTablero(tablero);
	
	// COLA DE PIEZAS
	ColaPiezas cola;
	inicializarCola(cola);
	generarBolsa(cola);
	
	// PRIMERA PIEZA
	Pieza pieza;
	pieza = obtenerSiguientePieza(cola);
	asegurarProximasPiezas(cola);
	
	// VENTANA
	sf::RenderWindow ventana(
							 sf::VideoMode(450, 550),
							 "Tetris - Proyecto I"
							 );
	
	// CONTROL DEL TIEMPO DE CAIDA
	sf::Clock relojCaida;
	
	float tiempoCaida = 0.6f;
	
	bool juegoTerminado = false;
	
	while (ventana.isOpen())
	{
		sf::Event evento;
		
		while (ventana.pollEvent(evento))
		{
			if (evento.type == sf::Event::Closed)
			{
				ventana.close();
			}
			
			if (evento.type == sf::Event::KeyPressed &&
				!juegoTerminado)
			{
				// IZQUIERDA
				if (evento.key.code == sf::Keyboard::A)
				{
					moverPiezaHorizontal(
										 tablero,
										 pieza,
										 -1
										 );
				}
				
				// DERECHA
				else if (evento.key.code == sf::Keyboard::D)
				{
					moverPiezaHorizontal(
										 tablero,
										 pieza,
										 1
										 );
				}
				
				// BAJAR UNA FILA
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
				
				// ROTAR
				else if (evento.key.code == sf::Keyboard::W)
				{
					rotarPiezaValida(
									 tablero,
									 pieza
									 );
				}
				
				// CAIDA COMPLETA
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
				
				// CERRAR
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
		
		dibujarTablero(
					   ventana,
					   tablero,
					   pieza
					   );
		
		dibujarProximas(
						ventana,
						cola
						);
		
		ventana.display();
	}
	
	liberarTablero(tablero);
	
	return 0;
}
