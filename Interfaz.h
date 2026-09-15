#ifndef INTERFAZ_H
#define INTERFAZ_H

#include <SFML/Graphics.hpp>
#include "Tablero.h"
#include "Pieza.h"
#include "ColaPiezas.h"

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

#endif
