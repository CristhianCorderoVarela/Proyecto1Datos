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

void procesarEventos(
					 ColaEventos &colaEventos,
					 int lineasTotales,
					 int &puntaje,
					 float &tiempoCaida,
					 bool &especialPendiente)
{
	Evento proximoEvento;
	
	while (
		   verProximoEvento(
							colaEventos,
							proximoEvento
							)
		   &&
		   lineasTotales >=
		   proximoEvento.momento)
	{
		Evento eventoActivado;
		
		extraerEvento(
					  colaEventos,
					  eventoActivado
					  );
		
		if (eventoActivado.tipo ==
			AUMENTAR_VELOCIDAD)
		{
			tiempoCaida = 0.45f;
			
			cout
				<< "EVENTO ACTIVADO: "
				<< "AUMENTAR VELOCIDAD"
				<< endl;
			
			cout
				<< "Nuevo tiempo de caida: "
				<< tiempoCaida
				<< " segundos"
				<< endl;
		}
		
		else if (eventoActivado.tipo ==
				 BONO_PUNTOS)
		{
			puntaje += 500;
			
			cout
				<< "EVENTO ACTIVADO: "
				<< "BONO DE PUNTOS"
				<< endl;
			
			cout
				<< "Bono: +500 puntos"
				<< endl;
			
			cout
				<< "Puntaje total: "
				<< puntaje
				<< endl;
		}
		
		else if (eventoActivado.tipo ==
				 PIEZA_ESPECIAL)
		{
			especialPendiente = true;
			
			cout
				<< "EVENTO ACTIVADO: "
				<< "PIEZA ESPECIAL"
				<< endl;
			
			cout
				<< "La siguiente pieza "
				<< "sera especial"
				<< endl;
		}
	}
}

