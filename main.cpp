#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

#include "Tablero.h"
#include "Pieza.h"
#include "ColaPiezas.h"
#include "Interfaz.h"
#include "PilaEspera.h"
#include "Eventos.h"
#include "Historial.h"
#include "Puntajes.h"

using namespace std;

void programarEventosIniciales(
							   ColaEventos &colaEventos)
{
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
}

void liberarColaPiezasLocal(
							ColaPiezas &cola)
{
	while (
		   cola.frente != nullptr)
	{
		NodoPieza *borrar =
			cola.frente;
		
		cola.frente =
			cola.frente->siguiente;
		
		delete borrar;
	}
		   
		   cola.frente =
		   nullptr;
		   
		   cola.final =
			   nullptr;
}

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
		
		if (
			eventoActivado.tipo ==
			AUMENTAR_VELOCIDAD)
		{
			tiempoCaida =
				0.45f;
			
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
			puntaje +=
				500;
			
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
			especialPendiente =
				true;
			
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
						   bool &especialPendiente,
						   sf::RenderWindow &ventana,
						   sf::Font &fuente,
						   PilaEspera pila)
{
	bool eraEspecial =
		pieza.especial;
	
	colocarPieza(
				 tablero,
				 pieza
				 );
	
	animarFilasCompletas(
						 ventana,
						 tablero,
						 pieza,
						 cola,
						 pila,
						 fuente,
						 puntaje,
						 lineasTotales
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

void reiniciarPartida(
					  Tablero &tablero,
					  ColaPiezas &cola,
					  PilaEspera &pila,
					  Pieza &pieza,
					  ColaEventos &colaEventos,
					  Historial &historial,
					  int &puntaje,
					  int &lineasTotales,
					  float &tiempoCaida,
					  bool &especialPendiente)
{
	liberarHistorial(
					 historial
					 );
	
	liberarColaEventos(
					   colaEventos
					   );
	
	while (
		   !estaVaciaPila(
						  pila
						  ))
	{
		desapilar(
				  pila
				  );
	}
						  
						  liberarColaPiezasLocal(
												 cola
												 );
						  
						  liberarTablero(
										 tablero
										 );
						  
						  inicializarTablero(
											 tablero
											 );
						  
						  inicializarCola(
										  cola
										  );
						  
						  generarBolsa(
									   cola
									   );
						  
						  inicializarPila(
										  pila
										  );
						  
						  pieza =
							  obtenerSiguientePieza(
													cola
													);
						  
						  asegurarProximasPiezas(
												 cola
												 );
						  
						  puntaje =
							  0;
						  
						  lineasTotales =
							  0;
						  
						  tiempoCaida =
							  0.6f;
						  
						  especialPendiente =
							  false;
						  
						  inicializarColaEventos(
												 colaEventos
												 );
						  
						  programarEventosIniciales(
													colaEventos
													);
						  
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
}

int main()
{
	srand(time(nullptr));
	
	Tablero tablero;
	inicializarTablero(
					   tablero
					   );
	
	ColaPiezas cola;
	inicializarCola(
					cola
					);
	
	generarBolsa(
				 cola
				 );
	
	PilaEspera pila;
	inicializarPila(
					pila
					);
	
	Pieza pieza;
	
	pieza =
		obtenerSiguientePieza(
							  cola
							  );
	
	asegurarProximasPiezas(
						   cola
						   );
	
	sf::RenderWindow ventana(
							 sf::VideoMode(
										   470,
										   650
										   ),
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
							 
							 bool juegoIniciado =
								 false;
							 
							 bool pantallaConfiguracion =
								 false;
							 
							 string nombreJugador =
								 "";
							 
							 int algoritmoOrdenamiento =
								 1;
							 
							 bool juegoPausado =
								 false;
							 
							 bool juegoTerminado =
								 false;
							 
							 bool puntajeRegistrado =
								 false;
							 
							 int puntajeFinal =
								 0;
							 
							 bool replayAutomatico =
								 false;
							 
							 bool modoReplay =
								 false;
							 
							 bool mostrarTop10Grafico =
								 false;
							 
							 RegistroPuntaje top10[10];
							 
							 int cantidadTop10 =
								 0;
							 
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
							 
							 programarEventosIniciales(
													   colaEventos
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
							 
							 while (
									ventana.isOpen())
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
											 sf::Event::TextEntered
											 &&
											 pantallaConfiguracion
											 &&
											 !juegoIniciado)
										 {
											 if (
												 evento.text.unicode ==
												 8)
											 {
												 if (
													 !nombreJugador.empty())
												 {
													 nombreJugador.erase(
																		 nombreJugador.size() - 1,
																		 1
																		 );
												 }
											 }
												 
											 else if (
													  evento.text.unicode >= 32
													  &&
													  evento.text.unicode <= 126
													  &&
													  evento.text.unicode != '|'
													  &&
													  nombreJugador.size() < 15)
												 {
												 nombreJugador +=
													 static_cast<char>(
																	   evento.text.unicode
																	   );
												 }
										 }
											 
											 if (
												 evento.type ==
												 sf::Event::KeyPressed)
											 {
												 if (!juegoIniciado)
												 {
													 if (
														 !pantallaConfiguracion)
													 {
														 if (
															 evento.key.code ==
															 sf::Keyboard::Return)
														 {
															 pantallaConfiguracion =
																 true;
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
																 sf::Keyboard::Right)
															 {
																 if (
																	 algoritmoOrdenamiento ==
																	 1)
																 {
																	 algoritmoOrdenamiento =
																		 2;
																 }
																 else
																	 {
																		 algoritmoOrdenamiento =
																			 1;
																	 }
															 }
																 
															 else if (
																	  evento.key.code ==
																	  sf::Keyboard::Return)
																 {
																 if (
																	 !nombreJugador.empty())
																 {
																	 juegoIniciado =
																		 true;
																	 
																	 pantallaConfiguracion =
																		 false;
																	 
																	 juegoPausado =
																		 false;
																	 
																	 relojCaida.restart();
																	 
																	 ventana.setTitle(
																					  "Tetris - Proyecto I"
																					  );
																	 
																	 cout
																		 << "Jugador: "
																		 << nombreJugador
																		 << endl;
																	 
																	 if (
																		 algoritmoOrdenamiento ==
																		 1)
																	 {
																		 cout
																			 << "Ordenamiento: "
																			 << "Bubble Sort"
																			 << endl;
																	 }
																	 else
																		 {
																			 cout
																				 << "Ordenamiento: "
																				 << "Merge Sort"
																				 << endl;
																		 }
																 }
																 }
																	  
															 else if (
																	  evento.key.code ==
																	  sf::Keyboard::Escape)
																	  {
																 pantallaConfiguracion =
																	 false;
																	  }
														 }
												 }
												 
												 else if (
														  juegoTerminado)
												 {
													 if (
														 mostrarTop10Grafico)
													 {
														 if (
															 evento.key.code ==
															 sf::Keyboard::T)
														 {
															 mostrarTop10Grafico =
																 false;
														 }
															 
														 else if (
																  evento.key.code ==
																  sf::Keyboard::N)
															 {
															 reiniciarPartida(
																			  tablero,
																			  cola,
																			  pila,
																			  pieza,
																			  colaEventos,
																			  historial,
																			  puntaje,
																			  lineasTotales,
																			  tiempoCaida,
																			  especialPendiente
																			  );
															 
															 juegoIniciado =
																 false;
															 
															 pantallaConfiguracion =
																 true;
															 
															 nombreJugador =
																 "";
															 
															 algoritmoOrdenamiento =
																 1;
															 
															 juegoPausado =
																 false;
															 
															 juegoTerminado =
																 false;
															 
															 puntajeRegistrado =
																 false;
															 
															 puntajeFinal =
																 0;
															 
															 replayAutomatico =
																 false;
															 
															 modoReplay =
																 false;
															 
															 mostrarTop10Grafico =
																 false;
															 
															 relojCaida.restart();
															 
															 ventana.setTitle(
																			  "Tetris - Proyecto I"
																			  );
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
																 sf::Keyboard::T)
															 {
																 mostrarTop10Grafico =
																	 true;
																 
																 replayAutomatico =
																	 false;
															 }
																 
															 else if (
																	  evento.key.code ==
																	  sf::Keyboard::N)
																 {
																 reiniciarPartida(
																				  tablero,
																				  cola,
																				  pila,
																				  pieza,
																				  colaEventos,
																				  historial,
																				  puntaje,
																				  lineasTotales,
																				  tiempoCaida,
																				  especialPendiente
																				  );
																 
																 juegoIniciado =
																	 false;
																 
																 pantallaConfiguracion =
																	 true;
																 
																 nombreJugador =
																	 "";
																 
																 algoritmoOrdenamiento =
																	 1;
																 
																 juegoPausado =
																	 false;
																 
																 juegoTerminado =
																	 false;
																 
																 puntajeRegistrado =
																	 false;
																 
																 puntajeFinal =
																	 0;
																 
																 replayAutomatico =
																	 false;
																 
																 modoReplay =
																	 false;
																 
																 mostrarTop10Grafico =
																	 false;
																 
																 relojCaida.restart();
																 
																 ventana.setTitle(
																				  "Tetris - Proyecto I"
																				  );
																 }
																	  
															 else if (
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
																	  }
																	  
															 else if (
																	  evento.key.code ==
																	  sf::Keyboard::Escape)
																	  {
																 ventana.close();
																	  }
														 }
												 }
														  
												 else if (
														  juegoPausado)
														  {
													 if (
														 evento.key.code ==
														 sf::Keyboard::P)
													 {
														 juegoPausado =
															 false;
														 
														 relojCaida.restart();
														 
														 ventana.setTitle(
																		  "Tetris - Proyecto I"
																		  );
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
																  sf::Keyboard::Escape)
															  {
																  ventana.close();
															  }
																  
															  else if (
																	   evento.key.code ==
																	   sf::Keyboard::P)
																  {
																  juegoPausado =
																	  true;
																  
																  ventana.setTitle(
																				   "PAUSA - Tetris"
																				   );
																  }
																	   
															  else if (
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
																											   especialPendiente,
																											   ventana,
																											   fuente,
																											   pila
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
																						 puntajeFinal =
																							 puntaje;
																						 
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
																						puntajeFinal =
																							puntaje;
																						
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
																											  especialPendiente,
																											  ventana,
																											  fuente,
																											  pila
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
																						puntajeFinal =
																							puntaje;
																						
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
														  }
											 }
								 }
														  
														  if (
															  juegoIniciado
															  &&
															  !juegoPausado
															  &&
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
																										   especialPendiente,
																										   ventana,
																										   fuente,
																										   pila
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
																					 puntajeFinal =
																						 puntaje;
																					 
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
																  !puntajeRegistrado)
															  {
																  bool entroTop10 =
																	  registrarPuntajeTop10(
																							nombreJugador,
																							puntajeFinal,
																							algoritmoOrdenamiento
																							);
																  
																  cout
																	  << endl
																	  << "=========================="
																	  << endl;
																  
																  cout
																	  << "GAME OVER"
																	  << endl;
																  
																  cout
																	  << "Jugador: "
																	  << nombreJugador
																	  << endl;
																  
																  cout
																	  << "Puntaje final: "
																	  << puntajeFinal
																	  << endl;
																  
																  if (
																	  algoritmoOrdenamiento ==
																	  1)
																  {
																	  cout
																		  << "Ordenamiento: "
																		  << "Bubble Sort"
																		  << endl;
																  }
																  else
																	  {
																		  cout
																			  << "Ordenamiento: "
																			  << "Merge Sort"
																			  << endl;
																	  }
																	  
																	  if (entroTop10)
																	  {
																		  cout
																			  << "El puntaje ingreso "
																			  << "al TOP 10"
																			  << endl;
																	  }
																	  else
																	  {
																		  cout
																			  << "El puntaje NO ingreso "
																			  << "al TOP 10"
																			  << endl;
																	  }
																	  
																	  cout
																		  << "=========================="
																		  << endl;
																	  
																	  cantidadTop10 =
																		  cargarPuntajes(
																						 top10,
																						 10
																						 );
																	  
																	  ordenarPuntajes(
																					  top10,
																					  cantidadTop10,
																					  algoritmoOrdenamiento
																					  );
																	  
																	  mostrarTop10(
																				   top10,
																				   cantidadTop10
																				   );
																	  
																	  puntajeRegistrado =
																		  true;
															  }
																  
																  if (
																	  juegoTerminado
																	  &&
																	  replayAutomatico
																	  &&
																	  !mostrarTop10Grafico
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
																	  
																	  if (!juegoIniciado)
																	  {
																		  if (
																			  !pantallaConfiguracion)
																		  {
																			  dibujarPantallaInicio(
																									ventana,
																									fuente
																									);
																		  }
																		  else
																			  {
																				  dibujarPantallaConfiguracion(
																											   ventana,
																											   fuente,
																											   nombreJugador,
																											   algoritmoOrdenamiento
																											   );
																			  }
																	  }
																	  else
																	  {
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
																		  
																		  if (juegoPausado)
																		  {
																			  dibujarPantallaPausa(
																								   ventana,
																								   fuente
																								   );
																		  }
																		  
																		  if (juegoTerminado)
																		  {
																			  if (
																				  mostrarTop10Grafico)
																			  {
																				  dibujarTop10(
																							   ventana,
																							   fuente,
																							   top10,
																							   cantidadTop10
																							   );
																			  }
																			  else
																				  {
																					  dibujarControlesReplay(
																											 ventana,
																											 fuente,
																											 juegoTerminado,
																											 modoReplay,
																											 replayAutomatico
																											 );
																				  }
																		  }
																	  }
																	  
																	  ventana.display();
							 }
									
									while (
										   !estaVaciaPila(
														  pila
														  ))
									{
										desapilar(
												  pila
												  );
									}
														  
														  liberarColaPiezasLocal(
																				 cola
																				 );
														  
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
