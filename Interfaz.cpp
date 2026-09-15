#include "Interfaz.h"

const int TAM_CELDA = 24;
const int INICIO_X = 25;
const int INICIO_Y = 25;

sf::Color obtenerColorPieza(char tipo)
{
	if (tipo == 'I')
		return sf::Color::Cyan;
	
	if (tipo == 'O')
		return sf::Color::Yellow;
	
	if (tipo == 'T')
		return sf::Color(160, 32, 240);
	
	if (tipo == 'S')
		return sf::Color::Green;
	
	if (tipo == 'Z')
		return sf::Color::Red;
	
	if (tipo == 'J')
		return sf::Color::Blue;
	
	if (tipo == 'L')
		return sf::Color(255, 140, 0);
	
	return sf::Color::White;
}

void dibujarTablero(
					sf::RenderWindow &ventana,
					Tablero tablero,
					Pieza pieza)
{
	NodoFila *actual = tablero.inicio;
	
	for (int fila = 0; fila < 20; fila++)
	{
		for (int columna = 0; columna < 10; columna++)
		{
			sf::RectangleShape celda(
									 sf::Vector2f(
												  TAM_CELDA - 1,
												  TAM_CELDA - 1
												  )
									 );
			
			celda.setPosition(
							  INICIO_X + columna * TAM_CELDA,
							  INICIO_Y + fila * TAM_CELDA
							  );
			
			if (actual->celdas[columna] == 0)
			{
				celda.setFillColor(
								   sf::Color(25, 25, 25)
								   );
			}
			else
			{
				celda.setFillColor(
								   sf::Color(150, 150, 150)
								   );
			}
			
			ventana.draw(celda);
		}
		
		actual = actual->siguiente;
	}
	
	int bloques[4][2];
	
	obtenerBloques(
				   pieza,
				   bloques
				   );
	
	for (int i = 0; i < 4; i++)
	{
		int fila = bloques[i][0];
		int columna = bloques[i][1];
		
		sf::RectangleShape bloque(
								  sf::Vector2f(
											   TAM_CELDA - 1,
											   TAM_CELDA - 1
											   )
								  );
		
		bloque.setPosition(
						   INICIO_X + columna * TAM_CELDA,
						   INICIO_Y + fila * TAM_CELDA
						   );
		
		bloque.setFillColor(
							obtenerColorPieza(
											  pieza.tipo
											  )
							);
		
		ventana.draw(bloque);
	}
}
