#include <SFML/Graphics.hpp>

#include "Tablero.h"
#include "Pieza.h"
#include "Interfaz.h"

int main()
{
	Tablero tablero;
	inicializarTablero(tablero);
	
	Pieza pieza;
	inicializarPieza(
					 pieza,
					 'T'
					 );
	
	sf::RenderWindow ventana(
							 sf::VideoMode(450, 550),
							 "Tetris - Proyecto I"
							 );
	
	while (ventana.isOpen())
	{
		sf::Event evento;
		
		while (ventana.pollEvent(evento))
		{
			if (evento.type == sf::Event::Closed)
			{
				ventana.close();
			}
			
			if (evento.type == sf::Event::KeyPressed)
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
				
				// BAJAR
				else if (evento.key.code == sf::Keyboard::S)
				{
					bajarPieza(
							   tablero,
							   pieza
							   );
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
									  pieza
									  ))
					{
					}
				}
				
				// CERRAR CON ESC
				else if (evento.key.code == sf::Keyboard::Escape)
				{
					ventana.close();
				}
			}
		}
		
		ventana.clear(
					  sf::Color::Black
					  );
		
		dibujarTablero(
					   ventana,
					   tablero,
					   pieza
					   );
		
		ventana.display();
	}
	
	liberarTablero(tablero);
	
	return 0;
}
