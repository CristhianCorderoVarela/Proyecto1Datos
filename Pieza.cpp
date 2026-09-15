#include "Pieza.h"

void inicializarPieza(Pieza &pieza, char tipo)
{
	pieza.tipo = tipo;
	pieza.fila = 0;
	pieza.columna = 3;
	pieza.orientacion = 0;
	pieza.numeroBolsa = 0;
}

void obtenerBloques(Pieza pieza, int bloques[4][2])
{

	for (int i = 0; i < 4; i++)
	{
		bloques[i][0] = -1;
		bloques[i][1] = -1;
	}
	

	// PIEZA I

	if (pieza.tipo == 'I')
	{
		if (pieza.orientacion == 0 || pieza.orientacion == 2)
		{
			bloques[0][0] = pieza.fila;
			bloques[0][1] = pieza.columna;
			
			bloques[1][0] = pieza.fila;
			bloques[1][1] = pieza.columna + 1;
			
			bloques[2][0] = pieza.fila;
			bloques[2][1] = pieza.columna + 2;
			
			bloques[3][0] = pieza.fila;
			bloques[3][1] = pieza.columna + 3;
		}
		else
		{
			bloques[0][0] = pieza.fila;
			bloques[0][1] = pieza.columna;
			
			bloques[1][0] = pieza.fila + 1;
			bloques[1][1] = pieza.columna;
			
			bloques[2][0] = pieza.fila + 2;
			bloques[2][1] = pieza.columna;
			
			bloques[3][0] = pieza.fila + 3;
			bloques[3][1] = pieza.columna;
		}
	}
	
	
	// PIEZA O

	else if (pieza.tipo == 'O')
	{
		bloques[0][0] = pieza.fila;
		bloques[0][1] = pieza.columna;
		
		bloques[1][0] = pieza.fila;
		bloques[1][1] = pieza.columna + 1;
		
		bloques[2][0] = pieza.fila + 1;
		bloques[2][1] = pieza.columna;
		
		bloques[3][0] = pieza.fila + 1;
		bloques[3][1] = pieza.columna + 1;
	}
	
	
	// PIEZA T

	else if (pieza.tipo == 'T')
	{
		if (pieza.orientacion == 0)
		{
			// T T T
			//   T
			bloques[0][0] = pieza.fila;
			bloques[0][1] = pieza.columna;
			
			bloques[1][0] = pieza.fila;
			bloques[1][1] = pieza.columna + 1;
			
			bloques[2][0] = pieza.fila;
			bloques[2][1] = pieza.columna + 2;
			
			bloques[3][0] = pieza.fila + 1;
			bloques[3][1] = pieza.columna + 1;
		}
		else if (pieza.orientacion == 1)
		{
			//   T
			// T T
			//   T
			bloques[0][0] = pieza.fila;
			bloques[0][1] = pieza.columna + 1;
			
			bloques[1][0] = pieza.fila + 1;
			bloques[1][1] = pieza.columna;
			
			bloques[2][0] = pieza.fila + 1;
			bloques[2][1] = pieza.columna + 1;
			
			bloques[3][0] = pieza.fila + 2;
			bloques[3][1] = pieza.columna + 1;
		}
		else if (pieza.orientacion == 2)
		{
			//   T
			// T T T
			bloques[0][0] = pieza.fila;
			bloques[0][1] = pieza.columna + 1;
			
			bloques[1][0] = pieza.fila + 1;
			bloques[1][1] = pieza.columna;
			
			bloques[2][0] = pieza.fila + 1;
			bloques[2][1] = pieza.columna + 1;
			
			bloques[3][0] = pieza.fila + 1;
			bloques[3][1] = pieza.columna + 2;
		}
		else
		{
			// T
			// T T
			// T
			bloques[0][0] = pieza.fila;
			bloques[0][1] = pieza.columna;
			
			bloques[1][0] = pieza.fila + 1;
			bloques[1][1] = pieza.columna;
			
			bloques[2][0] = pieza.fila + 1;
			bloques[2][1] = pieza.columna + 1;
			
			bloques[3][0] = pieza.fila + 2;
			bloques[3][1] = pieza.columna;
		}
	}
	

	// PIEZA S
	
	else if (pieza.tipo == 'S')
	{
		if (pieza.orientacion == 0 || pieza.orientacion == 2)
		{
			//   S S
			// S S
			bloques[0][0] = pieza.fila;
			bloques[0][1] = pieza.columna + 1;
			
			bloques[1][0] = pieza.fila;
			bloques[1][1] = pieza.columna + 2;
			
			bloques[2][0] = pieza.fila + 1;
			bloques[2][1] = pieza.columna;
			
			bloques[3][0] = pieza.fila + 1;
			bloques[3][1] = pieza.columna + 1;
		}
		else
		{
			// S
			// S S
			//   S
			bloques[0][0] = pieza.fila;
			bloques[0][1] = pieza.columna;
			
			bloques[1][0] = pieza.fila + 1;
			bloques[1][1] = pieza.columna;
			
			bloques[2][0] = pieza.fila + 1;
			bloques[2][1] = pieza.columna + 1;
			
			bloques[3][0] = pieza.fila + 2;
			bloques[3][1] = pieza.columna + 1;
		}
	}
	

	// PIEZA Z
	
	else if (pieza.tipo == 'Z')
	{
		if (pieza.orientacion == 0 || pieza.orientacion == 2)
		{
			// Z Z
			//   Z Z
			bloques[0][0] = pieza.fila;
			bloques[0][1] = pieza.columna;
			
			bloques[1][0] = pieza.fila;
			bloques[1][1] = pieza.columna + 1;
			
			bloques[2][0] = pieza.fila + 1;
			bloques[2][1] = pieza.columna + 1;
			
			bloques[3][0] = pieza.fila + 1;
			bloques[3][1] = pieza.columna + 2;
		}
		else
		{
			//   Z
			// Z Z
			// Z
			bloques[0][0] = pieza.fila;
			bloques[0][1] = pieza.columna + 1;
			
			bloques[1][0] = pieza.fila + 1;
			bloques[1][1] = pieza.columna;
			
			bloques[2][0] = pieza.fila + 1;
			bloques[2][1] = pieza.columna + 1;
			
			bloques[3][0] = pieza.fila + 2;
			bloques[3][1] = pieza.columna;
		}
	}
	

	// PIEZA J
	
	else if (pieza.tipo == 'J')
	{
		if (pieza.orientacion == 0)
		{
			// J
			// J J J
			bloques[0][0] = pieza.fila;
			bloques[0][1] = pieza.columna;
			
			bloques[1][0] = pieza.fila + 1;
			bloques[1][1] = pieza.columna;
			
			bloques[2][0] = pieza.fila + 1;
			bloques[2][1] = pieza.columna + 1;
			
			bloques[3][0] = pieza.fila + 1;
			bloques[3][1] = pieza.columna + 2;
		}
		else if (pieza.orientacion == 1)
		{
			// J J
			// J
			// J
			bloques[0][0] = pieza.fila;
			bloques[0][1] = pieza.columna;
			
			bloques[1][0] = pieza.fila;
			bloques[1][1] = pieza.columna + 1;
			
			bloques[2][0] = pieza.fila + 1;
			bloques[2][1] = pieza.columna;
			
			bloques[3][0] = pieza.fila + 2;
			bloques[3][1] = pieza.columna;
		}
		else if (pieza.orientacion == 2)
		{
			// J J J
			//     J
			bloques[0][0] = pieza.fila;
			bloques[0][1] = pieza.columna;
			
			bloques[1][0] = pieza.fila;
			bloques[1][1] = pieza.columna + 1;
			
			bloques[2][0] = pieza.fila;
			bloques[2][1] = pieza.columna + 2;
			
			bloques[3][0] = pieza.fila + 1;
			bloques[3][1] = pieza.columna + 2;
		}
		else
		{
			//   J
			//   J
			// J J
			bloques[0][0] = pieza.fila;
			bloques[0][1] = pieza.columna + 1;
			
			bloques[1][0] = pieza.fila + 1;
			bloques[1][1] = pieza.columna + 1;
			
			bloques[2][0] = pieza.fila + 2;
			bloques[2][1] = pieza.columna;
			
			bloques[3][0] = pieza.fila + 2;
			bloques[3][1] = pieza.columna + 1;
		}
	}
	

	// PIEZA L
	
	else if (pieza.tipo == 'L')
	{
		if (pieza.orientacion == 0)
		{
			//     L
			// L L L
			bloques[0][0] = pieza.fila;
			bloques[0][1] = pieza.columna + 2;
			
			bloques[1][0] = pieza.fila + 1;
			bloques[1][1] = pieza.columna;
			
			bloques[2][0] = pieza.fila + 1;
			bloques[2][1] = pieza.columna + 1;
			
			bloques[3][0] = pieza.fila + 1;
			bloques[3][1] = pieza.columna + 2;
		}
		else if (pieza.orientacion == 1)
		{
			// L
			// L
			// L L
			bloques[0][0] = pieza.fila;
			bloques[0][1] = pieza.columna;
			
			bloques[1][0] = pieza.fila + 1;
			bloques[1][1] = pieza.columna;
			
			bloques[2][0] = pieza.fila + 2;
			bloques[2][1] = pieza.columna;
			
			bloques[3][0] = pieza.fila + 2;
			bloques[3][1] = pieza.columna + 1;
		}
		else if (pieza.orientacion == 2)
		{
			// L L L
			// L
			bloques[0][0] = pieza.fila;
			bloques[0][1] = pieza.columna;
			
			bloques[1][0] = pieza.fila;
			bloques[1][1] = pieza.columna + 1;
			
			bloques[2][0] = pieza.fila;
			bloques[2][1] = pieza.columna + 2;
			
			bloques[3][0] = pieza.fila + 1;
			bloques[3][1] = pieza.columna;
		}
		else
		{
			// L L
			//   L
			//   L
			bloques[0][0] = pieza.fila;
			bloques[0][1] = pieza.columna;
			
			bloques[1][0] = pieza.fila;
			bloques[1][1] = pieza.columna + 1;
			
			bloques[2][0] = pieza.fila + 1;
			bloques[2][1] = pieza.columna + 1;
			
			bloques[3][0] = pieza.fila + 2;
			bloques[3][1] = pieza.columna + 1;
		}
	}
}

void rotarPieza(Pieza &pieza)
{
	pieza.orientacion++;
	
	if (pieza.orientacion > 3)
	{
		pieza.orientacion = 0;
	}
}
