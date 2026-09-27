#include "Juego.h"
#include "Interfaz.h"
#include "PruebasOrdenamiento.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

Juego::Juego()
	: ventana(sf::VideoMode(470, 650), "Tetris - Proyecto I"),
	tiempoCaida(0.6f), tiempoReplay(0.15f),
	juegoIniciado(false), pantallaConfiguracion(false),
	juegoPausado(false), juegoTerminado(false),
	puntajeRegistrado(false), replayAutomatico(false),
	modoReplay(false), mostrarTop10Grafico(false),
	especialPendiente(false), nombreJugador(""),
	algoritmoOrdenamiento(1), puntaje(0), puntajeFinal(0),
	lineasTotales(0), cantidadTop10(0)
{
	srand(time(nullptr));
	cargarFuente();
	inicializarEstructuras();
}

Juego::~Juego()
{
	liberarPila();
	liberarColaPiezas();
	liberarHistorial(historial);
	liberarColaEventos(colaEventos);
	liberarTablero(tablero);
}

void Juego::cargarFuente()
{
	if (!fuente.loadFromFile("C:/Windows/Fonts/arial.ttf"))
		cout << "Error al cargar la fuente" << endl;
}

void Juego::inicializarEstructuras()
{
	inicializarTablero(tablero);
	
	inicializarCola(cola);
	generarBolsa(cola);
	
	inicializarPila(pila);
	
	pieza = obtenerSiguientePieza(cola);
	asegurarProximasPiezas(cola);
	
	inicializarColaEventos(colaEventos);
	programarEventosIniciales();
	
	cout << "EVENTOS PROGRAMADOS:" << endl;
	mostrarEventos(colaEventos);
	
	inicializarHistorial(historial);
	registrarEstadoActual('I');
}

void Juego::programarEventosIniciales()
{
	Evento eventoEspecial;
	eventoEspecial.tipo = PIEZA_ESPECIAL;
	eventoEspecial.momento = 7;
	insertarEvento(colaEventos, eventoEspecial);
	
	Evento eventoVelocidad;
	eventoVelocidad.tipo = AUMENTAR_VELOCIDAD;
	eventoVelocidad.momento = 3;
	insertarEvento(colaEventos, eventoVelocidad);
	
	Evento eventoBono;
	eventoBono.tipo = BONO_PUNTOS;
	eventoBono.momento = 5;
	insertarEvento(colaEventos, eventoBono);
}

void Juego::liberarPila()
{
	while (!estaVaciaPila(pila))
		desapilar(pila);
}

void Juego::liberarColaPiezas()
{
	while (cola.frente != nullptr)
	{
		NodoPieza *borrar = cola.frente;
		cola.frente = cola.frente->siguiente;
		delete borrar;
	}
	
	cola.frente = nullptr;
	cola.final = nullptr;
}

void Juego::reiniciarEstructurasPartida()
{
	liberarHistorial(historial);
	liberarColaEventos(colaEventos);
	liberarPila();
	liberarColaPiezas();
	liberarTablero(tablero);
	
	inicializarTablero(tablero);
	
	inicializarCola(cola);
	generarBolsa(cola);
	
	inicializarPila(pila);
	
	pieza = obtenerSiguientePieza(cola);
	asegurarProximasPiezas(cola);
	
	puntaje = 0;
	lineasTotales = 0;
	tiempoCaida = 0.6f;
	especialPendiente = false;
	
	inicializarColaEventos(colaEventos);
	programarEventosIniciales();
	
	inicializarHistorial(historial);
	registrarEstadoActual('I');
}

void Juego::nuevoJuego()
{
	reiniciarEstructurasPartida();
	
	juegoIniciado = false;
	pantallaConfiguracion = true;
	nombreJugador = "";
	algoritmoOrdenamiento = 1;
	juegoPausado = false;
	juegoTerminado = false;
	puntajeRegistrado = false;
	puntajeFinal = 0;
	replayAutomatico = false;
	modoReplay = false;
	mostrarTop10Grafico = false;
	
	relojCaida.restart();
	ventana.setTitle("Tetris - Proyecto I");
}