bool fijarYCrearNuevaPieza(
						   Tablero &tablero,
						   ColaPiezas &cola,
						   Pieza &pieza,
						   int &puntaje,
						   int &lineasTotales,
						   ColaEventos &colaEventos,
						   float &tiempoCaida,
						   bool &especialPendiente)
{
	bool eraEspecial =
		pieza.especial;
	
	colocarPieza(
				 tablero,
				 pieza
				 );
	
	int eliminadas =
		eliminarFilasCompletas(
							   tablero
							   );
	
	if (eliminadas > 0)
	{
		lineasTotales +=
			eliminadas;
		
		puntaje +=
			eliminadas * 100;
		
		cout
			<< "Filas eliminadas: "
			<< eliminadas
			<< endl;
		
		cout
			<< "Lineas totales: "
			<< lineasTotales
			<< endl;
		
		cout
			<< "Puntaje: "
			<< puntaje
			<< endl;
	}
	
	if (eraEspecial)
	{
		if (eliminarFilaInferiorOcupada(
										tablero))
		{
			cout
				<< "EFECTO ESPECIAL: "
				<< "fila eliminada"
				<< endl;
		}
	}
	
	procesarEventos(
					colaEventos,
					lineasTotales,
					puntaje,
					tiempoCaida,
					especialPendiente
					);
	
	pieza =
		obtenerSiguientePieza(
							  cola
							  );
	
	asegurarProximasPiezas(
						   cola
						   );
	
	if (especialPendiente)
	{
		pieza.especial = true;
		
		especialPendiente =
			false;
		
		cout
			<< "PIEZA ESPECIAL CREADA"
			<< endl;
	}
	
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
	
	Tablero tablero;
	inicializarTablero(tablero);
	
	ColaPiezas cola;
	inicializarCola(cola);
	generarBolsa(cola);
	
	PilaEspera pila;
	inicializarPila(pila);
	
	Pieza pieza;
	
	pieza =
		obtenerSiguientePieza(
							  cola
							  );
	
	asegurarProximasPiezas(
						   cola
						   );
	
	sf::RenderWindow ventana(
							 sf::VideoMode(450, 550),
							 "Tetris - Proyecto I"
							 );
	
	sf::Font fuente;
	
	if (!fuente.loadFromFile(
							 "C:/Windows/Fonts/arial.ttf"))
	{
		cout
			<< "Error al cargar la fuente"
			<< endl;
	}
							 
							 sf::Clock relojCaida;
							 
							 float tiempoCaida =
								 0.6f;
							 
							 bool juegoTerminado =
								 false;
							 
							 int puntaje =
								 0;
							 
							 int lineasTotales =
								 0;
							 
							 bool especialPendiente =
								 false;
							 
							 ColaEventos colaEventos;
							 
							 inicializarColaEventos(
													colaEventos
													);
							 
							 Evento eventoEspecial;
							 
							 eventoEspecial.tipo =
								 PIEZA_ESPECIAL;
							 
							 eventoEspecial.momento =
								 7;
							 
							 insertarEvento(
											colaEventos,
											eventoEspecial
											);
							 
							 Evento eventoVelocidad;
							 
							 eventoVelocidad.tipo =
								 AUMENTAR_VELOCIDAD;
							 
							 eventoVelocidad.momento =
								 3;
							 
							 insertarEvento(
											colaEventos,
											eventoVelocidad
											);
							 
							 Evento eventoBono;
							 
							 eventoBono.tipo =
								 BONO_PUNTOS;
							 
							 eventoBono.momento =
								 5;
							 
							 insertarEvento(
											colaEventos,
											eventoBono
											);
							 
							 cout
								 << "EVENTOS PROGRAMADOS:"
								 << endl;
							 
							 mostrarEventos(
											colaEventos
											);
							 
							 while (ventana.isOpen())
							 {
								 sf::Event evento;
								 
								 while (
										ventana.pollEvent(
														  evento
														  ))
								 {
									 if (evento.type ==
										 sf::Event::Closed)
									 {
										 ventana.close();
									 }
									 
									 if (
										 evento.type ==
										 sf::Event::KeyPressed
										 &&
										 !juegoTerminado)
									 {
										 if (
											 evento.key.code ==
											 sf::Keyboard::A)
										 {
											 moverPiezaHorizontal(
																  tablero,
																  pieza,
																  -1
																  );
										 }
											 
										 else if (
												  evento.key.code ==
												  sf::Keyboard::D)
											 {
											 moverPiezaHorizontal(
																  tablero,
																  pieza,
																  1
																  );
											 }
												  
										 else if (
												  evento.key.code ==
												  sf::Keyboard::S)
												  {
											 if (!bajarPieza(
															 tablero,
															 pieza))
											 {
												 if (
													 !fijarYCrearNuevaPieza(
																			tablero,
																			cola,
																			pieza,
																			puntaje,
																			lineasTotales,
																			colaEventos,
																			tiempoCaida,
																			especialPendiente
																			))
												 {
													 juegoTerminado =
														 true;
													 
													 ventana.setTitle(
																	  "GAME OVER - Tetris"
																	  );
												 }
											 }
															 
															 relojCaida.restart();
												  }
												  
										 else if (
												  evento.key.code ==
												  sf::Keyboard::W)
												  {
											 rotarPiezaValida(
															  tablero,
															  pieza
															  );
												  }
												  
										 else if (
												  evento.key.code ==
												  sf::Keyboard::H)
												  {
											 if (
												 estaVaciaPila(
															   pila
															   ))
											 {
												 Pieza guardar;
												 
												 inicializarPieza(
																  guardar,
																  pieza.tipo
																  );
												 
												 guardar.especial =
													 pieza.especial;
												 
												 guardar.numeroBolsa =
													 pieza.numeroBolsa;
												 
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
																   Pieza guardada =
																	   desapilar(
																				 pila
																				 );
																   
																   Pieza guardar;
																   
																   inicializarPieza(
																					guardar,
																					pieza.tipo
																					);
																   
																   guardar.especial =
																	   pieza.especial;
																   
																   guardar.numeroBolsa =
																	   pieza.numeroBolsa;
																   
																   apilar(
																		  pila,
																		  guardar
																		  );
																   
																   bool especialGuardada =
																	   guardada.especial;
																   
																   int bolsaGuardada =
																	   guardada.numeroBolsa;
																   
																   inicializarPieza(
																					pieza,
																					guardada.tipo
																					);
																   
																   pieza.especial =
																	   especialGuardada;
																   
																   pieza.numeroBolsa =
																	   bolsaGuardada;
															   }
															   
															   if (!puedeColocarse(
																				   tablero,
																				   pieza))
															   {
																   juegoTerminado =
																	   true;
																   
																   ventana.setTitle(
																					"GAME OVER - Tetris"
																					);
															   }
																				   
																				   relojCaida.restart();
												  }
												  
										 else if (
												  evento.key.code ==
												  sf::Keyboard::X)
												  {
											 while (
													bajarPieza(
															   tablero,
															   pieza
															   ))
											 {
											 }
															   
															   if (
																   !fijarYCrearNuevaPieza(
																						  tablero,
																						  cola,
																						  pieza,
																						  puntaje,
																						  lineasTotales,
																						  colaEventos,
																						  tiempoCaida,
																						  especialPendiente
																						  ))
															   {
																   juegoTerminado =
																	   true;
																   
																   ventana.setTitle(
																					"GAME OVER - Tetris"
																					);
															   }
																						  
																						  relojCaida.restart();
												  }
												  
										 else if (
												  evento.key.code ==
												  sf::Keyboard::Escape)
												  {
											 ventana.close();
												  }
									 }
								 }
														  
														  if (
															  !juegoTerminado
															  &&
															  relojCaida
															  .getElapsedTime()
															  .asSeconds()
															  >= tiempoCaida)
														  {
															  if (!bajarPieza(
																			  tablero,
																			  pieza))
															  {
																  if (
																	  !fijarYCrearNuevaPieza(
																							 tablero,
																							 cola,
																							 pieza,
																							 puntaje,
																							 lineasTotales,
																							 colaEventos,
																							 tiempoCaida,
																							 especialPendiente
																							 ))
																  {
																	  juegoTerminado =
																		  true;
																	  
																	  ventana.setTitle(
																					   "GAME OVER - Tetris"
																					   );
																  }
															  }
																			  
																			  relojCaida.restart();
														  }
															  
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
															  
															  dibujarEspera(
																			ventana,
																			pila
																			);
															  
															  dibujarInformacion(
																				 ventana,
																				 fuente,
																				 puntaje,
																				 lineasTotales
																				 );
															  
															  ventana.display();
							 }
							 
							 if (!estaVaciaPila(
												pila))
							 {
								 desapilar(
										   pila
										   );
							 }
												
												liberarColaEventos(
																   colaEventos
																   );
												
												liberarTablero(
															   tablero
															   );
												
												return 0;
}
