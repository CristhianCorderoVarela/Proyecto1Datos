#ifndef INTERFAZ_H
#define INTERFAZ_H

#include <SFML/Graphics.hpp>
#include "Tablero.h"
#include "Pieza.h"
#include "ColaPiezas.h"
#include "PilaEspera.h"

sf::Color obtenerColorPieza(char tipo);

void dibujarTablero(
					sf::RenderWindow &ventana,
					Tablero tablero,
					Pieza pieza
					);

void dibujarProximas(
					 sf::RenderWindow &ventana,
					 ColaPiezas cola
					 );

void dibujarEspera(
				   sf::RenderWindow &ventana,
				   PilaEspera pila
				   );

void dibujarInformacion(
						sf::RenderWindow &ventana,
						sf::Font &fuente,
						int puntaje,
						int lineasTotales
						);

void dibujarControlesReplay(
							sf::RenderWindow &ventana,
							sf::Font &fuente,
							bool juegoTerminado,
							bool modoReplay,
							bool replayAutomatico
							);


void dibujarPantallaInicio(
						   sf::RenderWindow &ventana,
						   sf::Font &fuente
						   );

void dibujarPantallaPausa(
						  sf::RenderWindow &ventana,
						  sf::Font &fuente
						  );
#endif
