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
#include "Historial.h"

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
		
		else if (
				 eventoActivado.tipo ==
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
				 
		else if (
				 eventoActivado.tipo ==
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
		if (
			eliminarFilaInferiorOcupada(
										tablero
										))
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
	
	Pieza nuevaPieza =
		obtenerSiguientePieza(
							  cola
							  );
	
	asegurarProximasPiezas(
						   cola
						   );
	
	if (especialPendiente)
	{
		nuevaPieza.especial =
			true;
		
		especialPendiente =
			false;
		
		cout
			<< "PIEZA ESPECIAL CREADA"
			<< endl;
	}
	
	if (!puedeColocarse(
						tablero,
						nuevaPieza))
	{
		return false;
	}
						
						pieza =
						nuevaPieza;
						
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
							 sf::VideoMode(470, 650),
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
							 sf::Clock relojReplay;
							 
							 float tiempoCaida =
								 0.6f;
							 
							 float tiempoReplay =
								 0.15f;
							 
							 bool juegoTerminado =
								 false;
							 
							 bool replayAutomatico =
								 false;
							 
							 bool modoReplay =
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
							 
							 Historial historial;
							 
							 inicializarHistorial(
												  historial
												  );
							 
							 registrarEstado(
											 historial,
											 tablero,
											 pieza,
											 puntaje,
											 lineasTotales,
											 tiempoCaida,
											 especialPendiente,
											 pila,
											 cola,
											 colaEventos,
											 'I'
											 );
							 
							 while (ventana.isOpen())
							 {
								 sf::Event evento;
								 
								 while (
										ventana.pollEvent(
														  evento
														  ))
								 {
									 if (
										 evento.type ==
										 sf::Event::Closed)
									 {
										 ventana.close();
									 }
										 
										 if (
											 evento.type ==
											 sf::Event::KeyPressed)
										 {
											 if (!juegoTerminado)
											 {
												 if (
													 evento.key.code ==
													 sf::Keyboard::A)
												 {
													 if (
														 moverPiezaHorizontal(
																			  tablero,
																			  pieza,
																			  -1
																			  ))
													 {
														 registrarEstado(
																		 historial,
																		 tablero,
																		 pieza,
																		 puntaje,
																		 lineasTotales,
																		 tiempoCaida,
																		 especialPendiente,
																		 pila,
																		 cola,
																		 colaEventos,
																		 'A'
																		 );
													 }
												 }
													 
												 else if (
														  evento.key.code ==
														  sf::Keyboard::D)
													 {
													 if (
														 moverPiezaHorizontal(
																			  tablero,
																			  pieza,
																			  1
																			  ))
													 {
														 registrarEstado(
																		 historial,
																		 tablero,
																		 pieza,
																		 puntaje,
																		 lineasTotales,
																		 tiempoCaida,
																		 especialPendiente,
																		 pila,
																		 cola,
																		 colaEventos,
																		 'D'
																		 );
													 }
													 }
														  
												 else if (
														  evento.key.code ==
														  sf::Keyboard::W)
														  {
													 if (
														 rotarPiezaValida(
																		  tablero,
																		  pieza
																		  ))
													 {
														 registrarEstado(
																		 historial,
																		 tablero,
																		 pieza,
																		 puntaje,
																		 lineasTotales,
																		 tiempoCaida,
																		 especialPendiente,
																		 pila,
																		 cola,
																		 colaEventos,
																		 'W'
																		 );
													 }
														  }
														  
												 else if (
														  evento.key.code ==
														  sf::Keyboard::S)
														  {
													 if (
														 bajarPieza(
																	tablero,
																	pieza
																	))
													 {
														 registrarEstado(
																		 historial,
																		 tablero,
																		 pieza,
																		 puntaje,
																		 lineasTotales,
																		 tiempoCaida,
																		 especialPendiente,
																		 pila,
																		 cola,
																		 colaEventos,
																		 'S'
																		 );
													 }
													 else
																	{
																		bool continua =
																			fijarYCrearNuevaPieza(
																								  tablero,
																								  cola,
																								  pieza,
																								  puntaje,
																								  lineasTotales,
																								  colaEventos,
																								  tiempoCaida,
																								  especialPendiente
																								  );
																		
																		if (continua)
																		{
																			registrarEstado(
																							historial,
																							tablero,
																							pieza,
																							puntaje,
																							lineasTotales,
																							tiempoCaida,
																							especialPendiente,
																							pila,
																							cola,
																							colaEventos,
																							'P'
																							);
																		}
																		else
																		{
																			juegoTerminado =
																				true;
																			
																			replayAutomatico =
																				false;
																			
																			modoReplay =
																				false;
																			
																			ventana.setTitle(
																							 "GAME OVER - Tetris"
																							 );
																		}
																	}
																	
																	relojCaida.restart();
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
																	   
																	   registrarEstado(
																					   historial,
																					   tablero,
																					   pieza,
																					   puntaje,
																					   lineasTotales,
																					   tiempoCaida,
																					   especialPendiente,
																					   pila,
																					   cola,
																					   colaEventos,
																					   'H'
																					   );
																	   
																	   if (!puedeColocarse(
																						   tablero,
																						   pieza))
																	   {
																		   juegoTerminado =
																			   true;
																		   
																		   replayAutomatico =
																			   false;
																		   
																		   modoReplay =
																			   false;
																		   
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
													 bool bajo =
														 false;
													 
													 while (
															bajarPieza(
																	   tablero,
																	   pieza
																	   ))
													 {
														 bajo =
															 true;
													 }
																	   
																	   if (bajo)
																	   {
																		   registrarEstado(
																						   historial,
																						   tablero,
																						   pieza,
																						   puntaje,
																						   lineasTotales,
																						   tiempoCaida,
																						   especialPendiente,
																						   pila,
																						   cola,
																						   colaEventos,
																						   'X'
																						   );
																	   }
																	   
																	   bool continua =
																		   fijarYCrearNuevaPieza(
																								 tablero,
																								 cola,
																								 pieza,
																								 puntaje,
																								 lineasTotales,
																								 colaEventos,
																								 tiempoCaida,
																								 especialPendiente
																								 );
																	   
																	   if (continua)
																	   {
																		   registrarEstado(
																						   historial,
																						   tablero,
																						   pieza,
																						   puntaje,
																						   lineasTotales,
																						   tiempoCaida,
																						   especialPendiente,
																						   pila,
																						   cola,
																						   colaEventos,
																						   'P'
																						   );
																	   }
																	   else
																	   {
																		   juegoTerminado =
																			   true;
																		   
																		   replayAutomatico =
																			   false;
																		   
																		   modoReplay =
																			   false;
																		   
																		   ventana.setTitle(
																							"GAME OVER - Tetris"
																							);
																	   }
																	   
																	   relojCaida.restart();
														  }
														  
												 else if (
														  evento.key.code ==
														  sf::Keyboard::Z)
														  {
													 replayAutomatico =
														 false;
													 
													 if (
														 deshacer(
																  historial,
																  tablero,
																  pieza,
																  puntaje,
																  lineasTotales,
																  tiempoCaida,
																  especialPendiente,
																  pila,
																  cola,
																  colaEventos
																  ))
													 {
														 cout
															 << "DESHACER"
															 << endl;
														 
														 relojCaida.restart();
													 }
														  }
														  
												 else if (
														  evento.key.code ==
														  sf::Keyboard::Y)
														  {
													 replayAutomatico =
														 false;
													 
													 if (
														 rehacer(
																 historial,
																 tablero,
																 pieza,
																 puntaje,
																 lineasTotales,
																 tiempoCaida,
																 especialPendiente,
																 pila,
																 cola,
																 colaEventos
																 ))
													 {
														 cout
															 << "REHACER"
															 << endl;
														 
														 relojCaida.restart();
													 }
														  }
														  
												 else if (
														  evento.key.code ==
														  sf::Keyboard::Escape)
														  {
													 ventana.close();
														  }
											 }
											 
											 else
											 {
												 if (
													 evento.key.code ==
													 sf::Keyboard::R)
												 {
													 if (!modoReplay)
													 {
														 if (
															 irInicioHistorial(
																			   historial,
																			   tablero,
																			   pieza,
																			   puntaje,
																			   lineasTotales,
																			   tiempoCaida,
																			   especialPendiente,
																			   pila,
																			   cola,
																			   colaEventos
																			   ))
														 {
															 modoReplay =
																 true;
															 
															 replayAutomatico =
																 true;
															 
															 relojReplay.restart();
															 
															 ventana.setTitle(
																			  "REPLAY - Tetris"
																			  );
														 }
													 }
													 else
													 {
														 if (
															 historial.actual ==
															 historial.ultimo)
														 {
															 irInicioHistorial(
																			   historial,
																			   tablero,
																			   pieza,
																			   puntaje,
																			   lineasTotales,
																			   tiempoCaida,
																			   especialPendiente,
																			   pila,
																			   cola,
																			   colaEventos
																			   );
														 }
															 
															 replayAutomatico =
															 true;
															 
															 relojReplay.restart();
															 
															 ventana.setTitle(
																			  "REPLAY - Tetris"
																			  );
													 }
												 }
													 
												 else if (
														  evento.key.code ==
														  sf::Keyboard::Z)
													 {
													 replayAutomatico =
														 false;
													 
													 deshacer(
															  historial,
															  tablero,
															  pieza,
															  puntaje,
															  lineasTotales,
															  tiempoCaida,
															  especialPendiente,
															  pila,
															  cola,
															  colaEventos
															  );
													 
													 if (modoReplay)
													 {
														 ventana.setTitle(
																		  "REPLAY - Tetris"
																		  );
													 }
													 }
														  
												 else if (
														  evento.key.code ==
														  sf::Keyboard::Y)
														  {
													 replayAutomatico =
														 false;
													 
													 rehacer(
															 historial,
															 tablero,
															 pieza,
															 puntaje,
															 lineasTotales,
															 tiempoCaida,
															 especialPendiente,
															 pila,
															 cola,
															 colaEventos
															 );
													 
													 if (modoReplay)
													 {
														 ventana.setTitle(
																		  "REPLAY - Tetris"
																		  );
													 }
														  }
														  
												 else if (
														  evento.key.code ==
														  sf::Keyboard::Escape)
														  {
													 ventana.close();
														  }
											 }
										 }
								 }
														  
														  if (
															  !juegoTerminado
															  &&
															  historial.actual ==
															  historial.ultimo
															  &&
															  relojCaida
															  .getElapsedTime()
															  .asSeconds()
															  >= tiempoCaida)
														  {
															  if (
																  bajarPieza(
																			 tablero,
																			 pieza
																			 ))
															  {
																  registrarEstado(
																				  historial,
																				  tablero,
																				  pieza,
																				  puntaje,
																				  lineasTotales,
																				  tiempoCaida,
																				  especialPendiente,
																				  pila,
																				  cola,
																				  colaEventos,
																				  'B'
																				  );
															  }
															  else
																			 {
																				 bool continua =
																					 fijarYCrearNuevaPieza(
																										   tablero,
																										   cola,
																										   pieza,
																										   puntaje,
																										   lineasTotales,
																										   colaEventos,
																										   tiempoCaida,
																										   especialPendiente
																										   );
																				 
																				 if (continua)
																				 {
																					 registrarEstado(
																									 historial,
																									 tablero,
																									 pieza,
																									 puntaje,
																									 lineasTotales,
																									 tiempoCaida,
																									 especialPendiente,
																									 pila,
																									 cola,
																									 colaEventos,
																									 'P'
																									 );
																				 }
																				 else
																				 {
																					 juegoTerminado =
																						 true;
																					 
																					 replayAutomatico =
																						 false;
																					 
																					 modoReplay =
																						 false;
																					 
																					 ventana.setTitle(
																									  "GAME OVER - Tetris"
																									  );
																				 }
																			 }
																			 
																			 relojCaida.restart();
														  }
															  
															  if (
																  juegoTerminado
																  &&
																  replayAutomatico
																  &&
																  relojReplay
																  .getElapsedTime()
																  .asSeconds()
																  >= tiempoReplay)
															  {
																  if (
																	  !rehacer(
																			   historial,
																			   tablero,
																			   pieza,
																			   puntaje,
																			   lineasTotales,
																			   tiempoCaida,
																			   especialPendiente,
																			   pila,
																			   cola,
																			   colaEventos
																			   ))
																  {
																	  replayAutomatico =
																		  false;
																	  
																	  ventana.setTitle(
																					   "REPLAY - Tetris"
																					   );
																  }
																			   
																			   relojReplay.restart();
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
																  
																  dibujarControlesReplay(
																						 ventana,
																						 fuente,
																						 juegoTerminado,
																						 modoReplay,
																						 replayAutomatico
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
												
												liberarHistorial(
																 historial
																 );
												
												liberarColaEventos(
																   colaEventos
																   );
												
												liberarTablero(
															   tablero
															   );
												
												return 0;
}