void Juego::ejecutar()
{
	while (ventana.isOpen())
	{
		procesarEntrada();
		actualizar();
		dibujar();
	}
}

void Juego::procesarEntrada()
{
	sf::Event evento;
	
	while (ventana.pollEvent(evento))
	{
		if (evento.type == sf::Event::Closed)
			ventana.close();
		
		if (evento.type == sf::Event::TextEntered)
			procesarTexto(evento);
		
		if (evento.type == sf::Event::KeyPressed)
			procesarTecla(evento.key.code);
	}
}

void Juego::procesarTexto(const sf::Event &evento)
{
	if (!pantallaConfiguracion || juegoIniciado)
		return;
	
	if (evento.text.unicode == 8)
	{
		if (!nombreJugador.empty())
			nombreJugador.erase(nombreJugador.size() - 1, 1);
		
		return;
	}
	
	if (evento.text.unicode >= 32 &&
		evento.text.unicode <= 126 &&
		evento.text.unicode != '|' &&
		nombreJugador.size() < 15)
	{
		nombreJugador += static_cast<char>(evento.text.unicode);
	}
}

void Juego::procesarTecla(sf::Keyboard::Key tecla)
{
	if (!juegoIniciado)
	{
		if (pantallaConfiguracion)
			manejarConfiguracion(tecla);
		else
			manejarInicio(tecla);
		
		return;
	}
	
	if (juegoTerminado)
	{
		manejarGameOver(tecla);
		return;
	}
	
	if (juegoPausado)
	{
		manejarPausa(tecla);
		return;
	}
	
	manejarPartida(tecla);
}

void Juego::manejarInicio(
						  sf::Keyboard::Key tecla)
{
	if (
		tecla ==
		sf::Keyboard::Return)
	{
		pantallaConfiguracion =
			true;
	}
		
	else if (
			 tecla ==
			 sf::Keyboard::M)
		{
		ejecutarPruebasOrdenamiento();
		}
			 
	else if (
			 tecla ==
			 sf::Keyboard::Escape)
			 {
		ventana.close();
			 }
}

void Juego::manejarConfiguracion(sf::Keyboard::Key tecla)
{
	if (tecla == sf::Keyboard::Right)
	{
		if (algoritmoOrdenamiento == 1)
			algoritmoOrdenamiento = 2;
		else
			algoritmoOrdenamiento = 1;
	}
	else if (tecla == sf::Keyboard::Return)
	{
		if (nombreJugador.empty())
			return;
		
		juegoIniciado = true;
		pantallaConfiguracion = false;
		juegoPausado = false;
		relojCaida.restart();
		ventana.setTitle("Tetris - Proyecto I");
		
		cout << "Jugador: " << nombreJugador << endl;
		
		if (algoritmoOrdenamiento == 1)
			cout << "Ordenamiento: Bubble Sort" << endl;
		else
			cout << "Ordenamiento: Merge Sort" << endl;
	}
	else if (tecla == sf::Keyboard::Escape)
	{
		pantallaConfiguracion = false;
	}
}

void Juego::manejarGameOver(sf::Keyboard::Key tecla)
{
	if (mostrarTop10Grafico)
	{
		if (tecla == sf::Keyboard::T)
			mostrarTop10Grafico = false;
		else if (tecla == sf::Keyboard::N)
			nuevoJuego();
		else if (tecla == sf::Keyboard::Escape)
			ventana.close();
		
		return;
	}
	
	if (tecla == sf::Keyboard::T)
	{
		mostrarTop10Grafico = true;
		replayAutomatico = false;
	}
	else if (tecla == sf::Keyboard::N)
		nuevoJuego();
	else if (tecla == sf::Keyboard::R)
		iniciarReplay();
	else if (tecla == sf::Keyboard::Z)
		retrocederReplay();
	else if (tecla == sf::Keyboard::Y)
		avanzarReplay();
	else if (tecla == sf::Keyboard::Escape)
		ventana.close();
}

