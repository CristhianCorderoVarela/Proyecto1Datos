#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Tablero.h"
#include "Pieza.h"
#include "ColaPiezas.h"
#include "Interfaz.h"
#include "PilaEspera.h"
#include "Eventos.h"

using namespace std;

bool fijarYCrearNuevaPieza(
						   Tablero &tablero,
						   ColaPiezas &cola,
						   Pieza &pieza,
						   int &puntaje,
						   int &lineasTotales)
{
	// Fijar la pieza que ya no puede bajar
	colocarPieza(tablero, pieza);
	
	// Revisar si se completaron filas
	int eliminadas =
		eliminarFilasCompletas(tablero);
	
	if (eliminadas > 0)
	{
		lineasTotales += eliminadas;
		
		puntaje += eliminadas * 100;
		
		cout << "Filas eliminadas: "
			<< eliminadas << endl;
		
		cout << "Lineas totales: "
			<< lineasTotales << endl;
		
		cout << "Puntaje: "
			<< puntaje << endl;
	}
	
	// Obtener la siguiente pieza
	pieza =
		obtenerSiguientePieza(cola);
	
	// Mantener al menos 3 piezas futuras
	asegurarProximasPiezas(cola);
	
	// Verificar si la nueva pieza puede aparecer
	if (!puedeColocarse(
						tablero,
						pieza))
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
	
	pieza =
		obtenerSiguientePieza(cola);
	
	asegurarProximasPiezas(cola);
	
	// ==========================================
	// VENTANA
	// ==========================================
	
	sf::RenderWindow ventana(
							 sf::VideoMode(450, 550),
							 "Tetris - Proyecto I"
							 );
	
	sf::Font fuente;
	
	if (!fuente.loadFromFile(
							 "C:/Windows/Fonts/arial.ttf"))
	{
		cout << "Error al cargar la fuente"
			<< endl;
	}
							 
							 // ==========================================
							 // CONTROL DEL TIEMPO DE CAIDA
							 // ==========================================
							 
							 sf::Clock relojCaida;
							 
							 float tiempoCaida = 0.6f;
							 
							 bool juegoTerminado = false;
							 
							 // ==========================================
							 // PUNTAJE Y LINEAS
							 // ==========================================
							 
							 int puntaje = 0;
							 int lineasTotales = 0;
							 
							 // ==========================================
							 // COLA DE EVENTOS
							 // ==========================================
							 
							 ColaEventos colaEventos;
							 
							 inicializarColaEventos(
													colaEventos
													);
							 
							 // ------------------------------------------
							 // EVENTO 1
							 // PIEZA ESPECIAL EN 7 LINEAS
							 // ------------------------------------------
							 
							 Evento eventoEspecial;
							 
							 eventoEspecial.tipo =
								 PIEZA_ESPECIAL;
							 
							 eventoEspecial.momento = 7;
							 
							 insertarEvento(
											colaEventos,
											eventoEspecial
											);
							 
							 // ------------------------------------------
							 // EVENTO 2
							 // AUMENTAR VELOCIDAD EN 3 LINEAS
							 // ------------------------------------------
							 
							 Evento eventoVelocidad;
							 
							 eventoVelocidad.tipo =
								 AUMENTAR_VELOCIDAD;
							 
							 eventoVelocidad.momento = 3;
							 
							 insertarEvento(
											colaEventos,
											eventoVelocidad
											);
							 
							 // ------------------------------------------
							 // EVENTO 3
							 // BONO DE PUNTOS EN 5 LINEAS
							 // ------------------------------------------
							 
							 Evento eventoBono;
							 
							 eventoBono.tipo =
								 BONO_PUNTOS;
							 
							 eventoBono.momento = 5;
							 
							 insertarEvento(
											colaEventos,
											eventoBono
											);
							 
							 // ------------------------------------------
							 // MOSTRAR EVENTOS PARA PROBAR EL ORDEN
							 // ------------------------------------------
							 
							 cout << "EVENTOS PROGRAMADOS:"
								 << endl;
							 
							 mostrarEventos(
											colaEventos
											);
							 
							 // ==========================================
							 // CICLO PRINCIPAL
							 // ==========================================
							 
							 while (ventana.isOpen())
							 {
								 sf::Event evento;
								 
								 while (ventana.pollEvent(evento))
								 {
									 // ==================================
									 // CERRAR VENTANA
									 // ==================================
									 
									 if (evento.type ==
										 sf::Event::Closed)
									 {
										 ventana.close();
									 }
									 
									 // ==================================
									 // CONTROLES DEL JUEGO
									 // ==================================
									 
									 if (evento.type ==
										 sf::Event::KeyPressed &&
										 !juegoTerminado)
									 {
										 // ==============================
										 // IZQUIERDA
										 // ==============================
										 
										 if (evento.key.code ==
											 sf::Keyboard::A)
										 {
											 moverPiezaHorizontal(
																  tablero,
																  pieza,
																  -1
																  );
										 }
										 
										 // ==============================
										 // DERECHA
										 // ==============================
										 
										 else if (evento.key.code ==
												  sf::Keyboard::D)
										 {
											 moverPiezaHorizontal(
																  tablero,
																  pieza,
																  1
																  );
										 }
										 
										 // ==============================
										 // BAJAR UNA FILA
										 // ==============================
										 
										 else if (evento.key.code ==
												  sf::Keyboard::S)
										 {
											 if (!bajarPieza(
															 tablero,
															 pieza))
											 {
												 if (!fijarYCrearNuevaPieza(
																			tablero,
																			cola,
																			pieza,
																			puntaje,
																			lineasTotales))
												 {
													 juegoTerminado = true;
													 
													 ventana.setTitle(
																	  "GAME OVER - Tetris"
																	  );
												 }
											 }
															 
															 relojCaida.restart();
										 }
										 
										 // ==============================
										 // ROTAR
										 // ==============================
										 
										 else if (evento.key.code ==
												  sf::Keyboard::W)
										 {
											 rotarPiezaValida(
															  tablero,
															  pieza
															  );
										 }
										 
										 // ==============================
										 // PIEZA EN ESPERA - HOLD
										 // ==============================
										 
										 else if (evento.key.code ==
												  sf::Keyboard::H)
										 {
											 // Si la pila esta vacia
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
												 
												 pieza =
													 obtenerSiguientePieza(
																		   cola
																		   );
												 
												 asegurarProximasPiezas(
																		cola
																		);
											 }
											 else
											 {
												 // Sacar la pieza guardada
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
												 
												 // Convertir la guardada
												 // en la nueva pieza actual
												 inicializarPieza(
																  pieza,
																  guardada.tipo
																  );
											 }
											 
											 // Verificar si puede aparecer
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
										 
										 // ==============================
										 // CAIDA COMPLETA
										 // ==============================
										 
										 else if (evento.key.code ==
												  sf::Keyboard::X)
										 {
											 while (bajarPieza(
															   tablero,
															   pieza))
											 {
											 }
															   
															   if (!fijarYCrearNuevaPieza(
																						  tablero,
																						  cola,
																						  pieza,
																						  puntaje,
																						  lineasTotales))
															   {
																   juegoTerminado = true;
																   
																   ventana.setTitle(
																					"GAME OVER - Tetris"
																					);
															   }
																						  
																						  relojCaida.restart();
										 }
										 
										 // ==============================
										 // CERRAR CON ESC
										 // ==============================
										 
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
									 relojCaida
									 .getElapsedTime()
									 .asSeconds()
									 >= tiempoCaida)
								 {
									 if (!bajarPieza(
													 tablero,
													 pieza))
									 {
										 if (!fijarYCrearNuevaPieza(
																	tablero,
																	cola,
																	pieza,
																	puntaje,
																	lineasTotales))
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
								 
								 // Puntaje y lineas
								 dibujarInformacion(
													ventana,
													fuente,
													puntaje,
													lineasTotales
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
							 
							 liberarColaEventos(
												colaEventos
												);
							 
							 liberarTablero(
											tablero
											);
							 
							 return 0;
}
