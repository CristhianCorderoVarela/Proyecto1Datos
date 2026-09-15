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



void dibujarMiniPieza(
					  sf::RenderWindow &ventana,
					  char tipo,
					  float posicionX,
					  float posicionY)
{
	Pieza pieza;
	
	inicializarPieza(
					 pieza,
					 tipo
					 );
	
	int bloques[4][2];
	
	obtenerBloques(
				   pieza,
				   bloques
				   );
	
	int filaMinima = bloques[0][0];
	int columnaMinima = bloques[0][1];
	
	for (int i = 1; i < 4; i++)
	{
		if (bloques[i][0] < filaMinima)
		{
			filaMinima = bloques[i][0];
		}
		
		if (bloques[i][1] < columnaMinima)
		{
			columnaMinima = bloques[i][1];
		}
	}
	
	const int TAM_PREVIA = 16;
	
	for (int i = 0; i < 4; i++)
	{
		int fila =
			bloques[i][0] - filaMinima;
			
			int columna =
				bloques[i][1] - columnaMinima;
				
				sf::RectangleShape bloque(
										  sf::Vector2f(
													   TAM_PREVIA - 1,
													   TAM_PREVIA - 1
													   )
										  );
				
				bloque.setPosition(
								   posicionX +
								   columna * TAM_PREVIA,
								   posicionY +
								   fila * TAM_PREVIA
								   );
				
				bloque.setFillColor(
									obtenerColorPieza(tipo)
									);
				
				ventana.draw(bloque);
	}
}

void dibujarProximas(
					 sf::RenderWindow &ventana,
					 ColaPiezas cola)
{
	NodoPieza *actual =
		cola.frente;
	
	float panelX = 300;
	float panelY = 70;
	
	for (int i = 0;
	i < 3 && actual != nullptr;
	i++)
	{
		// Marco para cada pieza
		sf::RectangleShape marco(
								 sf::Vector2f(
											  110,
											  100
											  )
								 );
		
		marco.setPosition(
						  panelX,
						  panelY + i * 130
						  );
		
		marco.setFillColor(
						   sf::Color(20, 20, 20)
						   );
		
		marco.setOutlineThickness(2);
		
		marco.setOutlineColor(
							  sf::Color(80, 80, 80)
							  );
		
		ventana.draw(marco);
		
		// Dibujar la pieza
		dibujarMiniPieza(
						 ventana,
						 actual->pieza.tipo,
						 panelX + 22,
						 panelY + 28 + i * 130
						 );
		
		actual =
			actual->siguiente;
	}
}