void Juego::manejarPausa(sf::Keyboard::Key tecla)
{
	if (tecla == sf::Keyboard::P)
	{
		juegoPausado = false;
		relojCaida.restart();
		ventana.setTitle("Tetris - Proyecto I");
	}
	else if (tecla == sf::Keyboard::Escape)
	{
		ventana.close();
	}
}

void Juego::manejarPartida(sf::Keyboard::Key tecla)
{
	if (tecla == sf::Keyboard::Escape)
		ventana.close();
	else if (tecla == sf::Keyboard::P)
	{
		juegoPausado = true;
		ventana.setTitle("PAUSA - Tetris");
	}
	else if (tecla == sf::Keyboard::A)
		moverHorizontal(-1, 'A');
	else if (tecla == sf::Keyboard::D)
		moverHorizontal(1, 'D');
	else if (tecla == sf::Keyboard::W)
		rotarActual();
	else if (tecla == sf::Keyboard::S)
		bajarManual();
	else if (tecla == sf::Keyboard::H)
		usarHold();
	else if (tecla == sf::Keyboard::X)
		caidaRapida();
	else if (tecla == sf::Keyboard::Z)
		deshacerMovimiento();
	else if (tecla == sf::Keyboard::Y)
		rehacerMovimiento();
}

void Juego::iniciarReplay()
{
	if (!modoReplay)
	{
		if (irInicioHistorial(
							  historial, tablero, pieza, puntaje, lineasTotales,
							  tiempoCaida, especialPendiente, pila, cola, colaEventos))
		{
			modoReplay = true;
			replayAutomatico = true;
			relojReplay.restart();
			ventana.setTitle("REPLAY - Tetris");
		}
							  
							  return;
	}
	
	if (historial.actual == historial.ultimo)
	{
		irInicioHistorial(
						  historial, tablero, pieza, puntaje, lineasTotales,
						  tiempoCaida, especialPendiente, pila, cola, colaEventos);
	}
	
	replayAutomatico = true;
	relojReplay.restart();
	ventana.setTitle("REPLAY - Tetris");
}

void Juego::retrocederReplay()
{
	replayAutomatico = false;
	
	deshacer(
			 historial, tablero, pieza, puntaje, lineasTotales,
			 tiempoCaida, especialPendiente, pila, cola, colaEventos);
}

void Juego::avanzarReplay()
{
	replayAutomatico = false;
	
	rehacer(
			historial, tablero, pieza, puntaje, lineasTotales,
			tiempoCaida, especialPendiente, pila, cola, colaEventos);
}

void Juego::registrarEstadoActual(char accion)
{
	registrarEstado(
					historial, tablero, pieza, puntaje, lineasTotales,
					tiempoCaida, especialPendiente, pila, cola, colaEventos, accion);
}

void Juego::moverHorizontal(int desplazamiento, char accion)
{
	if (moverPiezaHorizontal(tablero, pieza, desplazamiento))
		registrarEstadoActual(accion);
}

void Juego::rotarActual()
{
	if (rotarPiezaValida(tablero, pieza))
		registrarEstadoActual('W');
}

void Juego::bajarManual()
{
	if (bajarPieza(tablero, pieza))
		registrarEstadoActual('S');
	else
		fijarPiezaYContinuar();
	
	relojCaida.restart();
}

void Juego::usarHold()
{
	if (estaVaciaPila(pila))
	{
		Pieza guardar;
		inicializarPieza(guardar, pieza.tipo);
		
		guardar.especial = pieza.especial;
		guardar.numeroBolsa = pieza.numeroBolsa;
		
		apilar(pila, guardar);
		
		pieza = obtenerSiguientePieza(cola);
		asegurarProximasPiezas(cola);
	}
	else
	{
		Pieza guardada = desapilar(pila);
		
		Pieza guardar;
		inicializarPieza(guardar, pieza.tipo);
		
		guardar.especial = pieza.especial;
		guardar.numeroBolsa = pieza.numeroBolsa;
		
		apilar(pila, guardar);
		
		bool especialGuardada = guardada.especial;
		int bolsaGuardada = guardada.numeroBolsa;
		
		inicializarPieza(pieza, guardada.tipo);
		
		pieza.especial = especialGuardada;
		pieza.numeroBolsa = bolsaGuardada;
	}
	
	registrarEstadoActual('H');
	
	if (!puedeColocarse(tablero, pieza))
		terminarJuego();
	
	relojCaida.restart();
}

