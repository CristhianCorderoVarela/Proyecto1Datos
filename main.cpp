#include <iostream>
#include "ColaPiezas.h"

using namespace std;

int main()
{
	ColaPiezas cola;
	
	inicializarCola(cola);
	
	Pieza p1;
	p1.tipo = 'T';
	
	Pieza p2;
	p2.tipo = 'I';
	
	Pieza p3;
	p3.tipo = 'L';
	
	encolar(cola, p1);
	encolar(cola, p2);
	encolar(cola, p3);
	
	Pieza actual;
	
	actual = desencolar(cola);
	cout << "Sale: " << actual.tipo << endl;
	
	actual = desencolar(cola);
	cout << "Sale: " << actual.tipo << endl;
	
	actual = desencolar(cola);
	cout << "Sale: " << actual.tipo << endl;
	
	return 0;
}