void Juego::caidaRapida()
{
	bool bajo = false;
	
	while (bajarPieza(tablero, pieza))
		bajo = true;
	
	if (bajo)
		registrarEstadoActual('X');
	
	fijarPiezaYContinuar();
	relojCaida.restart();
}

void Juego::deshacerMovimiento()
{
	if (deshacer(
				 historial, tablero, pieza, puntaje, lineasTotales,
				 tiempoCaida, especialPendiente, pila, cola, colaEventos))
	{
		cout << "DESHACER" << endl;
		relojCaida.restart();
	}
}

void Juego::rehacerMovimiento()
{
	if (rehacer(
				historial, tablero, pieza, puntaje, lineasTotales,
				tiempoCaida, especialPendiente, pila, cola, colaEventos))
	{
		cout << "REHACER" << endl;
		relojCaida.restart();
	}
}

void Juego::procesarEventosProgramados()
{
	Evento proximoEvento;
	
	while (verProximoEvento(colaEventos, proximoEvento) &&
		   lineasTotales >= proximoEvento.momento)
	{
		Evento eventoActivado;
		extraerEvento(colaEventos, eventoActivado);
		
		if (eventoActivado.tipo == AUMENTAR_VELOCIDAD)
		{
			tiempoCaida = 0.45f;
			
			cout << "EVENTO ACTIVADO: AUMENTAR VELOCIDAD" << endl;
			cout << "Nuevo tiempo de caida: "
				<< tiempoCaida << " segundos" << endl;
		}
		else if (eventoActivado.tipo == BONO_PUNTOS)
		{
			puntaje += 500;
			
			cout << "EVENTO ACTIVADO: BONO DE PUNTOS" << endl;
			cout << "Bono: +500 puntos" << endl;
			cout << "Puntaje total: " << puntaje << endl;
		}
		else if (eventoActivado.tipo == PIEZA_ESPECIAL)
		{
			especialPendiente = true;
			
			cout << "EVENTO ACTIVADO: PIEZA ESPECIAL" << endl;
			cout << "La siguiente pieza sera especial" << endl;
		}
	}
}

bool Juego::fijarYCrearNuevaPieza()
{
	bool eraEspecial = pieza.especial;
	
	colocarPieza(tablero, pieza);
	
	animarFilasCompletas(
						 ventana, tablero, pieza, cola, pila,
						 fuente, puntaje, lineasTotales);
	
	int eliminadas = eliminarFilasCompletas(tablero);
	
	if (eliminadas > 0)
	{
		lineasTotales += eliminadas;
		puntaje += eliminadas * 100;
		
		cout << "Filas eliminadas: " << eliminadas << endl;
		cout << "Lineas totales: " << lineasTotales << endl;
		cout << "Puntaje: " << puntaje << endl;
	}
	
	if (eraEspecial)
	{
		if (eliminarFilaInferiorOcupada(tablero))
			cout << "EFECTO ESPECIAL: fila eliminada" << endl;
	}
	
	procesarEventosProgramados();
	
	Pieza nuevaPieza = obtenerSiguientePieza(cola);
	asegurarProximasPiezas(cola);
	
	if (especialPendiente)
	{
		nuevaPieza.especial = true;
		especialPendiente = false;
		
		cout << "PIEZA ESPECIAL CREADA" << endl;
	}
	
	if (!puedeColocarse(tablero, nuevaPieza))
		return false;
	
	pieza = nuevaPieza;
	return true;
}

void Juego::fijarPiezaYContinuar()
{
	bool continua = fijarYCrearNuevaPieza();
	
	if (continua)
		registrarEstadoActual('P');
	else
		terminarJuego();
}

void Juego::terminarJuego()
{
	puntajeFinal = puntaje;
	juegoTerminado = true;
	replayAutomatico = false;
	modoReplay = false;
	
	ventana.setTitle("GAME OVER - Tetris");
}

void Juego::actualizar()
{
	actualizarCaidaAutomatica();
	registrarPuntajeSiCorresponde();
	actualizarReplay();
}

void Juego::actualizarCaidaAutomatica()
{
	if (!juegoIniciado || juegoPausado || juegoTerminado)
		return;
	
	if (historial.actual != historial.ultimo)
		return;
	
	if (relojCaida.getElapsedTime().asSeconds() < tiempoCaida)
		return;
	
	if (bajarPieza(tablero, pieza))
		registrarEstadoActual('B');
	else
		fijarPiezaYContinuar();
	
	relojCaida.restart();
}

void Juego::registrarPuntajeSiCorresponde()
{
	if (!juegoTerminado || puntajeRegistrado)
		return;
	
	bool entroTop10 = registrarPuntajeTop10(
											nombreJugador,
											puntajeFinal,
											algoritmoOrdenamiento);
	
	cout << endl;
	cout << "==========================" << endl;
	cout << "GAME OVER" << endl;
	cout << "Jugador: " << nombreJugador << endl;
	cout << "Puntaje final: " << puntajeFinal << endl;
	
	if (algoritmoOrdenamiento == 1)
		cout << "Ordenamiento: Bubble Sort" << endl;
	else
		cout << "Ordenamiento: Merge Sort" << endl;
	
	if (entroTop10)
		cout << "El puntaje ingreso al TOP 10" << endl;
	else
		cout << "El puntaje NO ingreso al TOP 10" << endl;
	
	cout << "==========================" << endl;
	
	cantidadTop10 = cargarPuntajes(top10, 10);
	
	ordenarPuntajes(
					top10,
					cantidadTop10,
					algoritmoOrdenamiento);
	
	mostrarTop10(top10, cantidadTop10);
	
	puntajeRegistrado = true;
}

void Juego::actualizarReplay()
{
	if (!juegoTerminado || !replayAutomatico || mostrarTop10Grafico)
		return;
	
	if (relojReplay.getElapsedTime().asSeconds() < tiempoReplay)
		return;
	
	if (!rehacer(
				 historial, tablero, pieza, puntaje, lineasTotales,
				 tiempoCaida, especialPendiente, pila, cola, colaEventos))
	{
		replayAutomatico = false;
		ventana.setTitle("REPLAY - Tetris");
	}
				 
				 relojReplay.restart();
}

void Juego::dibujar()
{
	ventana.clear(sf::Color::Black);
	
	if (!juegoIniciado)
	{
		if (pantallaConfiguracion)
		{
			dibujarPantallaConfiguracion(
										 ventana,
										 fuente,
										 nombreJugador,
										 algoritmoOrdenamiento);
		}
		else
		{
			dibujarPantallaInicio(ventana, fuente);
		}
	}
	else
	{
		dibujarJuego();
	}
	
	ventana.display();
}

void Juego::dibujarJuego()
{
	dibujarTablero(ventana, tablero, pieza);
	dibujarProximas(ventana, cola);
	dibujarEspera(ventana, pila);
	dibujarInformacion(ventana, fuente, puntaje, lineasTotales);
	
	if (juegoPausado)
		dibujarPantallaPausa(ventana, fuente);
	
	if (!juegoTerminado)
		return;
	
	if (mostrarTop10Grafico)
	{
		dibujarTop10(
					 ventana,
					 fuente,
					 top10,
					 cantidadTop10);
	}
	else
	{
		dibujarControlesReplay(
							   ventana,
							   fuente,
							   juegoTerminado,
							   modoReplay,
							   replayAutomatico);
	}
}
